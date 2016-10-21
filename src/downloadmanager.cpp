/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "downloadmanager.h"

#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <stdio.h>

DownloadManager::DownloadManager(QObject *parent)
    : QObject(parent), downloadedCount(0), totalCount(0)
{
}

void DownloadManager::append(const QList<DownloadManager::DownloadItem> &items)
{
    bool empty = downloadQueue.isEmpty();

    for(const DownloadItem & item : items)
    {
        downloadQueue.enqueue(item);
    }

    totalCount += items.size();

    if (empty)
        QTimer::singleShot(0, this, SLOT(startNextDownload()));
}

void DownloadManager::append(const DownloadItem &item)
{
    bool empty = downloadQueue.isEmpty();

    downloadQueue.enqueue(item);
    ++totalCount;

    if (empty)
        QTimer::singleShot(0, this, SLOT(startNextDownload()));
}

void DownloadManager::startNextDownload()
{
    if (downloadQueue.isEmpty())
    {
        logToLogger(Logger::Info, QString("%1/%2 files downloaded successfully").arg(downloadedCount).arg(totalCount));
        emit finished();
        return;
    }

    DownloadItem item = downloadQueue.dequeue();
    currentDownloadItem = item;
    QUrl url = item.url;

    QString filename = item.filePath;

    /*
     * If the filename is empty, all downloaded data should be written into the qbytearray
     */
    if(!filename.isEmpty())
    {
        output.setFileName(filename);

        if(output.exists())
            output.remove();

        if (!output.open(QIODevice::WriteOnly))
        {
            logToLogger(Logger::Error, QString("Problem opening save file '%1' for download '%2': %3")
                        .arg(filename)
                        .arg(QString::fromUtf8(url.toEncoded()))
                        .arg(output.errorString()));

            startNextDownload();
            return;                 // skip this download
        }
    }

    QNetworkRequest request(url);
    currentDownload = manager.get(request);

    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()),
            SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));

    // prepare the output
    logToLogger(Logger::Info, QString("Downloading %1...")
                .arg(QString::fromUtf8(url.toEncoded())));
    downloadTime.start();
}

void DownloadManager::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if(bytesReceived / (bytesTotal * 100) % 10 != 0)
        return;

    // calculate the download speed
    double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
    QString unit;
    if (speed < 1024)
    {
        unit = "bytes/sec";
    }
    else if (speed < 1024*1024)
    {
        speed /= 1024;
        unit = "kB/s";
    }
    else
    {
        speed /= 1024*1024;
        unit = "MB/s";
    }

    logToLogger(Logger::Info, QString("%1 bytes of %2 with %3 %4")
                .arg(bytesReceived)
                .arg(bytesTotal)
                .arg(speed)
                .arg(unit));
}

void DownloadManager::downloadFinished()
{
    output.close();

    if (currentDownload->error())
    {
        logToLogger(Logger::Info, QString("Failed %1...")
                    .arg(currentDownload->errorString()));
    }
    else
    {        
        ++downloadedCount;
    }

    downloadedItems << currentDownloadItem;

    currentDownload->deleteLater();
    currentDownload = nullptr;
    startNextDownload();
}

void DownloadManager::downloadReadyRead()
{
    if(!currentDownloadItem.filePath.isEmpty())
        output.write(currentDownload->readAll());
    else
        currentDownloadItem.data.append(currentDownload->readAll());
}

Logger *DownloadManager::getLogger() const
{
    return logger;
}

void DownloadManager::setLogger(Logger *value)
{
    logger = value;
}

void DownloadManager::logToLogger(Logger::Level level, const QString &message)
{
    if(logger != nullptr)
    {
        logger->log(level, "download-manager", "download-manager", "download", message);
    }
}

QList<DownloadManager::DownloadItem> DownloadManager::getDownloadedItems() const
{
    return downloadedItems;
}

void DownloadManager::cancelDownloads()
{
    downloadQueue.clear();

    if(currentDownload != nullptr && currentDownload->isRunning())
    {
        currentDownload->abort();
    }
}

void DownloadManager::clearDownloadedItems()
{
    downloadedItems.clear();
    totalCount = 0;
    downloadedCount = 0;
}

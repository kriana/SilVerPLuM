#pragma once

#include <QDir>
#include <QStringList>
#include <QStack>
#include <QFileInfo>
#include <QDebug>
#include <QLayout>
#include <QWidget>
#include <QtWidgets>
#include <QtConcurrent>
#include <QTextEdit>
#include <QtXml>
#include <sundown/src/markdown.h>
#include <sundown/html/html.h>
#include <sundown/src/buffer.h>

namespace utils
{

inline QString readAllTextFrom(const QString & path)
{
    QFile file(path);

    if(!file.open(QFile::ReadOnly | QFile::Text))
        return "";

    QTextStream stream(&file);
    return stream.readAll();
}

inline QString makeTextEditHTML(const QString & htmlbody)
{
    return "<html><head/><body>" + htmlbody + "</body></html>";
}

/**
 * @brief Took from https://github.com/sschober/qarkdown/blob/master/mainwindow.cpp
 * @param in
 * @return
 */
inline QString markdownToHTML(const QString & in)
{
    struct buf *ib, *ob;
    struct sd_callbacks cbs;
    struct html_renderopt opts;
    struct sd_markdown *mkd;

    if(in.size() > 0)
    {
        QByteArray qba = in.toUtf8();
        const char *txt = qba.constData();
        if(NULL == txt) qDebug() << "txt was null!";
        if(0 < qba.size())
        {
            ib = bufnew(qba.size());
            bufputs(ib,txt);
            ob = bufnew(64);
            sdhtml_renderer(&cbs,&opts,0);
            mkd = sd_markdown_new(0,16,&cbs,&opts);
            sd_markdown_render(ob,ib->data,ib->size,mkd);
            sd_markdown_free(mkd);
            return QString::fromUtf8(bufcstr(ob));
        }
        else
            qDebug() <<"qstrlen was null";
    }
    return "";
}

inline void moveTextCursorToEnd(QTextEdit * edit)
{
    QTextCursor newCursor(edit->document());
    newCursor.movePosition(QTextCursor::End);
    edit->setTextCursor(newCursor);
}

inline void clearLayout(QLayout * layout)
{
    QLayoutItem *item;

    while((item = layout->takeAt(0)) != nullptr)
    {
        if(item->layout() != nullptr)
        {
            clearLayout(item->layout());
        }
        if(item->widget() != nullptr)
        {
            item->widget()->hide();
            item->widget()->deleteLater();
        }
        if(item->spacerItem() != nullptr)
        {
            delete item->spacerItem();
        }
        else
        {
            delete item;
        }
    }
}

inline QStringList findAllFiles(const QDir & dir)
{
    QStringList result;
    QStack<QDir> todo;
    todo << dir;

    while(!todo.isEmpty())
    {
        QDir current = todo.pop();

        for(QString name : current.entryList(QDir::NoDotAndDotDot | QDir::Files))
        {
            result << current.absoluteFilePath(name);
        }
        for(QString name : current.entryList(QDir::NoDotAndDotDot | QDir::Dirs))
        {
            todo << QDir(current.absoluteFilePath(name));
        }
    }

    return result;
}

inline void copyDirectoryProgress(const QDir & from, const QDir & to, bool overwrite)
{
    qInfo() << from.absolutePath() << " --> " << to.absolutePath();

    QStringList files = findAllFiles(from);

    QProgressDialog dialog;
    dialog.setLabelText(QString("Copying %1 files...").arg(files.size()));

    QFutureWatcher<void> futureWatcher;
    QObject::connect(&futureWatcher, SIGNAL(finished()), &dialog, SLOT(reset()));
    QObject::connect(&dialog, SIGNAL(canceled()), &futureWatcher, SLOT(cancel()));
    QObject::connect(&futureWatcher, SIGNAL(progressRangeChanged(int,int)), &dialog, SLOT(setRange(int,int)));
    QObject::connect(&futureWatcher, SIGNAL(progressValueChanged(int)), &dialog, SLOT(setValue(int)));

    futureWatcher.setFuture(QtConcurrent::map(files, [&](const QString & src) {
        QString dst = to.absolutePath() + "/" + src.mid(from.absolutePath().size());

        //QFileInfo srcinfo(src);
        QFileInfo dstinfo(dst);

        qDebug() << src << " -> " << dst;

        // Delete directories or files that have the same name
        if(dstinfo.exists())
        {
            if(overwrite)
            {
                if(dstinfo.isDir())
                    QDir(dstinfo.absolutePath()).removeRecursively();
                else
                    QFile(dstinfo.absolutePath()).remove();
            }
            else
            {
                return;
            }
        }

        QDir parent = dstinfo.absoluteDir();

        if(!parent.exists())
            parent.mkpath(".");

        if(QFileInfo(dst).exists())
        {
            QFile(dst).remove();
        }

        QFile::copy(src, dst);
    }));

    // Display the dialog and start the event loop.
    dialog.exec();

    futureWatcher.waitForFinished();
}

inline void copyDirectory(const QDir & from, const QDir & to, bool overwrite)
{
    qInfo() << from.absolutePath() << " --> " << to.absolutePath();

    QStringList files = findAllFiles(from);

    for(QString src : files)
    {
        QString dst = to.absolutePath() + "/" + src.mid(from.absolutePath().size());

        //QFileInfo srcinfo(src);
        QFileInfo dstinfo(dst);

        qDebug() << src << " -> " << dst;

        // Delete directories or files that have the same name
        if(dstinfo.exists())
        {
            if(overwrite)
            {
                if(dstinfo.isDir())
                    QDir(dstinfo.absolutePath()).removeRecursively();
                else
                    QFile(dstinfo.absolutePath()).remove();
            }
            else
            {
                continue;
            }
        }

        QDir parent = dstinfo.absoluteDir();

        if(!parent.exists())
            parent.mkpath(".");

        if(QFileInfo(dst).exists())
        {
            QFile(dst).remove();
        }

        QFile::copy(src, dst);
    }
}

inline void clearDirectory(const QDir & dir)
{
    for(QString & file : dir.entryList(QDir::NoDotAndDotDot | QDir::Files))
    {
        QFile(dir.absoluteFilePath(file)).remove();
    }
    for(QString & file : dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs))
    {
        QDir(dir.absoluteFilePath(file)).removeRecursively();
    }
}

inline bool directoryEmpty(const QDir & dir)
{
    return dir.entryList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs).empty();
}

}

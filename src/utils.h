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
#include <sundown/src/html.h>
#include <sundown/src/buffer.h>
#include <QCryptographicHash>
#include <random>
#include "platform.h"
#include <QRegExp>
#include <QProcessEnvironment>

namespace utils
{

inline QString returnRelativeChildTo(const QDir & directory, const QString & path)
{
    QString relative = directory.relativeFilePath(path);

    if(relative == ".")
        return ".";

    if(relative.startsWith("../") || relative.startsWith("..\\"))
        return "";

    return relative;
}

inline QString toModURL(const QDir & directory, const QString & path, const QString & modid)
{
    QString relative = returnRelativeChildTo(directory, path);

    if(relative.isEmpty())
        return "";

    return modid + "://" + relative.replace("\\", "/");
}

inline QProcessEnvironment joinEnvironments(QProcessEnvironment env1, QProcessEnvironment env2)
{
    for(QString key : env2.keys())
    {
        env1.insert(key, env2.value(key));
    }

    return env1;
}

inline QStringList processEnvToList(const QProcessEnvironment & env)
{
    QStringList list;

    for(QString key : env.keys())
    {
        list << key + "=" + env.value(key);
    }

    return list;
}

inline QProcessEnvironment listToProcessEnv(const QStringList & values)
{
    QProcessEnvironment env;

    for(QString entry : values)
    {
        if(entry.contains("="))
        {
            QStringList cell = entry.split("=");

            if(cell.size() >= 2)
            {
                QString key = cell.takeFirst();
                env.insert(key, cell.join("="));
            }
        }
    }

    return env;
}

inline QString findFileInFileList(const QString & filename, const QStringList & filelist)
{
    for(QString f : filelist)
    {
        if(QFileInfo(f).fileName() == filename)
            return f;
    }

    return "";
}

inline QString makeValidModId(QString str)
{
    return str.trimmed().toLower().replace("..", "").replace(" ", "-").replace(QRegExp("[^a-z0-9_.\\-]+"), "");
}

inline bool isValidModId(QString id)
{
    return !id.isEmpty() && id.toLower() == id && !id.contains("..") && id.replace(QRegExp("[^a-z0-9_.\\-]+"), "") == id;
}

inline QString ArgumentListToString(QStringList list)
{
    QString result;

    bool first = true;

    for(QString str : list)
    {
        if(!first)
        {
            result += " ";            
        }
        else
        {
            first = false;
        }

        bool q = str.contains(" ");

        result += (q ? "\"" : "") + str.replace("\\", "\\\\").replace("\"", "\\\"") + (q ? "\"" : "");
    }

    return result;
}

/**
 * @brief Source: http://stackoverflow.com/questions/25068750/extract-parameters-from-string-included-quoted-regions-in-qt
 * @param cmdLine
 * @return
 */
inline QStringList stringToArgumentList(QString cmdLine)
{
    QStringList list;
    QString arg;
    bool escape = false;
    enum { Idle, Arg, QuotedArg } state = Idle;
    for(QChar c : cmdLine) {
        if (!escape && c == '\\') { escape = true; continue; }
        switch (state) {
        case Idle:
            if (!escape && c == '"') state = QuotedArg;
            else if (escape || !c.isSpace()) { arg += c; state = Arg; }
            break;
        case Arg:
            if (!escape && c == '"') state = QuotedArg;
            else if (escape || !c.isSpace()) arg += c;
            else { list << arg; arg.clear(); state = Idle; }
            break;
        case QuotedArg:
            if (!escape && c == '"') state = arg.isEmpty() ? Idle : Arg;
            else arg += c;
            break;
        }
        escape = false;
    }
    if (!arg.isEmpty()) list << arg;
    return list;
}

inline QString ecryptedContentEncryptPassword(const QString & password)
{
    if(password.isEmpty())
        return "";

    // Use STL random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 64);
    std::uniform_int_distribution<> dis2(0, 255);

    int start_index = dis(gen);

    QByteArray password_array = password.toUtf8();
    for(int i = 0; i < password_array.length(); ++i)
    {
        password_array[i] = ~password_array[i];
    }

    QByteArray res(start_index + password_array.length(), '\0');

    for(int i = 0; i < res.size(); ++i)
    {
        res[i] = dis2(gen);
    }

    res[0] = start_index;

    for(int i = 0; i < password_array.length(); ++i)
    {
        res[i + start_index] = password_array[i];
    }

    return QString(res.toHex());
}

inline QString encryptedContentDecryptPassword(const QString & epassword)
{
    if(epassword.isEmpty())
        return epassword;

    QByteArray password_array = QByteArray::fromHex(epassword.toUtf8());
    int start_index = password_array[0];

    if(start_index < 0 || start_index >= password_array.length())
        return "";

    QByteArray core(password_array.length() - start_index, '\0');
    for(int i = 0; i < core.length(); ++i)
    {
        core[i] = ~password_array[i + start_index];
    }

    return QString::fromUtf8(core);
}

inline void wrapMonoExecutable(QProcess * process, const QString & exectuable, const QStringList & arguments)
{
    if(Platform::getCurrentPlatform() != Platform::Windows)
    {
        if(exectuable.toLower().endsWith(".exe"))
        {
            // Wrap around mono
            process->setProgram("mono");

            QStringList new_args;
            new_args << exectuable << arguments;

            process->setArguments(new_args);
        }
        else
        {
            process->setProgram(exectuable);
            process->setArguments(arguments);
        }
    }
    else
    {
        process->setProgram(exectuable);
        process->setArguments(arguments);
    }
}

inline bool writeTextTo(const QString & path, const QString & content)
{
    QFile file(path);
    if(file.open(QFile::WriteOnly))
    {
        file.resize(0);
        QTextStream stream(&file);

        stream << content;
        file.close();

        return true;
    }
    else
    {
        return false;
    }
}

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
        //QString dst = to.absolutePath() + "/" + src.mid(from.absolutePath().size());
        QString dst = to.absolutePath() + "/" + from.relativeFilePath(src);

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
        //QString dst = to.absolutePath() + "/" + src.mid(from.absolutePath().size());
        QString dst = to.absolutePath() + "/" + from.relativeFilePath(src);

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

inline bool fileEqual(const QString & file1, const QString & file2)
{
    QFile f1(file1);
    QFile f2(file2);

    if(!f1.open(QFile::ReadOnly))
    {
        return false;
    }
    if(!f2.open(QFile::ReadOnly))
    {
        return false;
    }

    /*int s1 = f1.size();
    int s2 = f2.size();

    if(s1 != s2)
        return false;

    return f1.readAll() == f2.readAll();*/

    QByteArray h1 = QCryptographicHash::hash(f1.readAll(), QCryptographicHash::Sha1);
    QByteArray h2 = QCryptographicHash::hash(f2.readAll(), QCryptographicHash::Sha1);

    return h1 == h2;
}

inline bool folderEqual(const QDir & dir1, const QDir & dir2, const QStringList & excluded = QStringList())
{
    QStringList dir1_files = findAllFiles(dir1);
    QStringList dir2_files = findAllFiles(dir2);

    if(dir1_files.size() != dir2_files.size())
    {
        return false;
    }

    for(QString path : dir1_files)
    {
        //QString sub = path.mid(dir1.absolutePath().size() + 1);
        QString sub = dir1.relativeFilePath(path);

        if(excluded.contains(sub))
            continue;

        QString path2 = dir2.absolutePath() + "/" + sub;

        if(!fileEqual(path, path2))
            return false;
    }

    return true;
}

}

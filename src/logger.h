#ifndef LOGGER_H
#define LOGGER_H

#include <QtConcurrent>
#include <QString>
#include <QList>
#include <QTime>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>

class Logger
{
public:

    enum Level
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    struct Entry
    {
        Level level;
        QString component;
        QString subcomponent;
        QString operation;
        QString message;
        QTime timestamp = QTime::currentTime();

        QString toString()
        {
            QString msg;

            switch(level)
            {
            case DEBUG:
                msg += "[DEBUG]";
                break;
            case INFO:
                msg += "[INFO]";
                break;
            case WARNING:
                msg += "[WARNING]";
                break;
            case ERROR:
                msg += "[ERROR]";
                break;
            default:
                msg += "[???]";
                break;
            }

            msg += "\t" + component;
            msg += "\t" + subcomponent;
            msg += "\t" + operation;
            msg += "\t" + message;

            return msg;
        }

        void print()
        {
            switch(level)
            {
            case DEBUG:
                qDebug().noquote() << toString();
                break;
            case INFO:
                qInfo().noquote() << toString();
                break;
            case WARNING:
                qWarning().noquote() << toString();
                break;
            case ERROR:
                qCritical().noquote() << toString();
                break;
            default:
                qDebug().noquote() << toString();
                break;
            }
        }
    };

    Logger();

    void log(Level level, const QString & component, const QString & subcomponent, const QString & operation, const QString & message);

    void log(Level level, const QString & component, const QString & subcomponent, const QString & operation, const QStringList & message);

    void insert(const Logger & log);

private:

    QMutex m_mutex;

    QList<Entry> m_entries;
};

#endif // LOGGER_H

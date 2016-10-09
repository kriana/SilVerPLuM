#ifndef LOGGER_H
#define LOGGER_H

#include <QtConcurrent>
#include <QString>
#include <QList>
#include <QTime>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>

class Logger : public QObject
{
    Q_OBJECT

public:

    enum Level
    {
        Debug,
        Info,
        Warning,
        Error
    };

    struct Entry
    {
        Level level;
        QString component;
        QString subcomponent;
        QString operation;
        QString message;
        QTime timestamp = QTime::currentTime();

        QString levelToString() const
        {
            QString msg;

            switch(level)
            {
            case Debug:
                msg += "[DEBUG]";
                break;
            case Info:
                msg += "[INFO]";
                break;
            case Warning:
                msg += "[WARNING]";
                break;
            case Error:
                msg += "[ERROR]";
                break;
            default:
                msg += "[???]";
                break;
            }

            return msg;
        }

        QString toString() const
        {
            QString msg;

            msg += levelToString();

            msg += "\t" + component;
            msg += "\t" + subcomponent;
            msg += "\t" + operation;
            msg += "\t" + message;

            return msg;
        }

        void print() const
        {
            switch(level)
            {
            case Debug:
                qDebug().noquote() << toString();
                break;
            case Info:
                qInfo().noquote() << toString();
                break;
            case Warning:
                qWarning().noquote() << toString();
                break;
            case Error:
                qCritical().noquote() << toString();
                break;
            default:
                qDebug().noquote() << toString();
                break;
            }
        }
    };

    Logger(QObject * parent = 0);

    void log(Level level, const QString & component, const QString & subcomponent, const QString & operation, const QString & message);

    void log(Level level, const QString & component, const QString & subcomponent, const QString & operation, const QStringList & message);

    void insert(const Logger & log);

    QList<Entry> entries() const;

    void clear();

private:

    QMutex m_mutex;

    QList<Entry> m_entries;

signals:

    void logged(const Entry & entry);

    void loggedAsString(const QString & message);
};

Q_DECLARE_METATYPE(Logger::Entry)

#endif // LOGGER_H

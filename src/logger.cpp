#include "logger.h"

Logger::Logger(QObject *parent) : QObject(parent)
{

}

void Logger::log(Logger::Level level, const QString &component, const QString &subcomponent, const QString &operation, const QString &message)
{
    QMutexLocker _lock(&m_mutex);

    Entry e;
    e.level = level;
    e.component = component;
    e.subcomponent = subcomponent;
    e.operation = operation;
    e.message = message;

    e.print();

    m_entries << e;
    emit logged(e);
    emit loggedAsString(e.toString());
}

void Logger::log(Logger::Level level, const QString &component, const QString &subcomponent, const QString &operation, const QStringList &message)
{
    log(level,
        component,
        subcomponent,
        operation,
        message.join(" "));
}

void Logger::insert(const Logger &log)
{
    for(Entry e : log.m_entries)
    {
        m_entries << e;
    }

    std::sort(m_entries.begin(), m_entries.end(), [](const Entry & a, const Entry & b) {
       return a.timestamp < b.timestamp;
    });
}

QList<Logger::Entry> Logger::entries() const
{
    return QList<Entry>(m_entries);
}

void Logger::clear()
{
    m_entries.clear();
}

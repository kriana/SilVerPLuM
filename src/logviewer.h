#ifndef LOGVIEWER_H
#define LOGVIEWER_H

#include <QDialog>
#include "logger.h"
#include "profile.h"

namespace Ui {
class LogViewer;
}

class LogViewer : public QDialog
{
    Q_OBJECT

public:
    explicit LogViewer(QWidget *parent = 0);
    ~LogViewer();

    void setLogger(const Logger & logger);

    static void execForProfile(Profile * p);

private slots:

    void copyClicked();

private:
    Ui::LogViewer *ui;

    QString m_logText;

    QString formatEntry(const Logger::Entry & entry);


};

#endif // LOGVIEWER_H

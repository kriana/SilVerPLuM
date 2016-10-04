#ifndef FILESELECTOREDIT_H
#define FILESELECTOREDIT_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class FileSelectorEdit;
}

class FileSelectorEdit : public QWidget
{
    Q_OBJECT

public:
    explicit FileSelectorEdit(QWidget *parent = 0);
    ~FileSelectorEdit();

    QString getCurrentPath();

    void setCurrentPath(const QString & path);

    QFileDialog * getFileDialog();

    void setReadOnly(bool readonly);

private:
    Ui::FileSelectorEdit *ui;
    QFileDialog *m_fileDialog;

public slots:

    void triggerDialog();

    void triggerOpen();

signals:

    void changed();
};

#endif // FILESELECTOREDIT_H

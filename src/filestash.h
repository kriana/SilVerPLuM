#ifndef FILESTASH_H
#define FILESTASH_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class FileStash;
}

class FileStash : public QWidget
{
    Q_OBJECT

public:
    explicit FileStash(QWidget *parent = 0);
    ~FileStash();

    void addFiles(const QStringList & files);

    QStringList getFiles();

signals:

    void changed();

private slots:

    void addFiles();

    void removeSelection();

private:
    Ui::FileStash *ui;
    QFileDialog m_fileDialog;
};

#endif // FILESTASH_H

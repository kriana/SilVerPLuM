#include "filestash.h"
#include "ui_filestash.h"
#include <QToolButton>
#include <QTreeWidget>
#include <QApplication>

FileStash::FileStash(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileStash)
{
    ui->setupUi(this);

    connect(ui->btnAddFiles, SIGNAL(clicked(bool)), this, SLOT(addFiles()));
    connect(ui->btnRemoveFiles, &QToolButton::clicked, this, &FileStash::removeSelection);

    m_fileDialog.setFileMode(QFileDialog::ExistingFiles);
}

FileStash::~FileStash()
{
    delete ui;
}

void FileStash::addFiles(const QStringList &files)
{
    QStringList exisiting = getFiles();

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    for(QString file : files)
    {
        if(!exisiting.contains(file))
        {
            ui->fileList->addTopLevelItem(new QTreeWidgetItem(ui->fileList,
                                                              QStringList() <<
                                                              QFileInfo(file).fileName()
                                                              << file.replace("\\","/")));
        }
    }

    QApplication::restoreOverrideCursor();
}

QStringList FileStash::getFiles()
{
    QStringList files;

    for(int i = 0; i < ui->fileList->topLevelItemCount(); ++i)
    {
        files << ui->fileList->topLevelItem(i)->data(1, Qt::DisplayRole).toString();
    }

    return files;
}

void FileStash::addFiles()
{
    if(m_fileDialog.exec() == QFileDialog::Accepted)
    {
        addFiles(m_fileDialog.selectedFiles());
    }
}

void FileStash::removeSelection()
{
    for(QTreeWidgetItem * sel : ui->fileList->selectedItems())
    {
        delete sel;
    }
}

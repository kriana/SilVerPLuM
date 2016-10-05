#include "fileselectoredit.h"
#include "ui_fileselectoredit.h"
#include <QDesktopServices>

FileSelectorEdit::FileSelectorEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSelectorEdit)
{
    ui->setupUi(this);
    m_fileDialog = new QFileDialog(this);

    connect(ui->pathSelect, &QToolButton::clicked, this, &FileSelectorEdit::triggerDialog);
    connect(ui->pathOpen, &QToolButton::clicked, this, &FileSelectorEdit::triggerOpen);
    connect(ui->pathEdit, SIGNAL(textChanged(QString)), this, SIGNAL(changed()));
    connect(ui->pathEdit, SIGNAL(textChanged(QString)), this, SLOT(checkPath(QString)));
}

FileSelectorEdit::~FileSelectorEdit()
{
    delete m_fileDialog;
    delete ui;
}

QString FileSelectorEdit::getCurrentPath()
{
    return ui->pathEdit->text();
}

void FileSelectorEdit::setCurrentPath(const QString &path)
{
    ui->pathEdit->setText(path);
}

QFileDialog *FileSelectorEdit::getFileDialog()
{
    return m_fileDialog;
}

void FileSelectorEdit::setReadOnly(bool readonly)
{
    ui->pathEdit->setReadOnly(readonly);
    ui->pathSelect->setEnabled(!readonly);
}

void FileSelectorEdit::checkPath(const QString &path)
{
    QFileInfo info(path);

    ui->pathNotFound->setVisible(!info.exists());
}

void FileSelectorEdit::triggerDialog()
{
    m_fileDialog->setDirectory(getCurrentPath());
    if(m_fileDialog->exec() == QDialog::Accepted)
    {
        setCurrentPath(m_fileDialog->selectedFiles().first());
    }
}

void FileSelectorEdit::triggerOpen()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(getCurrentPath()));
}

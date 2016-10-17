#include "externalprogramsettingswidget.h"
#include "ui_externalprogramsettingswidget.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QMessageBox>
#include <QLabel>
#include <QAction>
#include <QToolButton>
#include "utils.h"
#include <QFileDialog>

ExternalProgramSettingsWidget::ExternalProgramSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExternalProgramSettingsWidget)
{
    ui->setupUi(this);

    connect(ui->programId, SIGNAL(textChanged(QString)), this, SIGNAL(changed()));
    connect(ui->programExecutable, SIGNAL(changed()), this, SIGNAL(changed()));
    connect(ui->programMimeTypes, SIGNAL(textChanged(QString)), this, SIGNAL(changed()));
    connect(ui->programArguments, SIGNAL(textChanged(QString)), this, SIGNAL(changed()));
    connect(ui->programRunnable, SIGNAL(toggled(bool)), this, SIGNAL(changed()));

    connect(ui->programId, SIGNAL(textChanged(QString)), ui->lblIdentifier, SLOT(setText(QString)));
    connect(ui->programExecutable, SIGNAL(changed()), this, SLOT(checkIfProgramExists()));

    connect(ui->actionRemove, &QAction::triggered, this, &ExternalProgramSettingsWidget::removeEntry);
    connect(ui->btnShowSettings, SIGNAL(toggled(bool)), ui->expandingWidget, SLOT(setVisible(bool)));
    connect(ui->btnAddMimeType, &QToolButton::clicked, this, &ExternalProgramSettingsWidget::addMimeType);

    QMenu * menu = new QMenu(ui->btnShowSettings);
    menu->addAction(ui->actionRemove);
    ui->btnShowSettings->setMenu(menu);

    ui->lblIdentifier->setText("");
    ui->expandingWidget->hide();
}

ExternalProgramSettingsWidget::~ExternalProgramSettingsWidget()
{
    delete ui;
}

ExternalProgram ExternalProgramSettingsWidget::getExternalProgram()
{
    ExternalProgram program;

    program.setExecutablePath(ui->programExecutable->getCurrentPath());
    program.setArguments(utils::stringToArgumentList(ui->programArguments->text()));
    program.setRunnable(ui->programRunnable->isChecked());
    program.setRuntimeMimeTypes(utils::stringToArgumentList(ui->programMimeTypes->text()));

    return program;
}

QString ExternalProgramSettingsWidget::getExternalProgramId()
{
    return ui->programId->text();
}

void ExternalProgramSettingsWidget::fillWith(const QString &programid)
{
    ui->programId->setText(programid);

    ExternalProgram program = GlobalSettings::instance()->getExternalProgram(programid);

    if(program.isEmpty())
    {
        hide();
        return;
    }

    ui->programExecutable->setCurrentPath(program.executablePath());
    ui->programArguments->setText(utils::ArgumentListToString(program.arguments()));
    ui->programMimeTypes->setText(utils::ArgumentListToString(program.runtimeMimeTypes()));
    ui->programRunnable->setChecked(program.runnable());

    ui->lblIdentifier->setText(programid);
    checkIfProgramExists();
}

void ExternalProgramSettingsWidget::removeEntry()
{
    if(QMessageBox::question(this, "Remove entry", "Do you really want to do this? Some mods or parts of this application might need this program.") == QMessageBox::Yes)
    {
        ui->programId->setText("");
        this->hide();

        emit changed();
    }
}

void ExternalProgramSettingsWidget::checkIfProgramExists()
{
    bool exists = false;

    if(!ui->programExecutable->getCurrentPath().isEmpty())
    {
        exists = QFileInfo(ui->programExecutable->getCurrentPath()).exists() && QFileInfo(ui->programExecutable->getCurrentPath()).isFile();
    }

    ui->lblWarning->setVisible(!exists);
}

void ExternalProgramSettingsWidget::addMimeType()
{
    QFileDialog dlg;
    dlg.setFileMode(QFileDialog::ExistingFiles);

    QSet<QString> mimetypes = QSet<QString>::fromList(utils::stringToArgumentList(ui->programMimeTypes->text()));

    QMimeDatabase mimedb;

    if(dlg.exec() == QFileDialog::Accepted)
    {
        for(QString file : dlg.selectedFiles())
        {
            QMimeType mime = mimedb.mimeTypeForFile(file);

            QString extension;
            if(file.contains("."))
                extension = file.split(".").last();

            mimetypes << mime.name() + (extension.isEmpty() ? "" : "&." + extension);
        }
    }

    ui->programMimeTypes->setText(utils::ArgumentListToString(mimetypes.toList()));
}

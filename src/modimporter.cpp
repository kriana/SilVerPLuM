#include "modimporter.h"
#include "ui_modimporter.h"
#include <QLayout>
#include <QGroupBox>
#include <QMessageBox>
#include "modimportercontentitem.h"
#include <QTemporaryDir>
#include <QDesktopServices>
#include <QJsonObject>
#include <QJsonDocument>
#include "utils.h"
#include "profile.h"
#include "profilemanager.h"
#include <QFileDialog>
#include <JlCompress.h>

ModImporter::ModImporter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModImporter)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);

    addContent()->setExpanded(true);

    for(QString version : Profile::StardewValleyVersions())
    {
        ui->modRequiresStardewValley->addItem(version);
    }

    connect(ui->btnImport, SIGNAL(clicked(bool)), this, SLOT(import()));
    connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btnAddContent, SIGNAL(clicked(bool)), this, SLOT(addContent()));
    connect(ui->modName, SIGNAL(textChanged(QString)), this, SLOT(nameChanged(QString)));

    connect(ui->btnImportDirectory, &QPushButton::clicked, this, &ModImporter::importDirectoryClicked);
    connect(ui->btnImportZip, &QPushButton::clicked, this, &ModImporter::importZipClicked);
    connect(ui->btnImportManually, &QPushButton::clicked, this, &ModImporter::importManuallyClicked);

    ui->toolBox->setCurrentWidget(ui->infoPage);
}

ModImporter::~ModImporter()
{
    delete ui;
}

void ModImporter::removeContent(ModImporterContentItem *item)
{
    if(m_contentItems.contains(item))
    {
        m_contentItems.removeAll(item);
        item->hide();
        item->deleteLater();
    }
}

QString ModImporter::findNewContentId()
{
    for(int i = 1; true; ++i)
    {
        QString id = "content" + QString::number(i);

        if(getContent(id) == nullptr)
            return id;
    }

    return "";
}

ModImporterContentItem *ModImporter::getContent(const QString &id)
{
    for(ModImporterContentItem * item : m_contentItems)
    {
        if(item->getContentId() == id)
            return item;
    }

    return nullptr;
}

void ModImporter::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this, "Close", "Do you really want to close this window? You will loose all your settings.") == QMessageBox::No)
    {
        event->setAccepted(false);
    }
    else
    {
        QDialog::closeEvent(event);
    }
}

ModImporterContentItem * ModImporter::addContent()
{
    QLayout * layout = ui->contentItems->layout();
    ModImporterContentItem * item = new ModImporterContentItem(this);
    layout->addWidget(item);
    m_contentItems << item;

    return item;
}

void ModImporter::import()
{
    if(!isValid())
    {
        QMessageBox::critical(this, "Import", "There's invalid information in the mod settings. Cannot import.");
        return;
    }
    QStringList existingids;
    for(ModImporterContentItem * content : m_contentItems)
    {
        if(existingids.contains(content->getContentId()))
        {
            QMessageBox::critical(this, "Import", "There are duplicate content identifiers. Cannot import.");
            return;
        }
        if(!content->isValid())
        {
            QMessageBox::critical(this, "Import", "There's invalid information in a content entry. Cannot import.");
            return;
        }

        existingids << content->getContentId();
    }

    QTemporaryDir temp;
    temp.setAutoRemove(false);

    if(temp.isValid())
    {
        QDir tempdir = temp.path();
        tempdir.mkpath(".");

        QJsonObject root;

        root["id"] = ui->modIdentifier->text();
        root["name"] = ui->modName->text();
        root["author"] = ui->modAuthor->text();
        root["license"] = ui->modLicense->currentText();
        root["url"] = ui->modWebsite->text();
        root["version"] = QVersionNumber::fromString(ui->modVersion->text()).toString();
        root["requires"] = QJsonArray({"stardewvalley=" + ui->modRequiresStardewValley->currentText()});

        QJsonArray categories;

        for(QString cat : utils::stringToArgumentList(ui->modCategories->text()))
        {
            if(!cat.isEmpty())
            {
                categories << cat;
            }
        }

        root["categories"] = categories;

        QJsonObject content_list;

        for(ModImporterContentItem * content : m_contentItems)
        {
            QJsonObject entry = content->build(tempdir);
            content_list[content->getContentId()] = entry;
        }

        root["content"] = content_list;

        QJsonDocument doc(root);
        QString doc_json = doc.toJson();

        utils::writeTextTo(tempdir.absoluteFilePath("mod.json"), doc_json);
        utils::writeTextTo(tempdir.absoluteFilePath("mod-description.md"), ui->modDescription->document()->toPlainText());

        // Now ask what to do
        while(true)
        {
            QMessageBox dlg;
            dlg.setText("Import");
            dlg.setInformativeText("The mod has been successfully built. What do you want to do?");
            dlg.setStandardButtons(QMessageBox::Open | QMessageBox::Ok | QMessageBox::Cancel);
            dlg.setButtonText(QMessageBox::Open, "Open result directory");
            dlg.setButtonText(QMessageBox::Ok, "Import");

            int ret = dlg.exec();

            if(ret == QMessageBox::Open)
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile(tempdir.absolutePath()));
            }
            else if(ret == QMessageBox::Ok)
            {
                if(ProfileManager::instance()->getSelectedProfile()->getModManager()->importModFromDirectory(tempdir))
                    this->close();

                break;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        QMessageBox::critical(this, "Import", "Could not create temporary directory!");
    }
}

void ModImporter::nameChanged(const QString &text)
{
    ui->modIdentifier->setText(text);
}

void ModImporter::importManuallyClicked()
{
    ui->toolBox->setCurrentWidget(ui->modInfoPage);
}

void ModImporter::importZipClicked()
{
    QFileDialog dlg;
    dlg.setFileMode(QFileDialog::ExistingFile);
    dlg.setMimeTypeFilters(QStringList() << "application/zip" << "application/octet-stream");

    if(dlg.exec() == QFileDialog::Accepted)
    {
        QTemporaryDir tempdir;
        tempdir.setAutoRemove(false);

        if(tempdir.isValid())
        {
            QStringList extracted = JlCompress::extractDir(dlg.selectedFiles().first(), tempdir.path());

            if(extracted.isEmpty())
            {
                QMessageBox::critical(nullptr, "Import *.zip", "Extraction of file failed!");
                return;
            }

            importDirectory(tempdir.path(), QFileInfo(dlg.selectedFiles().first()).baseName());
        }
        else
        {
            QMessageBox::critical(nullptr, "Import *.zip", "Could not create temporary directory!");
            return;
        }
    }
}

void ModImporter::importDirectoryClicked()
{
    QFileDialog dlg;
    dlg.setFileMode(QFileDialog::DirectoryOnly);

    if(dlg.exec() == QFileDialog::Accepted)
    {
        importDirectory(dlg.selectedFiles().first(), QDir(dlg.selectedFiles().first()).dirName());
    }
}

bool ModImporter::isValid()
{
    if(ui->modIdentifier->text().isEmpty())
        return false;
    if(ui->modName->text().isEmpty())
        return false;
    if(ui->modAuthor->text().isEmpty())
        return false;
    if(ui->modLicense->currentText().isEmpty())
        return false;
    if(m_contentItems.isEmpty())
        return false;

    return true;
}

void ModImporter::importDirectory(const QDir &dir, QString name)
{
    // If it's valid, add instead of replace
    if(!isValid())
    {
        // Clean up
        while(!m_contentItems.isEmpty())
            removeContent(m_contentItems.first());

        // Determine name
        name = name.replace("-", " ");
        ui->modName->setText(name);
        ui->modIdentifier->setText(ProfileManager::instance()->getSelectedProfile()->getModManager()->unifyModId(name));
        ui->modAuthor->setText("Unknown");
        ui->modLicense->setCurrentText("Unknown");
    }

    // Find all mod files
    QDir contentdir = ProfileManager::instance()->getSelectedProfile()->StardewValleyContentDir();
    QStringList mod_files = utils::findAllFiles(dir);
    QStringList content_files = utils::findAllFiles(contentdir);
    QStringList unprocessed = QStringList(mod_files);

    // Content replacer mods
    for(QString file : mod_files)
    {
        if(file.endsWith(".xnb"))
        {
            QString path_in_content = utils::findFileInFileList(QFileInfo(file).fileName(), content_files);

            if(!path_in_content.isEmpty())
            {
                QString in_content_dir = QFileInfo(path_in_content).absolutePath();
                QString install_path = "stardewvalley-content://" + contentdir.relativeFilePath(in_content_dir);

                ModImporterContentItem * item = getOrCreateContentWithInstallPath(install_path);
                item->addFiles(QStringList() << file);
                item->setContentName("Installs into Content/" + contentdir.relativeFilePath(in_content_dir));

                unprocessed.removeAll(file);
            }
        }
    }

    // DLL mods
    for(QString file : mod_files)
    {
        if(file.endsWith(".dll"))
        {
            QString name = QFileInfo(file).baseName();
            QDir containingdir = QFileInfo(file).absolutePath();

            QStringList toadd = utils::findAllFiles(containingdir);

            ModImporterContentItem * item = addContent();
            item->setInstallDir("stardewvalley://Mods/" + name);
            item->setContentName("SMAPI-Mod " + name);

            item->addFiles(toadd);

            for(QString f : toadd)
            {
                unprocessed.removeAll(f);
            }
        }
    }

    QMessageBox::information(this, "Import automatically", "The files have been inserted into the mod importer. Check if everything is corrent and click 'Import' to finalize the process.");

    if(unprocessed.isEmpty())
    {
        ui->messageWidget->hide();
    }
    else
    {
        ui->messageWidget->message("Could not insert all files. Following files are affected: \n• " + unprocessed.join("\n• "));
    }

    if(ui->modDescription->document()->toPlainText().isEmpty())
    {
        ui->modDescription->document()->setPlainText("Created with SilVerPLuM automatic mod importer.");
    }
}

ModImporterContentItem *ModImporter::getOrCreateContentWithInstallPath(const QString &installpath)
{
    for(ModImporterContentItem * item : m_contentItems)
    {
        if(item->getInstallDir() == installpath)
            return item;
    }

    ModImporterContentItem * item = addContent();
    item->setInstallDir(installpath);

    return item;
}

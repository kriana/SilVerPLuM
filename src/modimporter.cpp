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

    ui->toolBox->setCurrentWidget(ui->modInfoPage);
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

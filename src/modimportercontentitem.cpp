#include "modimportercontentitem.h"
#include "ui_modimportercontentitem.h"
#include "modmanager.h"
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QMessageBox>
#include "modimporter.h"
#include "utils.h"

ModImporterContentItem::ModImporterContentItem(ModImporter * importer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModImporterContentItem),
    m_importer(importer)
{
    ui->setupUi(this);

    ui->contentInstallTo->addItems(QStringList() << "Content"
                                   << "Content/Animals"
                                   << "Content/Buildings"
                                   << "Content/Characters"
                                   << "Content/Data"
                                   << "Content/Fonts"
                                   << "Content/LooseSprites"
                                   << "Content/Maps"
                                   << "Content/Mines"
                                   << "Content/Minigames"
                                   << "Content/Portraits"
                                   << "Content/Strings"
                                   << "Content/TerrainFeatures"
                                   << "Content/TileSheets"
                                   << "Content/XACT");
    for(QString modid : ModManager::FORBIDDEN_MOD_IDS)
    {
        ui->contentInstallTo->addItem(modid + "://");
    }

    ui->contentId->setText(importer->findNewContentId());
    ui->contentName->setText("Mod content");

    connect(ui->btnDelete, SIGNAL(clicked(bool)), this, SLOT(remove()));
}

ModImporterContentItem::~ModImporterContentItem()
{
    delete ui;
}

bool ModImporterContentItem::isValid()
{
    if(ui->contentId->text().isEmpty())
        return false;
    if(ui->contentName->text().isEmpty())
        return false;
    if(ui->contentFiles->getFiles().isEmpty())
        return false;

    return true;
}

QString ModImporterContentItem::getContentId()
{
    return ui->contentId->text();
}

QJsonObject ModImporterContentItem::build(const QDir &modbasepath)
{
    QString contentid = getContentId();

    if(contentid.isEmpty())
        return QJsonObject();
    if(ui->contentName->text().isEmpty())
        return QJsonObject();
    if(ui->contentFiles->getFiles().isEmpty())
        return QJsonObject();

    QDir contentbasepath = modbasepath.absoluteFilePath(ui->contentId->text());
    contentbasepath.mkpath(".");

    QJsonObject json_entry = QJsonObject({
                                             { "name", ui->contentName->text() },
                                             { "default", ui->contentIsDefault->isChecked() },
                                             { "priority", ui->contentPriority->value() },
                                             { "pipeline", "file" },
                                             { "platforms", QJsonArray({ "windows", "linux", "mac" }) }
                                         });


    if(!ui->contentDescription->document()->toPlainText().isEmpty())
    {
        utils::writeTextTo(contentbasepath.absoluteFilePath("mod-description.md"), ui->contentDescription->document()->toPlainText());
    }

    //QJsonObject installables_json = content_entry["installables"].toObject();
    QJsonObject installables_json = QJsonObject();

    QString path_prefix = ui->contentInstallTo->currentText();

    for(QString file : ui->contentFiles->getFiles())
    {
        QString filename = QFileInfo(file).fileName();
        if(QFile::copy(file, contentbasepath.absoluteFilePath(filename)))
        {
            installables_json[filename] =  path_prefix + "/" + filename;
        }

    }

    json_entry["installables"] = installables_json;

    return json_entry;
}

void ModImporterContentItem::remove()
{
    if(QMessageBox::question(this, "Remove content", "Do you really want to remove this content?") == QMessageBox::Yes)
    {
        m_importer->removeContent(this);
    }
}

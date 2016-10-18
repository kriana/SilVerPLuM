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

    ui->contentInstallTo->addItems(QStringList() << "stardewvalley-content://"
                                   << "stardewvalley-content://Animals"
                                   << "stardewvalley-content://Buildings"
                                   << "stardewvalley-content://Characters"
                                   << "stardewvalley-content://Data"
                                   << "stardewvalley-content://Fonts"
                                   << "stardewvalley-content://LooseSprites"
                                   << "stardewvalley-content://Maps"
                                   << "stardewvalley-content://Mines"
                                   << "stardewvalley-content://Minigames"
                                   << "stardewvalley-content://Portraits"
                                   << "stardewvalley-content://Strings"
                                   << "stardewvalley-content://TerrainFeatures"
                                   << "stardewvalley-content://TileSheets"
                                   << "stardewvalley-content://XACT");
    for(QString modid : ModManager::FORBIDDEN_MOD_IDS)
    {
        ui->contentInstallTo->addItem(modid + "://");
    }

    ui->contentId->setText(importer->findNewContentId());
    ui->contentName->setText("Mod content");

    QMenu * menu = new QMenu(ui->btnShowSettings);
    menu->addAction(ui->actionRemove);
    ui->btnShowSettings->setMenu(menu);

    connect(ui->actionRemove, SIGNAL(triggered(bool)), this, SLOT(remove()));
    connect(ui->btnShowSettings, SIGNAL(toggled(bool)), ui->expandWidget, SLOT(setVisible(bool)));
    connect(ui->contentId, SIGNAL(textChanged(QString)), this, SLOT(updateInformationLabel()));
    connect(ui->contentName, SIGNAL(textChanged(QString)), this, SLOT(updateInformationLabel()));
    connect(ui->contentFiles, SIGNAL(changed()), this, SLOT(updateInformationLabel()));

    updateInformationLabel();

    ui->expandWidget->hide();
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
            installables_json[filename] =  path_prefix.replace("\\", "/") + "/" + filename;
        }

    }

    json_entry["installables"] = installables_json;

    return json_entry;
}

void ModImporterContentItem::setExpanded(bool expand)
{
    ui->btnShowSettings->setChecked(expand);
}

void ModImporterContentItem::addFiles(const QStringList &files)
{
    ui->contentFiles->addFiles(files);
}

void ModImporterContentItem::setInstallDir(const QString &dir)
{
    ui->contentInstallTo->setCurrentText(dir);
}

void ModImporterContentItem::updateInformationLabel()
{
    QString id = ui->contentId->text().isEmpty() ? "<No ID>" : ui->contentId->text();
    QString name = ui->contentName->text().isEmpty() ? "<Unnamed>" : ui->contentName->text();
    int filecount = ui->contentFiles->getFiles().size();

    ui->lblInformation->setText(QString("%1 (%2) - %3 files").arg(name).arg(id).arg(QString::number(filecount)));
}

void ModImporterContentItem::remove()
{
    if(QMessageBox::question(this, "Remove content", "Do you really want to remove this content?") == QMessageBox::Yes)
    {
        m_importer->removeContent(this);
    }
}

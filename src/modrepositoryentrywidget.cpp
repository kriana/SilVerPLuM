#include "modrepositoryentrywidget.h"
#include "ui_modrepositoryentrywidget.h"
#include <QPushButton>
#include <QLabel>
#include "modrepository.h"
#include "modmanager.h"
#include "utils.h"

ModRepositoryEntryWidget::ModRepositoryEntryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModRepositoryEntryWidget)
{
    ui->setupUi(this);

    connect(ui->btnShowMore, SIGNAL(toggled(bool)), ui->expandWidget, SLOT(setVisible(bool)));
    connect(ui->btnInstall, SIGNAL(clicked(bool)), this, SLOT(installClicked()));
    ui->expandWidget->hide();
}

ModRepositoryEntryWidget::~ModRepositoryEntryWidget()
{
    delete ui;
}

void ModRepositoryEntryWidget::setRepositoryEntry(ModRepositoryEntry *entry)
{
    m_currentEntry = entry;

    Modification * installed = entry->getInstalledMod();

    if(installed == nullptr)
    {
        ui->btnInstall->setText(tr("Install"));
        ui->btnInstall->setToolTip(tr("Will install this modification. Will download " + entry->modDownloadURL().toEncoded()));
        ui->lblStatus->setText("");
        m_updatesModification = false;
    }
    else
    {
        if(entry->modification()->version() < installed->version())
        {
            ui->btnInstall->setText(tr("Downgrade"));
            ui->btnInstall->setToolTip(tr("Will downgrade this modification to an older version. Will download " + entry->modDownloadURL().toEncoded()));
            ui->lblStatus->setText("");
            m_updatesModification = false;
        }
        else if(entry->modification()->version() == installed->version())
        {
            ui->btnInstall->setText(tr("Reinstall"));
            ui->btnInstall->setToolTip(tr("Will reinstall this modification. Will download " + entry->modDownloadURL().toEncoded()));
            ui->lblStatus->setText("");
            m_updatesModification = false;
        }
        else
        {
            ui->btnInstall->setText(tr("Update"));
            ui->btnInstall->setToolTip(tr("Will update this modification to a newer version. Will download " + entry->modDownloadURL().toEncoded()));
            ui->lblStatus->setText(tr("Update found"));
            m_updatesModification = true;
        }
    }

    ui->lblName->setText(entry->modification()->name());
    ui->lblAuthor->setText("by " + entry->modification()->author());
    ui->lblIcon->setPixmap(entry->icon());
    ui->lblIdentifier->setText(entry->modification()->id());
    ui->lblVersion->setText("Version " + entry->modification()->version().toString());
    ui->lblLicense->setText(entry->modification()->license());
    ui->lblWebsite->setText(QString("<html><head/><body><p><a href=\"%1\"><span style=\" text-decoration: underline; color:#4c6b8a;\">Website</span></a></p></body></html>")
                            .arg(entry->modification()->url()));
    ui->lblWebsite->setToolTip(entry->modification()->url());
    ui->lblRepositoryWebsite->setText(QString("<html><head/><body><p><a href=\"%1\"><span style=\" text-decoration: underline; color:#4c6b8a;\">Repository source</span></a></p></body></html>")
                            .arg(QString::fromUtf8(entry->getRepositorySource()->repositoryURL().toEncoded())));
    ui->lblRepositoryWebsite->setToolTip(QString::fromUtf8(entry->getRepositorySource()->repositoryURL().toEncoded()));
    ui->lblRepositoryInfo->setText(QString("In '%1' maintained by %2").arg(entry->getRepositorySource()->repositoryName()).arg(entry->getRepositorySource()->maintainer()));
    ui->lblRepositoryInfo->setToolTip(entry->getRepositorySource()->repositoryDescription());
    ui->lblDescription->setText(utils::makeTextEditHTML(utils::markdownToHTML(entry->repository()->getModManager()->autoResolveModUrls(entry->modification()->description()))));
}

ModRepositoryEntry *ModRepositoryEntryWidget::currentEntry() const
{
    return m_currentEntry;
}

void ModRepositoryEntryWidget::installClicked()
{
    m_currentEntry->repository()->install(QList<ModRepositoryEntry*>() << m_currentEntry, m_updatesModification);
}

#include "modmanagerwidgetitem.h"
#include "ui_modmanagerwidgetitem.h"
#include "utils.h"
#include "modmanagerwidgetpipelineitem.h"
#include "modmanager.h"
#include <QPixmap>
#include <QMenu>
#include "profilemanager.h"
#include "logviewer.h"
#include "activatemoddialog.h"

ModManagerWidgetItem::ModManagerWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModManagerWidgetItem)
{
    ui->setupUi(this);

    QMenu *action_menu = new QMenu(ui->btnDelete);
    action_menu->addActions(QList<QAction*>() << ui->actionCopyToProfile << ui->actionReinitialize << ui->actionExportMod << ui->actionOpenDirectory);
    ui->btnDelete->setMenu(action_menu);

    connect(ui->btnShowMore, SIGNAL(toggled(bool)), this, SLOT(showMoreToggled(bool)));
    connect(ui->btnEnableDefaults, &QPushButton::clicked, this,&ModManagerWidgetItem::enableClicked);
    connect(ui->btnDisableAll, &QPushButton::clicked, this, &ModManagerWidgetItem::disableClicked);
    connect(ui->btnSortUp, &QToolButton::clicked, this, &ModManagerWidgetItem::moveUpClicked);
    connect(ui->btnSortDown, &QToolButton::clicked, this, &ModManagerWidgetItem::moveDownClicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &ModManagerWidgetItem::deleteClicked);
    connect(ui->actionCopyToProfile, &QAction::triggered, this, &ModManagerWidgetItem::copyToProfileClicked);
    connect(ui->actionReinitialize, &QAction::triggered, this, &ModManagerWidgetItem::reprimeClicked);
    connect(ui->actionExportMod, &QAction::triggered, this, &ModManagerWidgetItem::exportClicked);
    connect(ui->actionOpenDirectory, &QAction::triggered, this, &ModManagerWidgetItem::openDirectoryClicked);

    ui->expandWidget->hide();
}

ModManagerWidgetItem::~ModManagerWidgetItem()
{
    delete ui;
}

void ModManagerWidgetItem::setCurrentModification(Modification *mod)
{
    if(m_currentModification != nullptr)
    {
        disconnect(m_currentModification,
                   SIGNAL(contentEnabledDisabled(QString,bool)),
                   this,
                   SLOT(contentEnabledDisabled(QString,bool)));
    }

    m_currentModification = mod;

    if(mod != nullptr)
    {
        connect(m_currentModification,
                   SIGNAL(contentEnabledDisabled(QString,bool)),
                   this,
                   SLOT(contentEnabledDisabled(QString,bool)));
        updateData();
    }
}

void ModManagerWidgetItem::setCollapsed(bool enabled)
{
    ui->expandWidget->setVisible(!enabled && ui->btnShowMore->isChecked());
    ui->mainWidget->setVisible(!enabled);
}

void ModManagerWidgetItem::searchFilter(const QString &searchstring, const QString &category)
{
    bool visible = true;

    if(!searchstring.isEmpty())
    {
        visible &= m_currentModification->search(searchstring);
    }
    if(!category.isEmpty())
    {
        visible &= m_currentModification->isInCategory(category);
    }

    setCollapsed(!visible);
}

void ModManagerWidgetItem::showMoreToggled(bool toggle)
{
    ui->expandWidget->setVisible(toggle);
}

void ModManagerWidgetItem::contentEnabledDisabled(const QString &contentid, bool enabled)
{
    if(m_currentModification != nullptr)
    {
        QList<Pipeline*> enabled_pipelines = m_currentModification->getEnabledPipelines();

        ui->btnDisableAll->setVisible(enabled_pipelines.size() > 0);
        ui->btnEnableDefaults->setVisible(enabled_pipelines.empty());

        if(enabled_pipelines.empty())
        {
            ui->lblIcon->setEnabled(false);
            ui->lblStatus->setText("");
        }
        else
        {
            ui->lblIcon->setEnabled(true);
            ui->lblStatus->setText(QString("%1 modules enabled").arg(enabled_pipelines.size()));
        }
    }
}

void ModManagerWidgetItem::enableClicked()
{
    if(m_currentModification != nullptr)
    {
        ActivateModDialog dlg;
        dlg.activateModification(m_currentModification);

        /*QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        int err = m_currentModification->enableDefaults();

        QApplication::restoreOverrideCursor();

        while(err != 0)
        {
            QMessageBox msg;
            msg.setText("Enable default modifications");
            msg.setInformativeText("An error happened while activating the mod. What do you want to do?");
            msg.setStandardButtons(QMessageBox::Ignore | QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Open);
            msg.setButtonText(QMessageBox::Abort, "Deactivate mod");
            msg.setButtonText(QMessageBox::Open, "Open profile log");

            int action = msg.exec();

            if(action == QMessageBox::Ignore)
            {
                return;
            }
            else if(action == QMessageBox::Abort)
            {
                m_currentModification->disableDefaults();
                return;
            }
            else if(action == QMessageBox::Retry)
            {
                m_currentModification->disableDefaults();
                err = m_currentModification->enableDefaults();
            }
            else if(action == QMessageBox::Open)
            {
                LogViewer::execForProfile(m_currentModification->getModManager()->profile());
            }
        }*/
    }
}

void ModManagerWidgetItem::disableClicked()
{
    if(m_currentModification != nullptr)
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        m_currentModification->disableAll();

        QApplication::restoreOverrideCursor();
    }
}

void ModManagerWidgetItem::moveUpClicked()
{
    if(m_currentModification != nullptr)
    {
        m_currentModification->getModManager()->priotizeUp(m_currentModification);
    }
}

void ModManagerWidgetItem::moveDownClicked()
{
    if(m_currentModification != nullptr)
    {
        m_currentModification->getModManager()->priotizeDown(m_currentModification);
    }
}

void ModManagerWidgetItem::deleteClicked()
{
    if(m_currentModification != nullptr)
    {
        if(QMessageBox::question(this,
                                 "Delete modification",
                                 "Do you really want to delete the modification " + m_currentModification->name() + "?",
                                 QMessageBox::Yes,
                                 QMessageBox::No) != QMessageBox::Yes)
            return;

        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        Modification * current = m_currentModification;
        ModManager * mgr = m_currentModification->getModManager();
        setCurrentModification(nullptr);

        mgr->deleteMod(current);

        QApplication::restoreOverrideCursor();
    }
}

void ModManagerWidgetItem::copyToProfileClicked()
{
    QStringList profiles;

    for(Profile * p : ProfileManager::instance()->getProfiles())
    {
        if(p != m_currentModification->getModManager()->profile())
        {
            profiles << p->name() + " (" + p->id() + ")";
        }
    }

    if(profiles.isEmpty())
    {
        QMessageBox::information(this, "Copy modification to ...", "You don't have other profiles.", QMessageBox::Ok);
        return;
    }

    QInputDialog dlg;
    dlg.setInputMode(QInputDialog::TextInput);
    dlg.setOption(QInputDialog::UseListViewForComboBoxItems, true);
    dlg.setComboBoxItems(profiles);
    dlg.setLabelText("Select the profile where the modification should be copied to:");
    dlg.setOkButtonText("Copy modification");

    if(dlg.exec() == QInputDialog::Accepted)
    {
        QString profileid = dlg.textValue().split(" ").last();
        profileid = profileid.mid(1, profileid.size() - 2);
        Profile * p = ProfileManager::instance()->getProfile(profileid);

        if(p == nullptr)
        {
            throw std::runtime_error("Implementation fail!");
        }

        if(p->getModManager()->getModification(m_currentModification->id()) != nullptr)
        {
            QMessageBox overwritedlg;
            overwritedlg.setText("Copy to ...");
            overwritedlg.setInformativeText("There is already a modification with the same name. What do you want to do? Keep in mind that this could break some thins.");
            overwritedlg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            overwritedlg.setButtonText(QMessageBox::Ok, "Overwrite");

            if(overwritedlg.exec() == QMessageBox::Cancel)
                return;
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        m_currentModification->getModManager()->copyModTo(m_currentModification, p);

        QApplication::restoreOverrideCursor();
    }
}

void ModManagerWidgetItem::reprimeClicked()
{
    if(m_currentModification->getEnabledPipelines().isEmpty())
    {
        QMessageBox::information(this, "Reinitialize modification", "This modification is not enabled. No reinitialization will be done.");
        return;
    }

    ActivateModDialog dlg;
    dlg.reininitializeModification(m_currentModification);

    /*QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    int err = m_currentModification->prime(true);

    QApplication::restoreOverrideCursor();

    while(err != 0)
    {
        QMessageBox msg;
        msg.setText("Re-initialize content");
        msg.setInformativeText("An error happened while reinitializing the mod. What do you want to do?");
        msg.setStandardButtons(QMessageBox::Ignore | QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Open);
        msg.setButtonText(QMessageBox::Abort, "Deactivate mod");
        msg.setButtonText(QMessageBox::Open, "Open profile log");

        int action = msg.exec();

        if(action == QMessageBox::Ignore)
        {
            return;
        }
        else if(action == QMessageBox::Abort)
        {
            m_currentModification->disableAll();
            return;
        }
        else if(action == QMessageBox::Retry)
        {
            err = m_currentModification->prime(true);
        }
        else if(action == QMessageBox::Open)
        {
            LogViewer::execForProfile(m_currentModification->getModManager()->profile());
        }
    }*/
}

void ModManagerWidgetItem::exportClicked()
{
    QFileDialog dlg;
    dlg.setFileMode(QFileDialog::AnyFile);
    dlg.setMimeTypeFilters(QStringList() << "application/zip" << "application/octet-stream");
    dlg.setAcceptMode(QFileDialog::AcceptSave);

    if(dlg.exec() == QFileDialog::Accepted)
    {
        QString file = dlg.selectedFiles().first();

        if(QFileInfo(file).exists())
        {
            if(QMessageBox::question(this,
                                     "Export modification",
                                     "Do you want to overwrite " + file + "?") != QMessageBox::Yes)
            {
                return;
            }
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        if(!m_currentModification->exportToZip(file))
        {
            QMessageBox::critical(this,
                                  "Export modification",
                                  "Error while exporting!");
        }

        QApplication::restoreOverrideCursor();
    }
}

void ModManagerWidgetItem::openDirectoryClicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_currentModification->modBasePath().absolutePath()));
}

void ModManagerWidgetItem::updateData()
{
    Modification * mod = m_currentModification;

    ui->lblName->setText(mod->name());
    ui->lblDescription->setText(utils::makeTextEditHTML(utils::markdownToHTML(mod->getModManager()->autoResolveModUrls(mod->description()))));
    ui->lblAuthor->setText("by " + mod->author());
    ui->lblLicense->setText(mod->license());
    ui->lblIdentifier->setText(mod->id());
    ui->lblVersion->setText(mod->version().toString());
    ui->lblWebsite->setText(QString("<html><head/><body><p><a href=\"%1\"><span style=\" text-decoration: underline; color:#4c6b8a;\">Website</span></a></p></body></html>")
                            .arg(mod->url()));
    ui->lblWebsite->setToolTip(mod->url());

    QList<Pipeline*> enabled = mod->getEnabledPipelines();

    ui->btnDisableAll->setVisible(enabled.size() > 0);
    ui->btnEnableDefaults->setVisible(enabled.empty());

    ui->btnEnableDefaults->setEnabled(mod->getSupportedDefaultPipelines().size() > 0);

    if(enabled.empty())
    {
        ui->lblIcon->setEnabled(false);
        ui->lblStatus->setText("");
    }
    else
    {
        ui->lblIcon->setEnabled(true);
        ui->lblStatus->setText(QString("%1 modules enabled").arg(enabled.size()));
    }

    // Add pipelines
    ui->pipelineListWidget->setPipelines(mod->getPipelines());
    /*utils::clearLayout(ui->grpPipelines->layout());
    bool first = true;
    for(QString id : mod->getPipelineIds())
    {
        if(!first)
        {
            QFrame * hline = new QFrame(ui->grpPipelines);
            hline->setFrameShadow(QFrame::Sunken);
            hline->setFrameShape(QFrame::HLine);
            ui->grpPipelines->layout()->addWidget(hline);
        }
        else
        {
            first = false;
        }

        Pipeline * pip = mod->getPipeline(id);

        ModManagerWidgetPipelineItem * widget = new ModManagerWidgetPipelineItem(ui->grpPipelines);
        widget->setCurrentPipeline(pip);

        ui->grpPipelines->layout()->addWidget(widget);
    }*/

    // Set icon if available
    QString iconfilename = mod->modBasePath().absoluteFilePath("icon.png");
    QPixmap icon;

    if(!icon.load(iconfilename))
    {
        icon.load(":/resources/icons/mod-100.png");
    }

    ui->lblIcon->setPixmap(icon);
}

#include "modmanagerwidgetitem.h"
#include "ui_modmanagerwidgetitem.h"
#include "utils.h"
#include "modmanagerwidgetpipelineitem.h"
#include "modmanager.h"
#include <QPixmap>
#include <QMenu>
#include "profilemanager.h"

ModManagerWidgetItem::ModManagerWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModManagerWidgetItem)
{
    ui->setupUi(this);

    QMenu *action_menu = new QMenu(ui->btnDelete);
    action_menu->addActions(QList<QAction*>() << ui->actionCopyToProfile << ui->actionReinitialize);
    ui->btnDelete->setMenu(action_menu);

    connect(ui->btnShowMore, SIGNAL(toggled(bool)), this, SLOT(showMoreToggled(bool)));
    connect(ui->btnEnableDefaults, &QPushButton::clicked, this,&ModManagerWidgetItem::enableClicked);
    connect(ui->btnDisableAll, &QPushButton::clicked, this, &ModManagerWidgetItem::disableClicked);
    connect(ui->btnSortUp, &QToolButton::clicked, this, &ModManagerWidgetItem::moveUpClicked);
    connect(ui->btnSortDown, &QToolButton::clicked, this, &ModManagerWidgetItem::moveDownClicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &ModManagerWidgetItem::deleteClicked);
    connect(ui->actionCopyToProfile, &QAction::triggered, this, &ModManagerWidgetItem::copyToProfileClicked);
    connect(ui->actionReinitialize, &QAction::triggered, this, &ModManagerWidgetItem::reprimeClicked);

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

void ModManagerWidgetItem::search(const QString &searchstring)
{
    setCollapsed(!(searchstring.isEmpty() || m_currentModification->search(searchstring)));
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
            ui->lblStatus->setText("");
        else
            ui->lblStatus->setText(QString("%1 modules enabled").arg(enabled_pipelines.size()));
    }
}

void ModManagerWidgetItem::enableClicked()
{
    if(m_currentModification != nullptr)
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();

        int err = m_currentModification->enableDefaults();

        QApplication::restoreOverrideCursor();

        if(err != 0)
        {
            QMessageBox::information(this, "Enable defaults", "Something went wrong while activating the modification. Open the 'Profile log' at 'Play' to see what happened.");
        }
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
        m_currentModification->getModManager()->priotizeUp(m_currentModification->id());
    }
}

void ModManagerWidgetItem::moveDownClicked()
{
    if(m_currentModification != nullptr)
    {
        m_currentModification->getModManager()->priotizeDown(m_currentModification->id());
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

        QString id = m_currentModification->id();
        ModManager * mgr = m_currentModification->getModManager();
        setCurrentModification(nullptr);

        mgr->deleteMod(id);

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

        m_currentModification->getModManager()->copyModTo(m_currentModification->id(), p);

        QApplication::restoreOverrideCursor();
    }
}

void ModManagerWidgetItem::reprimeClicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    m_currentModification->rePrime();

    QApplication::restoreOverrideCursor();
}

void ModManagerWidgetItem::updateData()
{
    Modification * mod = m_currentModification;

    ui->lblName->setText(mod->name());
    ui->lblDescription->document()->setPlainText(mod->description());
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

    if(enabled.empty())
        ui->lblStatus->setText("");
    else
        ui->lblStatus->setText(QString("%1 modules enabled").arg(enabled.size()));

    // Add pipelines
    utils::clearLayout(ui->grpPipelines->layout());
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
    }

    // Set icon if available
    QString iconfilename = mod->modBasePath().absoluteFilePath("icon.png");
    QPixmap icon;

    if(!icon.load(iconfilename))
    {
        icon.load(":/resources/icons/mod-100.png");
    }

    ui->lblIcon->setPixmap(icon);
}

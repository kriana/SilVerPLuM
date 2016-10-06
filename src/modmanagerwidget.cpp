#include "modmanagerwidget.h"
#include "ui_modmanagerwidget.h"
#include "utils.h"
#include "modmanager.h"
#include "modmanagerwidgetitem.h"
#include <QFileDialog>

ModManagerWidget::ModManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModManagerWidget)
{
    ui->setupUi(this);

    connect(ui->searchBar, SIGNAL(textChanged(QString)), this, SLOT(search(QString)));
    connect(ui->btnRefresh, SIGNAL(clicked(bool)), this, SLOT(reloadModList()));
    connect(ui->btnInstallMod, &QToolButton::clicked, this, &ModManagerWidget::installModClicked);
}

ModManagerWidget::~ModManagerWidget()
{
    delete ui;
}

ModManager *ModManagerWidget::currentModManager() const
{
    return m_currentMM;
}

void ModManagerWidget::setModManager(ModManager *currentMM)
{
    if(m_currentMM != nullptr)
    {
        disconnect(m_currentMM, SIGNAL(modListUpdated()), this, SLOT(reloadModList()));
        disconnect(m_currentMM->profile(), SIGNAL(updated()), this, SLOT(reloadModList()));
    }

    m_currentMM = currentMM;

    if(m_currentMM != nullptr)
    {
        connect(m_currentMM, SIGNAL(modListUpdated()), this, SLOT(reloadModList()));
        connect(m_currentMM->profile(), SIGNAL(updated()), this, SLOT(reloadModList()));
    }

    ui->dependencyWarning->setModManager(currentMM);

    reloadModList();

    ui->searchBar->setText("");
}

void ModManagerWidget::reloadModList()
{
    int scrollh =ui->scrollArea->horizontalScrollBar()->value();
    int scrollv = ui->scrollArea->verticalScrollBar()->value();

    utils::clearLayout(ui->modList->layout());


    QVBoxLayout * layout = dynamic_cast<QVBoxLayout*>(ui->modList->layout());

    if(m_currentMM != nullptr)
    {
        for(Modification * mod : m_currentMM->getModifications())
        {
            ModManagerWidgetItem * item = new ModManagerWidgetItem(ui->modList);
            item->setCurrentModification(mod);
            layout->addWidget(item);
        }
    }

    layout->addStretch(1);


    search(ui->searchBar->text());
    ui->scrollArea->horizontalScrollBar()->setValue(scrollh);
    ui->scrollArea->verticalScrollBar()->setValue(scrollv);
}

void ModManagerWidget::installModClicked()
{
    QFileDialog dlg;
    dlg.setFileMode(QFileDialog::ExistingFiles);
    dlg.setMimeTypeFilters(QStringList() << "application/zip" << "application/octet-stream");

    if(dlg.exec() == QFileDialog::Accepted)
    {
        for(QString file : dlg.selectedFiles())
        {
            try
            {
                m_currentMM->addMod(file);
            }
            catch(...)
            {
                if(QMessageBox::critical(this,
                                      "Add modification",
                                      "Could not add " + file,
                                      QMessageBox::Ok,
                                      QMessageBox::Cancel) == QMessageBox::Cancel)
                {
                    break;
                }
            }
        }
    }
}

void ModManagerWidget::search(const QString &searchstring_)
{
    QString searchstring = searchstring_.trimmed();

    QLayout * layout = ui->modList->layout();

    for(int i = 0; i < layout->count(); ++i)
    {
        QLayoutItem * item = layout->itemAt(i);

        if(item->widget() != nullptr)
        {
            ModManagerWidgetItem * mitem = dynamic_cast<ModManagerWidgetItem*>(item->widget());

            if(mitem != nullptr)
            {
                mitem->search(searchstring);
            }
        }
    }
}

#include "savegameviewerdialog.h"
#include "ui_savegameviewerdialog.h"

SavegameViewerDialog::SavegameViewerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SavegameViewerDialog)
{
    ui->setupUi(this);
}

SavegameViewerDialog::~SavegameViewerDialog()
{
    delete ui;
}

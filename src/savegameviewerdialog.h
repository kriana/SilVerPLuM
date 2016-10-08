#ifndef SAVEGAMEVIEWERDIALOG_H
#define SAVEGAMEVIEWERDIALOG_H

#include <QDialog>

namespace Ui {
class SavegameViewerDialog;
}

class SavegameViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SavegameViewerDialog(QWidget *parent = 0);
    ~SavegameViewerDialog();

private:
    Ui::SavegameViewerDialog *ui;
};

#endif // SAVEGAMEVIEWERDIALOG_H

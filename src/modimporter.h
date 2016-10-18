#ifndef MODIMPORTER_H
#define MODIMPORTER_H

#include <QDialog>
#include "modimportercontentitem.h"

namespace Ui {
class ModImporter;
}

class ModImporter : public QDialog
{
    Q_OBJECT

public:
    explicit ModImporter(QWidget *parent = 0);
    ~ModImporter();

    void removeContent(ModImporterContentItem * item);

    QString findNewContentId();

    ModImporterContentItem * getContent(const QString & id);

protected:

    void closeEvent(QCloseEvent * event);

private slots:

    ModImporterContentItem *addContent();

    void import();

    void nameChanged(const QString & text);

    void importManuallyClicked();

    void importZipClicked();

    void importDirectoryClicked();

private:
    Ui::ModImporter *ui;
    QList<ModImporterContentItem*> m_contentItems;

    bool isValid();

    void importDirectory(const QDir & dir, QString name);
};

#endif // MODIMPORTER_H

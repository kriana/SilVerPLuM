#ifndef MODIMPORTERCONTENTITEM_H
#define MODIMPORTERCONTENTITEM_H

#include <QWidget>
#include <QDir>
#include <QJsonObject>

namespace Ui {
class ModImporterContentItem;
}

class ModImporter;

class ModImporterContentItem : public QWidget
{
    Q_OBJECT

public:
    explicit ModImporterContentItem(ModImporter * importer, QWidget *parent = 0);
    ~ModImporterContentItem();

    bool isValid();

    QString getContentId();

    QJsonObject build(const QDir & modbasepath);

    void setExpanded(bool expand);

private:
    Ui::ModImporterContentItem *ui;
    ModImporter * m_importer;

private slots:

    void updateInformationLabel();

    void remove();
};

#endif // MODIMPORTERCONTENTITEM_H

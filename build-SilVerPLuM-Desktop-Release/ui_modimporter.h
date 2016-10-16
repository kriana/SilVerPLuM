/********************************************************************************
** Form generated from reading UI file 'modimporter.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIMPORTER_H
#define UI_MODIMPORTER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "identifierlineedit.h"
#include "markdowntexteditor.h"

QT_BEGIN_NAMESPACE

class Ui_ModImporter
{
public:
    QVBoxLayout *verticalLayout;
    QToolBox *toolBox;
    QWidget *page;
    QFormLayout *formLayout_2;
    QLabel *label;
    IdentifierLineEdit *modIdentifier;
    QLabel *label_7;
    MarkdownTextEditor *modDescription;
    QLabel *label_8;
    QComboBox *modRequiresStardewValley;
    QLabel *label_2;
    QLineEdit *modName;
    QLabel *label_3;
    QLineEdit *modAuthor;
    QLabel *label_4;
    QComboBox *modLicense;
    QLabel *label_5;
    QLineEdit *modVersion;
    QLabel *label_6;
    QLineEdit *modWebsite;
    QWidget *contentItemsPage;
    QVBoxLayout *verticalLayout_3;
    QWidget *contentItems;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAddContent;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClose;
    QPushButton *btnImport;

    void setupUi(QDialog *ModImporter)
    {
        if (ModImporter->objectName().isEmpty())
            ModImporter->setObjectName(QStringLiteral("ModImporter"));
        ModImporter->resize(589, 374);
        ModImporter->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(ModImporter);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        toolBox = new QToolBox(ModImporter);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 557, 484));
        formLayout_2 = new QFormLayout(page);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(140, 0));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label);

        modIdentifier = new IdentifierLineEdit(page);
        modIdentifier->setObjectName(QStringLiteral("modIdentifier"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, modIdentifier);

        label_7 = new QLabel(page);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(140, 0));

        formLayout_2->setWidget(7, QFormLayout::LabelRole, label_7);

        modDescription = new MarkdownTextEditor(page);
        modDescription->setObjectName(QStringLiteral("modDescription"));
        modDescription->setMinimumSize(QSize(0, 200));

        formLayout_2->setWidget(7, QFormLayout::FieldRole, modDescription);

        label_8 = new QLabel(page);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(140, 0));

        formLayout_2->setWidget(8, QFormLayout::LabelRole, label_8);

        modRequiresStardewValley = new QComboBox(page);
        modRequiresStardewValley->setObjectName(QStringLiteral("modRequiresStardewValley"));
        modRequiresStardewValley->setEditable(true);

        formLayout_2->setWidget(8, QFormLayout::FieldRole, modRequiresStardewValley);

        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(140, 0));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_2);

        modName = new QLineEdit(page);
        modName->setObjectName(QStringLiteral("modName"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, modName);

        label_3 = new QLabel(page);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(140, 0));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        modAuthor = new QLineEdit(page);
        modAuthor->setObjectName(QStringLiteral("modAuthor"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, modAuthor);

        label_4 = new QLabel(page);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(140, 0));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_4);

        modLicense = new QComboBox(page);
        modLicense->setObjectName(QStringLiteral("modLicense"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(modLicense->sizePolicy().hasHeightForWidth());
        modLicense->setSizePolicy(sizePolicy);
        modLicense->setEditable(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, modLicense);

        label_5 = new QLabel(page);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(140, 0));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_5);

        modVersion = new QLineEdit(page);
        modVersion->setObjectName(QStringLiteral("modVersion"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, modVersion);

        label_6 = new QLabel(page);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(140, 0));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_6);

        modWebsite = new QLineEdit(page);
        modWebsite->setObjectName(QStringLiteral("modWebsite"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, modWebsite);

        toolBox->addItem(page, QStringLiteral("Mod information"));
        contentItemsPage = new QWidget();
        contentItemsPage->setObjectName(QStringLiteral("contentItemsPage"));
        contentItemsPage->setGeometry(QRect(0, 0, 577, 246));
        verticalLayout_3 = new QVBoxLayout(contentItemsPage);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        contentItems = new QWidget(contentItemsPage);
        contentItems->setObjectName(QStringLiteral("contentItems"));
        verticalLayout_2 = new QVBoxLayout(contentItems);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, -1, 0, -1);

        verticalLayout_3->addWidget(contentItems);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        toolBox->addItem(contentItemsPage, QStringLiteral("Mod content"));

        verticalLayout->addWidget(toolBox);

        widget = new QWidget(ModImporter);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnAddContent = new QPushButton(widget);
        btnAddContent->setObjectName(QStringLiteral("btnAddContent"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("list-add");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnAddContent->setIcon(icon);

        horizontalLayout->addWidget(btnAddContent);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnClose = new QPushButton(widget);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        QIcon icon1;
        iconThemeName = QStringLiteral("dialog-close");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnClose->setIcon(icon1);

        horizontalLayout->addWidget(btnClose);

        btnImport = new QPushButton(widget);
        btnImport->setObjectName(QStringLiteral("btnImport"));
        QIcon icon2;
        iconThemeName = QStringLiteral("dialog-ok");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnImport->setIcon(icon2);

        horizontalLayout->addWidget(btnImport);


        verticalLayout->addWidget(widget);


        retranslateUi(ModImporter);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ModImporter);
    } // setupUi

    void retranslateUi(QDialog *ModImporter)
    {
        ModImporter->setWindowTitle(QApplication::translate("ModImporter", "Mod Importer", 0));
        label->setText(QApplication::translate("ModImporter", "Identifier", 0));
#ifndef QT_NO_TOOLTIP
        modIdentifier->setToolTip(QApplication::translate("ModImporter", "The identifier of this modification.", 0));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("ModImporter", "Description", 0));
        label_8->setText(QApplication::translate("ModImporter", "Stardew Valley version", 0));
#ifndef QT_NO_TOOLTIP
        modRequiresStardewValley->setToolTip(QApplication::translate("ModImporter", "The Stardew Valley version this mod is intended to run.", 0));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("ModImporter", "Name", 0));
#ifndef QT_NO_TOOLTIP
        modName->setToolTip(QApplication::translate("ModImporter", "The name of this modification", 0));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("ModImporter", "Author", 0));
#ifndef QT_NO_TOOLTIP
        modAuthor->setToolTip(QApplication::translate("ModImporter", "The author of this modification.", 0));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("ModImporter", "License", 0));
        modLicense->clear();
        modLicense->insertItems(0, QStringList()
         << QApplication::translate("ModImporter", "Creative Commons CC BY", 0)
         << QApplication::translate("ModImporter", "Creative Commons CC BY-SA", 0)
         << QApplication::translate("ModImporter", "Creative Commons CC BY-ND", 0)
         << QApplication::translate("ModImporter", "Creative Commons CC BY-NC", 0)
         << QApplication::translate("ModImporter", "Creative Commons CC BY-NC-SA", 0)
         << QApplication::translate("ModImporter", "Creative Commons CC BY-NC-ND", 0)
         << QApplication::translate("ModImporter", "GPLv2", 0)
         << QApplication::translate("ModImporter", "GPLv3", 0)
         << QApplication::translate("ModImporter", "LGPL", 0)
         << QApplication::translate("ModImporter", "MIT", 0)
         << QApplication::translate("ModImporter", "Apache", 0)
         << QApplication::translate("ModImporter", "BSD", 0)
         << QApplication::translate("ModImporter", "Chucklefish Allow-Pack Anyone", 0)
         << QApplication::translate("ModImporter", "Chucklefish Ask-Pack Anyone", 0)
         << QApplication::translate("ModImporter", "Chucklefish No-Pack Anyone", 0)
         << QApplication::translate("ModImporter", "Chucklefish Allow-Pack Ask", 0)
         << QApplication::translate("ModImporter", "Chucklefish Ask-Pack Ask", 0)
         << QApplication::translate("ModImporter", "Chucklefish No-Pack Ask", 0)
         << QApplication::translate("ModImporter", "Chucklefish Allow-Pack Only-Use", 0)
         << QApplication::translate("ModImporter", "Chucklefish Ask-Pack Only-Use", 0)
         << QApplication::translate("ModImporter", "Chucklefish No-Pack Only-Use", 0)
        );
#ifndef QT_NO_TOOLTIP
        modLicense->setToolTip(QApplication::translate("ModImporter", "Select the license used by the modification. The drop-down-box contains pre-made entries you can use.", 0));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("ModImporter", "Version", 0));
#ifndef QT_NO_TOOLTIP
        modVersion->setToolTip(QApplication::translate("ModImporter", "The version of this mod.", 0));
#endif // QT_NO_TOOLTIP
        modVersion->setText(QApplication::translate("ModImporter", "1.0.0.0", 0));
        label_6->setText(QApplication::translate("ModImporter", "Website", 0));
#ifndef QT_NO_TOOLTIP
        modWebsite->setToolTip(QApplication::translate("ModImporter", "The website URL of this mod.", 0));
#endif // QT_NO_TOOLTIP
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("ModImporter", "Mod information", 0));
        toolBox->setItemText(toolBox->indexOf(contentItemsPage), QApplication::translate("ModImporter", "Mod content", 0));
#ifndef QT_NO_TOOLTIP
        btnAddContent->setToolTip(QApplication::translate("ModImporter", "Adds another content entry into 'Mod content'.", 0));
#endif // QT_NO_TOOLTIP
        btnAddContent->setText(QApplication::translate("ModImporter", "Add content", 0));
        btnClose->setText(QApplication::translate("ModImporter", "Close", 0));
        btnImport->setText(QApplication::translate("ModImporter", "Import", 0));
    } // retranslateUi

};

namespace Ui {
    class ModImporter: public Ui_ModImporter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIMPORTER_H

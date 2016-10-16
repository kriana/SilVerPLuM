/********************************************************************************
** Form generated from reading UI file 'modmanagerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODMANAGERWIDGET_H
#define UI_MODMANAGERWIDGET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "dependencycheckerwidget.h"

QT_BEGIN_NAMESPACE

class Ui_ModManagerWidget
{
public:
    QAction *actionReloadMods;
    QAction *actionImportMod;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QToolButton *btnRefresh;
    QToolButton *btnInstallMod;
    QSpacerItem *horizontalSpacer;
    QLineEdit *searchBar;
    QScrollArea *scrollArea;
    QWidget *modList;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    DependencyCheckerWidget *dependencyWarning;

    void setupUi(QWidget *ModManagerWidget)
    {
        if (ModManagerWidget->objectName().isEmpty())
            ModManagerWidget->setObjectName(QStringLiteral("ModManagerWidget"));
        ModManagerWidget->resize(638, 384);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ModManagerWidget->sizePolicy().hasHeightForWidth());
        ModManagerWidget->setSizePolicy(sizePolicy);
        ModManagerWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionReloadMods = new QAction(ModManagerWidget);
        actionReloadMods->setObjectName(QStringLiteral("actionReloadMods"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("view-refresh");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionReloadMods->setIcon(icon);
        actionImportMod = new QAction(ModManagerWidget);
        actionImportMod->setObjectName(QStringLiteral("actionImportMod"));
        QIcon icon1;
        iconThemeName = QStringLiteral("document-import");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionImportMod->setIcon(icon1);
        verticalLayout = new QVBoxLayout(ModManagerWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(ModManagerWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnRefresh = new QToolButton(widget);
        btnRefresh->setObjectName(QStringLiteral("btnRefresh"));
        btnRefresh->setIcon(icon);
        btnRefresh->setPopupMode(QToolButton::MenuButtonPopup);
        btnRefresh->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnRefresh->setAutoRaise(true);

        horizontalLayout->addWidget(btnRefresh);

        btnInstallMod = new QToolButton(widget);
        btnInstallMod->setObjectName(QStringLiteral("btnInstallMod"));
        QIcon icon2;
        iconThemeName = QStringLiteral("list-add");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnInstallMod->setIcon(icon2);
        btnInstallMod->setPopupMode(QToolButton::MenuButtonPopup);
        btnInstallMod->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnInstallMod->setAutoRaise(true);

        horizontalLayout->addWidget(btnInstallMod);

        horizontalSpacer = new QSpacerItem(301, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        searchBar = new QLineEdit(widget);
        searchBar->setObjectName(QStringLiteral("searchBar"));
        searchBar->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(searchBar);


        verticalLayout->addWidget(widget);

        scrollArea = new QScrollArea(ModManagerWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        modList = new QWidget();
        modList->setObjectName(QStringLiteral("modList"));
        modList->setGeometry(QRect(0, 0, 606, 306));
        verticalLayout_2 = new QVBoxLayout(modList);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 289, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        scrollArea->setWidget(modList);

        verticalLayout->addWidget(scrollArea);

        dependencyWarning = new DependencyCheckerWidget(ModManagerWidget);
        dependencyWarning->setObjectName(QStringLiteral("dependencyWarning"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dependencyWarning->sizePolicy().hasHeightForWidth());
        dependencyWarning->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(dependencyWarning);


        retranslateUi(ModManagerWidget);

        QMetaObject::connectSlotsByName(ModManagerWidget);
    } // setupUi

    void retranslateUi(QWidget *ModManagerWidget)
    {
        ModManagerWidget->setWindowTitle(QApplication::translate("ModManagerWidget", "Form", 0));
        actionReloadMods->setText(QApplication::translate("ModManagerWidget", "Reload all mods", 0));
#ifndef QT_NO_TOOLTIP
        actionReloadMods->setToolTip(QApplication::translate("ModManagerWidget", "Reloads all mods from the mod directory.", 0));
#endif // QT_NO_TOOLTIP
        actionImportMod->setText(QApplication::translate("ModManagerWidget", "Import from files", 0));
#ifndef QT_NO_TOOLTIP
        actionImportMod->setToolTip(QApplication::translate("ModManagerWidget", "Imports a mod from mods that are not compatible with SilVerPLuM", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btnRefresh->setToolTip(QApplication::translate("ModManagerWidget", "Refreshes the mod list. Does NOT reload all mods.", 0));
#endif // QT_NO_TOOLTIP
        btnRefresh->setText(QApplication::translate("ModManagerWidget", "Refresh", 0));
#ifndef QT_NO_TOOLTIP
        btnInstallMod->setToolTip(QApplication::translate("ModManagerWidget", "Adds a SilVerPLuM mod from a *.zip file. For non-SilVerPLuM mods use the mod importer in the arrow menu.", 0));
#endif // QT_NO_TOOLTIP
        btnInstallMod->setText(QApplication::translate("ModManagerWidget", "Add mod", 0));
        searchBar->setPlaceholderText(QApplication::translate("ModManagerWidget", "Search ...", 0));
    } // retranslateUi

};

namespace Ui {
    class ModManagerWidget: public Ui_ModManagerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODMANAGERWIDGET_H

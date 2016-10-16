/********************************************************************************
** Form generated from reading UI file 'savegamemanagerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEGAMEMANAGERWIDGET_H
#define UI_SAVEGAMEMANAGERWIDGET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SavegameManagerWidget
{
public:
    QAction *actionReloadSavegames;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QToolButton *btnRefresh;
    QToolButton *btnImport;
    QSpacerItem *horizontalSpacer;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QWidget *savegameItems;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *SavegameManagerWidget)
    {
        if (SavegameManagerWidget->objectName().isEmpty())
            SavegameManagerWidget->setObjectName(QStringLiteral("SavegameManagerWidget"));
        SavegameManagerWidget->resize(400, 300);
        SavegameManagerWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionReloadSavegames = new QAction(SavegameManagerWidget);
        actionReloadSavegames->setObjectName(QStringLiteral("actionReloadSavegames"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("view-refresh");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionReloadSavegames->setIcon(icon);
        verticalLayout_3 = new QVBoxLayout(SavegameManagerWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widget = new QWidget(SavegameManagerWidget);
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

        btnImport = new QToolButton(widget);
        btnImport->setObjectName(QStringLiteral("btnImport"));
        QIcon icon1;
        iconThemeName = QStringLiteral("list-add");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnImport->setIcon(icon1);
        btnImport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnImport->setAutoRaise(true);

        horizontalLayout->addWidget(btnImport);

        horizontalSpacer = new QSpacerItem(130, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addWidget(widget);

        scrollArea = new QScrollArea(SavegameManagerWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 368, 240));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        savegameItems = new QWidget(scrollAreaWidgetContents);
        savegameItems->setObjectName(QStringLiteral("savegameItems"));
        verticalLayout = new QVBoxLayout(savegameItems);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout_2->addWidget(savegameItems);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);


        retranslateUi(SavegameManagerWidget);

        QMetaObject::connectSlotsByName(SavegameManagerWidget);
    } // setupUi

    void retranslateUi(QWidget *SavegameManagerWidget)
    {
        SavegameManagerWidget->setWindowTitle(QApplication::translate("SavegameManagerWidget", "Form", 0));
        actionReloadSavegames->setText(QApplication::translate("SavegameManagerWidget", "Reload all savegames", 0));
#ifndef QT_NO_TOOLTIP
        actionReloadSavegames->setToolTip(QApplication::translate("SavegameManagerWidget", "Reloads all savegames from the savegame directory.", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btnRefresh->setToolTip(QApplication::translate("SavegameManagerWidget", "Refreshes the savegame list. This will NOT reload all savegames from the profile directory.", 0));
#endif // QT_NO_TOOLTIP
        btnRefresh->setText(QApplication::translate("SavegameManagerWidget", "Refresh", 0));
#ifndef QT_NO_TOOLTIP
        btnImport->setToolTip(QApplication::translate("SavegameManagerWidget", "Imports a savegame form a *.zip file.", 0));
#endif // QT_NO_TOOLTIP
        btnImport->setText(QApplication::translate("SavegameManagerWidget", "Import savegame", 0));
    } // retranslateUi

};

namespace Ui {
    class SavegameManagerWidget: public Ui_SavegameManagerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEGAMEMANAGERWIDGET_H

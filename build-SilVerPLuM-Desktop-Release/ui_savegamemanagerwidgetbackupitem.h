/********************************************************************************
** Form generated from reading UI file 'savegamemanagerwidgetbackupitem.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEGAMEMANAGERWIDGETBACKUPITEM_H
#define UI_SAVEGAMEMANAGERWIDGETBACKUPITEM_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SavegameManagerWidgetBackupItem
{
public:
    QAction *actionDelete;
    QAction *actionCopyTo;
    QAction *actionSingleOut;
    QAction *actionExport;
    QHBoxLayout *horizontalLayout;
    QLabel *lblDate;
    QLabel *lblInfo;
    QToolButton *btnRestore;

    void setupUi(QWidget *SavegameManagerWidgetBackupItem)
    {
        if (SavegameManagerWidgetBackupItem->objectName().isEmpty())
            SavegameManagerWidgetBackupItem->setObjectName(QStringLiteral("SavegameManagerWidgetBackupItem"));
        SavegameManagerWidgetBackupItem->resize(400, 300);
        SavegameManagerWidgetBackupItem->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionDelete = new QAction(SavegameManagerWidgetBackupItem);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("edit-delete");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionDelete->setIcon(icon);
        actionCopyTo = new QAction(SavegameManagerWidgetBackupItem);
        actionCopyTo->setObjectName(QStringLiteral("actionCopyTo"));
        QIcon icon1;
        iconThemeName = QStringLiteral("edit-copy");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionCopyTo->setIcon(icon1);
        actionSingleOut = new QAction(SavegameManagerWidgetBackupItem);
        actionSingleOut->setObjectName(QStringLiteral("actionSingleOut"));
        actionSingleOut->setIcon(icon1);
        actionExport = new QAction(SavegameManagerWidgetBackupItem);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        QIcon icon2;
        iconThemeName = QStringLiteral("document-save");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionExport->setIcon(icon2);
        horizontalLayout = new QHBoxLayout(SavegameManagerWidgetBackupItem);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lblDate = new QLabel(SavegameManagerWidgetBackupItem);
        lblDate->setObjectName(QStringLiteral("lblDate"));

        horizontalLayout->addWidget(lblDate);

        lblInfo = new QLabel(SavegameManagerWidgetBackupItem);
        lblInfo->setObjectName(QStringLiteral("lblInfo"));
        QFont font;
        font.setItalic(true);
        lblInfo->setFont(font);

        horizontalLayout->addWidget(lblInfo);

        btnRestore = new QToolButton(SavegameManagerWidgetBackupItem);
        btnRestore->setObjectName(QStringLiteral("btnRestore"));
        btnRestore->setMinimumSize(QSize(100, 0));
        btnRestore->setMaximumSize(QSize(100, 16777215));
        btnRestore->setPopupMode(QToolButton::MenuButtonPopup);
        btnRestore->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(btnRestore);


        retranslateUi(SavegameManagerWidgetBackupItem);

        QMetaObject::connectSlotsByName(SavegameManagerWidgetBackupItem);
    } // setupUi

    void retranslateUi(QWidget *SavegameManagerWidgetBackupItem)
    {
        SavegameManagerWidgetBackupItem->setWindowTitle(QApplication::translate("SavegameManagerWidgetBackupItem", "Form", 0));
        actionDelete->setText(QApplication::translate("SavegameManagerWidgetBackupItem", "Delete", 0));
#ifndef QT_NO_TOOLTIP
        actionDelete->setToolTip(QApplication::translate("SavegameManagerWidgetBackupItem", "Deletes this backup.", 0));
#endif // QT_NO_TOOLTIP
        actionCopyTo->setText(QApplication::translate("SavegameManagerWidgetBackupItem", "Copy to another profile", 0));
#ifndef QT_NO_TOOLTIP
        actionCopyTo->setToolTip(QApplication::translate("SavegameManagerWidgetBackupItem", "Copies this backup into another profile as a new savegame.", 0));
#endif // QT_NO_TOOLTIP
        actionSingleOut->setText(QApplication::translate("SavegameManagerWidgetBackupItem", "Single out", 0));
#ifndef QT_NO_TOOLTIP
        actionSingleOut->setToolTip(QApplication::translate("SavegameManagerWidgetBackupItem", "Creates a new savegame out of this backup.", 0));
#endif // QT_NO_TOOLTIP
        actionExport->setText(QApplication::translate("SavegameManagerWidgetBackupItem", "Export savegame", 0));
#ifndef QT_NO_TOOLTIP
        actionExport->setToolTip(QApplication::translate("SavegameManagerWidgetBackupItem", "Exports this backup as *.zip file.", 0));
#endif // QT_NO_TOOLTIP
        lblDate->setText(QApplication::translate("SavegameManagerWidgetBackupItem", "TextLabel", 0));
        lblInfo->setText(QApplication::translate("SavegameManagerWidgetBackupItem", "TextLabel", 0));
#ifndef QT_NO_TOOLTIP
        btnRestore->setToolTip(QApplication::translate("SavegameManagerWidgetBackupItem", "Restores this backup. Will overwrite the current savegame.", 0));
#endif // QT_NO_TOOLTIP
        btnRestore->setText(QApplication::translate("SavegameManagerWidgetBackupItem", "Restore", 0));
    } // retranslateUi

};

namespace Ui {
    class SavegameManagerWidgetBackupItem: public Ui_SavegameManagerWidgetBackupItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEGAMEMANAGERWIDGETBACKUPITEM_H

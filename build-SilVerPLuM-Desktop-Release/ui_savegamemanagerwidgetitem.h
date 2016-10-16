/********************************************************************************
** Form generated from reading UI file 'savegamemanagerwidgetitem.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEGAMEMANAGERWIDGETITEM_H
#define UI_SAVEGAMEMANAGERWIDGETITEM_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SavegameManagerWidgetItem
{
public:
    QAction *actionDelete;
    QAction *actionCopyTo;
    QAction *actionSingleOut;
    QAction *actionDeleteMainSavegame;
    QAction *actionPrune;
    QAction *actionExport;
    QGridLayout *gridLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QWidget *mainWidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblFarmerName;
    QLabel *lblIngameDate;
    QLabel *lblFarmName;
    QLabel *lblMoney;
    QLabel *lblPlayTime;
    QSpacerItem *verticalSpacer;
    QLabel *lblId;
    QVBoxLayout *verticalLayout_3;
    QLabel *lblBackupInfo;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QToolButton *btnBackup;
    QPushButton *btnShowMore;
    QWidget *expandWidget;
    QVBoxLayout *verticalLayout_4;
    QFrame *line;
    QWidget *backupItems;
    QVBoxLayout *verticalLayout_5;

    void setupUi(QWidget *SavegameManagerWidgetItem)
    {
        if (SavegameManagerWidgetItem->objectName().isEmpty())
            SavegameManagerWidgetItem->setObjectName(QStringLiteral("SavegameManagerWidgetItem"));
        SavegameManagerWidgetItem->resize(416, 300);
        SavegameManagerWidgetItem->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionDelete = new QAction(SavegameManagerWidgetItem);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("edit-delete");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionDelete->setIcon(icon);
        actionCopyTo = new QAction(SavegameManagerWidgetItem);
        actionCopyTo->setObjectName(QStringLiteral("actionCopyTo"));
        QIcon icon1;
        iconThemeName = QStringLiteral("edit-duplicate");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionCopyTo->setIcon(icon1);
        actionSingleOut = new QAction(SavegameManagerWidgetItem);
        actionSingleOut->setObjectName(QStringLiteral("actionSingleOut"));
        QIcon icon2;
        iconThemeName = QStringLiteral("edit-copy");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionSingleOut->setIcon(icon2);
        actionDeleteMainSavegame = new QAction(SavegameManagerWidgetItem);
        actionDeleteMainSavegame->setObjectName(QStringLiteral("actionDeleteMainSavegame"));
        actionDeleteMainSavegame->setIcon(icon);
        actionPrune = new QAction(SavegameManagerWidgetItem);
        actionPrune->setObjectName(QStringLiteral("actionPrune"));
        QIcon icon3;
        iconThemeName = QStringLiteral("edit-cut");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionPrune->setIcon(icon3);
        actionExport = new QAction(SavegameManagerWidgetItem);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        QIcon icon4;
        iconThemeName = QStringLiteral("document-save");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionExport->setIcon(icon4);
        gridLayout = new QGridLayout(SavegameManagerWidgetItem);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame = new QFrame(SavegameManagerWidgetItem);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mainWidget = new QWidget(frame);
        mainWidget->setObjectName(QStringLiteral("mainWidget"));
        horizontalLayout_2 = new QHBoxLayout(mainWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        widget = new QWidget(mainWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lblFarmerName = new QLabel(widget);
        lblFarmerName->setObjectName(QStringLiteral("lblFarmerName"));
        QFont font;
        font.setPointSize(16);
        lblFarmerName->setFont(font);

        verticalLayout_2->addWidget(lblFarmerName);

        lblIngameDate = new QLabel(widget);
        lblIngameDate->setObjectName(QStringLiteral("lblIngameDate"));

        verticalLayout_2->addWidget(lblIngameDate);

        lblFarmName = new QLabel(widget);
        lblFarmName->setObjectName(QStringLiteral("lblFarmName"));

        verticalLayout_2->addWidget(lblFarmName);

        lblMoney = new QLabel(widget);
        lblMoney->setObjectName(QStringLiteral("lblMoney"));

        verticalLayout_2->addWidget(lblMoney);

        lblPlayTime = new QLabel(widget);
        lblPlayTime->setObjectName(QStringLiteral("lblPlayTime"));

        verticalLayout_2->addWidget(lblPlayTime);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        lblId = new QLabel(widget);
        lblId->setObjectName(QStringLiteral("lblId"));
        QFont font1;
        font1.setItalic(true);
        lblId->setFont(font1);

        verticalLayout_2->addWidget(lblId);


        horizontalLayout_2->addWidget(widget);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        lblBackupInfo = new QLabel(mainWidget);
        lblBackupInfo->setObjectName(QStringLiteral("lblBackupInfo"));
        lblBackupInfo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_3->addWidget(lblBackupInfo);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnBackup = new QToolButton(mainWidget);
        btnBackup->setObjectName(QStringLiteral("btnBackup"));
        btnBackup->setPopupMode(QToolButton::MenuButtonPopup);
        btnBackup->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(btnBackup);

        btnShowMore = new QPushButton(mainWidget);
        btnShowMore->setObjectName(QStringLiteral("btnShowMore"));
        btnShowMore->setCheckable(true);

        horizontalLayout->addWidget(btnShowMore);


        verticalLayout_3->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout->addWidget(mainWidget);

        expandWidget = new QWidget(frame);
        expandWidget->setObjectName(QStringLiteral("expandWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(expandWidget->sizePolicy().hasHeightForWidth());
        expandWidget->setSizePolicy(sizePolicy1);
        verticalLayout_4 = new QVBoxLayout(expandWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        line = new QFrame(expandWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        backupItems = new QWidget(expandWidget);
        backupItems->setObjectName(QStringLiteral("backupItems"));
        verticalLayout_5 = new QVBoxLayout(backupItems);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));

        verticalLayout_4->addWidget(backupItems);


        verticalLayout->addWidget(expandWidget);


        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(SavegameManagerWidgetItem);

        QMetaObject::connectSlotsByName(SavegameManagerWidgetItem);
    } // setupUi

    void retranslateUi(QWidget *SavegameManagerWidgetItem)
    {
        SavegameManagerWidgetItem->setWindowTitle(QApplication::translate("SavegameManagerWidgetItem", "Form", 0));
        actionDelete->setText(QApplication::translate("SavegameManagerWidgetItem", "Delete savegame and backups", 0));
        actionCopyTo->setText(QApplication::translate("SavegameManagerWidgetItem", "Copy to another profile", 0));
        actionSingleOut->setText(QApplication::translate("SavegameManagerWidgetItem", "Single out", 0));
#ifndef QT_NO_TOOLTIP
        actionSingleOut->setToolTip(QApplication::translate("SavegameManagerWidgetItem", "Creates a new savegame from the current savegame", 0));
#endif // QT_NO_TOOLTIP
        actionDeleteMainSavegame->setText(QApplication::translate("SavegameManagerWidgetItem", "Delete only savegame", 0));
#ifndef QT_NO_TOOLTIP
        actionDeleteMainSavegame->setToolTip(QApplication::translate("SavegameManagerWidgetItem", "Deletes only the current savegame. Backups will be left untouched.", 0));
#endif // QT_NO_TOOLTIP
        actionPrune->setText(QApplication::translate("SavegameManagerWidgetItem", "Remove duplicate backups", 0));
#ifndef QT_NO_TOOLTIP
        actionPrune->setToolTip(QApplication::translate("SavegameManagerWidgetItem", "Removes all backups that are duplicate. The newest one will be kept.", 0));
#endif // QT_NO_TOOLTIP
        actionExport->setText(QApplication::translate("SavegameManagerWidgetItem", "Export savegame", 0));
#ifndef QT_NO_TOOLTIP
        actionExport->setToolTip(QApplication::translate("SavegameManagerWidgetItem", "Exports this savegame as *.zip file.", 0));
#endif // QT_NO_TOOLTIP
        lblFarmerName->setText(QApplication::translate("SavegameManagerWidgetItem", "Farmer name", 0));
        lblIngameDate->setText(QApplication::translate("SavegameManagerWidgetItem", "24th of Summer, Year 2", 0));
        lblFarmName->setText(QApplication::translate("SavegameManagerWidgetItem", "Farm Farm", 0));
        lblMoney->setText(QApplication::translate("SavegameManagerWidgetItem", "1000 G", 0));
        lblPlayTime->setText(QApplication::translate("SavegameManagerWidgetItem", "60h played", 0));
        lblId->setText(QApplication::translate("SavegameManagerWidgetItem", "Identifier", 0));
        lblBackupInfo->setText(QApplication::translate("SavegameManagerWidgetItem", "TextLabel", 0));
#ifndef QT_NO_TOOLTIP
        btnBackup->setToolTip(QApplication::translate("SavegameManagerWidgetItem", "Creates a backup from the current savegame.", 0));
#endif // QT_NO_TOOLTIP
        btnBackup->setText(QApplication::translate("SavegameManagerWidgetItem", "Backup now", 0));
        btnShowMore->setText(QApplication::translate("SavegameManagerWidgetItem", "Show more", 0));
    } // retranslateUi

};

namespace Ui {
    class SavegameManagerWidgetItem: public Ui_SavegameManagerWidgetItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEGAMEMANAGERWIDGETITEM_H

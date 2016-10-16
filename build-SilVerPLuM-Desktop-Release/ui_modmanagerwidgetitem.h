/********************************************************************************
** Form generated from reading UI file 'modmanagerwidgetitem.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODMANAGERWIDGETITEM_H
#define UI_MODMANAGERWIDGETITEM_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModManagerWidgetItem
{
public:
    QAction *actionCopyToProfile;
    QAction *actionReinitialize;
    QAction *actionExportMod;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QWidget *mainWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QToolButton *btnSortUp;
    QSpacerItem *verticalSpacer_2;
    QToolButton *btnSortDown;
    QLabel *lblIcon;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *lblName;
    QLabel *lblAuthor;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblStatus;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnEnableDefaults;
    QPushButton *btnDisableAll;
    QPushButton *btnShowMore;
    QWidget *expandWidget;
    QVBoxLayout *verticalLayout_6;
    QLabel *lblDescription;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblIdentifier;
    QLabel *lblVersion;
    QLabel *lblWebsite;
    QFrame *line_2;
    QWidget *grpPipelines;
    QVBoxLayout *verticalLayout_7;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *btnDelete;
    QSpacerItem *horizontalSpacer;
    QLabel *label_13;
    QLabel *lblLicense;

    void setupUi(QWidget *ModManagerWidgetItem)
    {
        if (ModManagerWidgetItem->objectName().isEmpty())
            ModManagerWidgetItem->setObjectName(QStringLiteral("ModManagerWidgetItem"));
        ModManagerWidgetItem->resize(675, 391);
        ModManagerWidgetItem->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionCopyToProfile = new QAction(ModManagerWidgetItem);
        actionCopyToProfile->setObjectName(QStringLiteral("actionCopyToProfile"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("edit-copy");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionCopyToProfile->setIcon(icon);
        actionReinitialize = new QAction(ModManagerWidgetItem);
        actionReinitialize->setObjectName(QStringLiteral("actionReinitialize"));
        QIcon icon1;
        iconThemeName = QStringLiteral("run-build");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionReinitialize->setIcon(icon1);
        actionExportMod = new QAction(ModManagerWidgetItem);
        actionExportMod->setObjectName(QStringLiteral("actionExportMod"));
        QIcon icon2;
        iconThemeName = QStringLiteral("document-export");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionExportMod->setIcon(icon2);
        verticalLayout = new QVBoxLayout(ModManagerWidgetItem);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(ModManagerWidgetItem);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        mainWidget = new QWidget(frame);
        mainWidget->setObjectName(QStringLiteral("mainWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainWidget->sizePolicy().hasHeightForWidth());
        mainWidget->setSizePolicy(sizePolicy);
        mainWidget->setMinimumSize(QSize(0, 100));
        mainWidget->setMaximumSize(QSize(16777215, 120));
        horizontalLayout_2 = new QHBoxLayout(mainWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        btnSortUp = new QToolButton(mainWidget);
        btnSortUp->setObjectName(QStringLiteral("btnSortUp"));
        btnSortUp->setAutoRaise(true);
        btnSortUp->setArrowType(Qt::UpArrow);

        verticalLayout_5->addWidget(btnSortUp);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        btnSortDown = new QToolButton(mainWidget);
        btnSortDown->setObjectName(QStringLiteral("btnSortDown"));
        btnSortDown->setAutoRaise(true);
        btnSortDown->setArrowType(Qt::DownArrow);

        verticalLayout_5->addWidget(btnSortDown);


        horizontalLayout_2->addLayout(verticalLayout_5);

        lblIcon = new QLabel(mainWidget);
        lblIcon->setObjectName(QStringLiteral("lblIcon"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblIcon->sizePolicy().hasHeightForWidth());
        lblIcon->setSizePolicy(sizePolicy1);
        lblIcon->setMinimumSize(QSize(100, 100));
        lblIcon->setMaximumSize(QSize(100, 100));
        lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/resources/icons/mod-100.png")));
        lblIcon->setScaledContents(true);

        horizontalLayout_2->addWidget(lblIcon);

        verticalWidget = new QWidget(mainWidget);
        verticalWidget->setObjectName(QStringLiteral("verticalWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(verticalWidget->sizePolicy().hasHeightForWidth());
        verticalWidget->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(verticalWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, 20, -1, -1);
        lblName = new QLabel(verticalWidget);
        lblName->setObjectName(QStringLiteral("lblName"));
        QFont font;
        font.setPointSize(16);
        lblName->setFont(font);

        verticalLayout_4->addWidget(lblName);

        lblAuthor = new QLabel(verticalWidget);
        lblAuthor->setObjectName(QStringLiteral("lblAuthor"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lblAuthor->sizePolicy().hasHeightForWidth());
        lblAuthor->setSizePolicy(sizePolicy3);
        lblAuthor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_4->addWidget(lblAuthor);


        horizontalLayout_2->addWidget(verticalWidget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lblStatus = new QLabel(mainWidget);
        lblStatus->setObjectName(QStringLiteral("lblStatus"));
        lblStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(lblStatus);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnEnableDefaults = new QPushButton(mainWidget);
        btnEnableDefaults->setObjectName(QStringLiteral("btnEnableDefaults"));
        QIcon icon3;
        iconThemeName = QStringLiteral("dialog-ok");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnEnableDefaults->setIcon(icon3);

        horizontalLayout->addWidget(btnEnableDefaults);

        btnDisableAll = new QPushButton(mainWidget);
        btnDisableAll->setObjectName(QStringLiteral("btnDisableAll"));
        QIcon icon4;
        iconThemeName = QStringLiteral("dialog-cancel");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnDisableAll->setIcon(icon4);

        horizontalLayout->addWidget(btnDisableAll);

        btnShowMore = new QPushButton(mainWidget);
        btnShowMore->setObjectName(QStringLiteral("btnShowMore"));
        QIcon icon5;
        iconThemeName = QStringLiteral("arrow-down");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnShowMore->setIcon(icon5);
        btnShowMore->setCheckable(true);

        horizontalLayout->addWidget(btnShowMore);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addWidget(mainWidget);

        expandWidget = new QWidget(frame);
        expandWidget->setObjectName(QStringLiteral("expandWidget"));
        verticalLayout_6 = new QVBoxLayout(expandWidget);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        lblDescription = new QLabel(expandWidget);
        lblDescription->setObjectName(QStringLiteral("lblDescription"));
        lblDescription->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        lblDescription->setWordWrap(true);
        lblDescription->setOpenExternalLinks(true);

        verticalLayout_6->addWidget(lblDescription);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lblIdentifier = new QLabel(expandWidget);
        lblIdentifier->setObjectName(QStringLiteral("lblIdentifier"));
        QFont font1;
        font1.setItalic(true);
        lblIdentifier->setFont(font1);

        horizontalLayout_4->addWidget(lblIdentifier);

        lblVersion = new QLabel(expandWidget);
        lblVersion->setObjectName(QStringLiteral("lblVersion"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lblVersion->sizePolicy().hasHeightForWidth());
        lblVersion->setSizePolicy(sizePolicy4);

        horizontalLayout_4->addWidget(lblVersion);

        lblWebsite = new QLabel(expandWidget);
        lblWebsite->setObjectName(QStringLiteral("lblWebsite"));
        sizePolicy2.setHeightForWidth(lblWebsite->sizePolicy().hasHeightForWidth());
        lblWebsite->setSizePolicy(sizePolicy2);
        lblWebsite->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblWebsite->setOpenExternalLinks(true);

        horizontalLayout_4->addWidget(lblWebsite);


        verticalLayout_6->addLayout(horizontalLayout_4);

        line_2 = new QFrame(expandWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_2);

        grpPipelines = new QWidget(expandWidget);
        grpPipelines->setObjectName(QStringLiteral("grpPipelines"));
        verticalLayout_7 = new QVBoxLayout(grpPipelines);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, -1, 0, -1);

        verticalLayout_6->addWidget(grpPipelines);

        line = new QFrame(expandWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnDelete = new QToolButton(expandWidget);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        QIcon icon6;
        iconThemeName = QStringLiteral("list-remove");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon6 = QIcon::fromTheme(iconThemeName);
        } else {
            icon6.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnDelete->setIcon(icon6);
        btnDelete->setPopupMode(QToolButton::MenuButtonPopup);
        btnDelete->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_3->addWidget(btnDelete);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_13 = new QLabel(expandWidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_3->addWidget(label_13);

        lblLicense = new QLabel(expandWidget);
        lblLicense->setObjectName(QStringLiteral("lblLicense"));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        lblLicense->setFont(font2);

        horizontalLayout_3->addWidget(lblLicense);


        verticalLayout_6->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(expandWidget);


        verticalLayout->addWidget(frame);


        retranslateUi(ModManagerWidgetItem);

        QMetaObject::connectSlotsByName(ModManagerWidgetItem);
    } // setupUi

    void retranslateUi(QWidget *ModManagerWidgetItem)
    {
        ModManagerWidgetItem->setWindowTitle(QApplication::translate("ModManagerWidgetItem", "Form", 0));
        actionCopyToProfile->setText(QApplication::translate("ModManagerWidgetItem", "Copy to another profile", 0));
        actionReinitialize->setText(QApplication::translate("ModManagerWidgetItem", "Reinitialize modification", 0));
#ifndef QT_NO_TOOLTIP
        actionReinitialize->setToolTip(QApplication::translate("ModManagerWidgetItem", "Reinitializes this mod for development and debugging purposes", 0));
#endif // QT_NO_TOOLTIP
        actionExportMod->setText(QApplication::translate("ModManagerWidgetItem", "Export modification", 0));
#ifndef QT_NO_TOOLTIP
        actionExportMod->setToolTip(QApplication::translate("ModManagerWidgetItem", "Creates a distributable *.zip file with the contents of this mod.", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btnSortUp->setToolTip(QApplication::translate("ModManagerWidgetItem", "Priotizes this mod higher. Other mods with lower priority can overwrite files from this mod.", 0));
#endif // QT_NO_TOOLTIP
        btnSortUp->setText(QApplication::translate("ModManagerWidgetItem", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnSortDown->setToolTip(QApplication::translate("ModManagerWidgetItem", "Priotizes this mod lower. This mod can overwrite files with higher priority.", 0));
#endif // QT_NO_TOOLTIP
        btnSortDown->setText(QApplication::translate("ModManagerWidgetItem", "...", 0));
        lblIcon->setText(QString());
        lblName->setText(QApplication::translate("ModManagerWidgetItem", "Modification name", 0));
        lblAuthor->setText(QApplication::translate("ModManagerWidgetItem", "by Autor", 0));
        lblStatus->setText(QApplication::translate("ModManagerWidgetItem", "Status", 0));
#ifndef QT_NO_TOOLTIP
        btnEnableDefaults->setToolTip(QApplication::translate("ModManagerWidgetItem", "Enables the default content of this mod.", 0));
#endif // QT_NO_TOOLTIP
        btnEnableDefaults->setText(QApplication::translate("ModManagerWidgetItem", "Enable", 0));
#ifndef QT_NO_TOOLTIP
        btnDisableAll->setToolTip(QApplication::translate("ModManagerWidgetItem", "Disables this mod.", 0));
#endif // QT_NO_TOOLTIP
        btnDisableAll->setText(QApplication::translate("ModManagerWidgetItem", "Disable", 0));
        btnShowMore->setText(QApplication::translate("ModManagerWidgetItem", "Show more", 0));
        lblDescription->setText(QApplication::translate("ModManagerWidgetItem", "TextLabel", 0));
        lblIdentifier->setText(QApplication::translate("ModManagerWidgetItem", "TextLabel", 0));
        lblVersion->setText(QApplication::translate("ModManagerWidgetItem", "Version 1.0.0.0", 0));
        lblWebsite->setText(QApplication::translate("ModManagerWidgetItem", "<html><head/><body><p><a href=\"https://\"><span style=\" text-decoration: underline; color:#4c6b8a;\">Website</span></a></p></body></html>", 0));
#ifndef QT_NO_TOOLTIP
        btnDelete->setToolTip(QApplication::translate("ModManagerWidgetItem", "Deletes this modification.", 0));
#endif // QT_NO_TOOLTIP
        btnDelete->setText(QApplication::translate("ModManagerWidgetItem", "Delete modification", 0));
        label_13->setText(QApplication::translate("ModManagerWidgetItem", "Licensed under", 0));
        lblLicense->setText(QApplication::translate("ModManagerWidgetItem", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class ModManagerWidgetItem: public Ui_ModManagerWidgetItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODMANAGERWIDGETITEM_H

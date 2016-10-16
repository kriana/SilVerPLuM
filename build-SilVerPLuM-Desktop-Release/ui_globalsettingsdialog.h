/********************************************************************************
** Form generated from reading UI file 'globalsettingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLOBALSETTINGSDIALOG_H
#define UI_GLOBALSETTINGSDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GlobalSettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_4;
    QFormLayout *formLayout_4;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *appName;
    QLabel *appVersion;
    QLabel *label_9;
    QLabel *label_12;
    QLabel *label_11;
    QLabel *label_13;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QCheckBox *modsRedirectXNA;
    QLabel *label_5;
    QCheckBox *modsForceUnsupported;
    QLabel *label_6;
    QCheckBox *modsEnableFileGuard;
    QLabel *label_7;
    QCheckBox *modEnableDepCheck;
    QCheckBox *modDepCheckPriorityAware;
    QCheckBox *modDisablePrimeCache;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_3;
    QLabel *label_4;
    QCheckBox *runningBackupSDVSavegames;
    QCheckBox *runningBackupProfileSavegames;
    QSpacerItem *horizontalSpacer;
    QGroupBox *externalPrograms;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnAddProgram;
    QWidget *externalProgramsList;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GlobalSettingsDialog)
    {
        if (GlobalSettingsDialog->objectName().isEmpty())
            GlobalSettingsDialog->setObjectName(QStringLiteral("GlobalSettingsDialog"));
        GlobalSettingsDialog->resize(575, 370);
        QIcon icon;
        icon.addFile(QStringLiteral(":/resources/icons/application-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        GlobalSettingsDialog->setWindowIcon(icon);
        GlobalSettingsDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(GlobalSettingsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollArea = new QScrollArea(GlobalSettingsDialog);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, -252, 543, 570));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_4 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        formLayout_4 = new QFormLayout(groupBox_4);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(120, 0));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_8);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(120, 0));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_10);

        appName = new QLabel(groupBox_4);
        appName->setObjectName(QStringLiteral("appName"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, appName);

        appVersion = new QLabel(groupBox_4);
        appVersion->setObjectName(QStringLiteral("appVersion"));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, appVersion);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(120, 0));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, label_9);

        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setOpenExternalLinks(true);

        formLayout_4->setWidget(2, QFormLayout::FieldRole, label_12);

        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMinimumSize(QSize(120, 0));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, label_11);

        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setOpenExternalLinks(true);

        formLayout_4->setWidget(3, QFormLayout::FieldRole, label_13);


        verticalLayout_2->addWidget(groupBox_4);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(120, 0));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        modsRedirectXNA = new QCheckBox(groupBox_2);
        modsRedirectXNA->setObjectName(QStringLiteral("modsRedirectXNA"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, modsRedirectXNA);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(120, 0));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_5);

        modsForceUnsupported = new QCheckBox(groupBox_2);
        modsForceUnsupported->setObjectName(QStringLiteral("modsForceUnsupported"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, modsForceUnsupported);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(120, 0));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_6);

        modsEnableFileGuard = new QCheckBox(groupBox_2);
        modsEnableFileGuard->setObjectName(QStringLiteral("modsEnableFileGuard"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, modsEnableFileGuard);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(120, 0));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_7);

        modEnableDepCheck = new QCheckBox(groupBox_2);
        modEnableDepCheck->setObjectName(QStringLiteral("modEnableDepCheck"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, modEnableDepCheck);

        modDepCheckPriorityAware = new QCheckBox(groupBox_2);
        modDepCheckPriorityAware->setObjectName(QStringLiteral("modDepCheckPriorityAware"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, modDepCheckPriorityAware);

        modDisablePrimeCache = new QCheckBox(groupBox_2);
        modDisablePrimeCache->setObjectName(QStringLiteral("modDisablePrimeCache"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, modDisablePrimeCache);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        formLayout_3 = new QFormLayout(groupBox_3);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(120, 0));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_4);

        runningBackupSDVSavegames = new QCheckBox(groupBox_3);
        runningBackupSDVSavegames->setObjectName(QStringLiteral("runningBackupSDVSavegames"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, runningBackupSDVSavegames);

        runningBackupProfileSavegames = new QCheckBox(groupBox_3);
        runningBackupProfileSavegames->setObjectName(QStringLiteral("runningBackupProfileSavegames"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, runningBackupProfileSavegames);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout_3->setItem(1, QFormLayout::LabelRole, horizontalSpacer);


        verticalLayout_2->addWidget(groupBox_3);

        externalPrograms = new QGroupBox(scrollAreaWidgetContents);
        externalPrograms->setObjectName(QStringLiteral("externalPrograms"));
        verticalLayout_3 = new QVBoxLayout(externalPrograms);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widget = new QWidget(externalPrograms);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, 0, -1);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnAddProgram = new QPushButton(widget);
        btnAddProgram->setObjectName(QStringLiteral("btnAddProgram"));
        QIcon icon1;
        QString iconThemeName = QStringLiteral("list-add");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnAddProgram->setIcon(icon1);

        horizontalLayout->addWidget(btnAddProgram);


        verticalLayout_3->addWidget(widget);

        externalProgramsList = new QWidget(externalPrograms);
        externalProgramsList->setObjectName(QStringLiteral("externalProgramsList"));
        verticalLayout_4 = new QVBoxLayout(externalProgramsList);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, -1, 0, -1);

        verticalLayout_3->addWidget(externalProgramsList);


        verticalLayout_2->addWidget(externalPrograms);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        buttonBox = new QDialogButtonBox(GlobalSettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Discard);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(GlobalSettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GlobalSettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GlobalSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GlobalSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *GlobalSettingsDialog)
    {
        GlobalSettingsDialog->setWindowTitle(QApplication::translate("GlobalSettingsDialog", "Application Settings", 0));
        groupBox_4->setTitle(QApplication::translate("GlobalSettingsDialog", "Application info", 0));
        label_8->setText(QApplication::translate("GlobalSettingsDialog", "Version", 0));
        label_10->setText(QApplication::translate("GlobalSettingsDialog", "Application", 0));
        appName->setText(QApplication::translate("GlobalSettingsDialog", "SilVerPLuM", 0));
        appVersion->setText(QApplication::translate("GlobalSettingsDialog", "<Version>", 0));
        label_9->setText(QApplication::translate("GlobalSettingsDialog", "Website", 0));
        label_12->setText(QApplication::translate("GlobalSettingsDialog", "<html><head/><body><p><a href=\"https://github.com/rumangerst/SilVerPLuM\"><span style=\" text-decoration: underline; color:#4c6b8a;\">https://github.com/rumangerst/SilVerPLuM</span></a></p></body></html>", 0));
        label_11->setText(QApplication::translate("GlobalSettingsDialog", "License", 0));
        label_13->setText(QApplication::translate("GlobalSettingsDialog", "<html><head/><body><p><a href=\"https://github.com/rumangerst/SilVerPLuM/blob/master/LICENSE\"><span style=\" text-decoration: underline; color:#4c6b8a;\">GPLv3</span></a></p></body></html>", 0));
        groupBox_2->setTitle(QApplication::translate("GlobalSettingsDialog", "Mods", 0));
        label_3->setText(QApplication::translate("GlobalSettingsDialog", "DLL mods", 0));
#ifndef QT_NO_TOOLTIP
        modsRedirectXNA->setToolTip(QApplication::translate("GlobalSettingsDialog", "<html><head/><body><p>If enabled, dll-compile mods will translate between XNA and MonoGame depending on profile settings.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        modsRedirectXNA->setText(QApplication::translate("GlobalSettingsDialog", "Redirect XNA to MonoGame and vice versa", 0));
        label_5->setText(QApplication::translate("GlobalSettingsDialog", "Hacks", 0));
#ifndef QT_NO_TOOLTIP
        modsForceUnsupported->setToolTip(QApplication::translate("GlobalSettingsDialog", "<html><head/><body><p>If enabled, all content can be enabled despite not supported by your platform.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        modsForceUnsupported->setText(QApplication::translate("GlobalSettingsDialog", "Force unsupported mods to be installable", 0));
        label_6->setText(QApplication::translate("GlobalSettingsDialog", "Security", 0));
#ifndef QT_NO_TOOLTIP
        modsEnableFileGuard->setToolTip(QApplication::translate("GlobalSettingsDialog", "Enables checking for paths that may break out of the game or profile directories. Also protects all game files except in Content and modded directories.", 0));
#endif // QT_NO_TOOLTIP
        modsEnableFileGuard->setText(QApplication::translate("GlobalSettingsDialog", "Enable file protection", 0));
        label_7->setText(QApplication::translate("GlobalSettingsDialog", "Dependencies", 0));
#ifndef QT_NO_TOOLTIP
        modEnableDepCheck->setToolTip(QApplication::translate("GlobalSettingsDialog", "<html><head/><body><p>If enabled, mod depencencies will be checked.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        modEnableDepCheck->setText(QApplication::translate("GlobalSettingsDialog", "Enable dependency check", 0));
#ifndef QT_NO_TOOLTIP
        modDepCheckPriorityAware->setToolTip(QApplication::translate("GlobalSettingsDialog", "<html><head/><body><p>If enabled, the dependency check will check if mods have the right order.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        modDepCheckPriorityAware->setText(QApplication::translate("GlobalSettingsDialog", "Check based on priority", 0));
#ifndef QT_NO_TOOLTIP
        modDisablePrimeCache->setToolTip(QApplication::translate("GlobalSettingsDialog", "<html><head/><body><p>If enabled, all mods re-activate on enabling and starting a launcher.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        modDisablePrimeCache->setText(QApplication::translate("GlobalSettingsDialog", "Always rebuild mods on activation", 0));
        groupBox_3->setTitle(QApplication::translate("GlobalSettingsDialog", "Running", 0));
        label_4->setText(QApplication::translate("GlobalSettingsDialog", "Backup", 0));
#ifndef QT_NO_TOOLTIP
        runningBackupSDVSavegames->setToolTip(QApplication::translate("GlobalSettingsDialog", "<html><head/><body><p>If enabled, existing savegames will be backed up into a temporary directory before starting the launcher.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        runningBackupSDVSavegames->setText(QApplication::translate("GlobalSettingsDialog", "Backup savegames in savegame folder", 0));
#ifndef QT_NO_TOOLTIP
        runningBackupProfileSavegames->setToolTip(QApplication::translate("GlobalSettingsDialog", "<html><head/><body><p>If enabled, savegames in your profile folder are backed up into a temporary directory before moving savegames after launch.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        runningBackupProfileSavegames->setText(QApplication::translate("GlobalSettingsDialog", "Backup savegames in profile folder", 0));
        externalPrograms->setTitle(QApplication::translate("GlobalSettingsDialog", "Programs", 0));
        btnAddProgram->setText(QApplication::translate("GlobalSettingsDialog", "Add program", 0));
    } // retranslateUi

};

namespace Ui {
    class GlobalSettingsDialog: public Ui_GlobalSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLOBALSETTINGSDIALOG_H

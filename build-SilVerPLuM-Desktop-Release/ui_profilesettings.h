/********************************************************************************
** Form generated from reading UI file 'profilesettings.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILESETTINGS_H
#define UI_PROFILESETTINGS_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "fileselectoredit.h"
#include "markdowntexteditor.h"

QT_BEGIN_NAMESPACE

class Ui_ProfileSettings
{
public:
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLineEdit *profileName;
    QLabel *label_4;
    QLabel *label_5;
    FileSelectorEdit *profileDirectory;
    MarkdownTextEditor *profileDescription;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    FileSelectorEdit *sdvApplicationDirectory;
    QLabel *label_2;
    FileSelectorEdit *sdvSavegameDirectory;
    QLabel *label_8;
    QComboBox *sdvVersion;
    QSpacerItem *horizontalSpacer;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_6;
    QPushButton *btnSDVAutodetect;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *sdvTechXNA;
    QRadioButton *sdvTechMonoGame;
    QLabel *label_12;
    FileSelectorEdit *sdvUserDataDirectory;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QWidget *launchersLauncherList;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton;
    QGroupBox *groupBox_4;
    QFormLayout *formLayout_3;
    QLabel *label_10;
    QCheckBox *backupBeforeStart;
    QLabel *label_11;
    QCheckBox *backupCheckExisting;
    QSpinBox *backupInterval;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *ProfileSettings)
    {
        if (ProfileSettings->objectName().isEmpty())
            ProfileSettings->setObjectName(QStringLiteral("ProfileSettings"));
        ProfileSettings->resize(570, 490);
        ProfileSettings->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout_2 = new QVBoxLayout(ProfileSettings);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        scrollArea = new QScrollArea(ProfileSettings);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, -376, 538, 814));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(140, 0));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        profileName = new QLineEdit(groupBox_2);
        profileName->setObjectName(QStringLiteral("profileName"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, profileName);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(140, 0));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(140, 0));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_5);

        profileDirectory = new FileSelectorEdit(groupBox_2);
        profileDirectory->setObjectName(QStringLiteral("profileDirectory"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(profileDirectory->sizePolicy().hasHeightForWidth());
        profileDirectory->setSizePolicy(sizePolicy);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, profileDirectory);

        profileDescription = new MarkdownTextEditor(groupBox_2);
        profileDescription->setObjectName(QStringLiteral("profileDescription"));
        profileDescription->setMinimumSize(QSize(0, 200));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, profileDescription);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(140, 0));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        sdvApplicationDirectory = new FileSelectorEdit(groupBox);
        sdvApplicationDirectory->setObjectName(QStringLiteral("sdvApplicationDirectory"));
        sizePolicy.setHeightForWidth(sdvApplicationDirectory->sizePolicy().hasHeightForWidth());
        sdvApplicationDirectory->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::FieldRole, sdvApplicationDirectory);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(140, 0));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        sdvSavegameDirectory = new FileSelectorEdit(groupBox);
        sdvSavegameDirectory->setObjectName(QStringLiteral("sdvSavegameDirectory"));
        sizePolicy.setHeightForWidth(sdvSavegameDirectory->sizePolicy().hasHeightForWidth());
        sdvSavegameDirectory->setSizePolicy(sizePolicy);

        formLayout->setWidget(1, QFormLayout::FieldRole, sdvSavegameDirectory);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(140, 0));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_8);

        sdvVersion = new QComboBox(groupBox);
        sdvVersion->setObjectName(QStringLiteral("sdvVersion"));
        sdvVersion->setEditable(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, sdvVersion);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(4, QFormLayout::LabelRole, horizontalSpacer);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(4, QFormLayout::FieldRole, label_9);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(140, 0));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(140, 0));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_6);

        btnSDVAutodetect = new QPushButton(groupBox);
        btnSDVAutodetect->setObjectName(QStringLiteral("btnSDVAutodetect"));
        btnSDVAutodetect->setMinimumSize(QSize(0, 0));
        QIcon icon;
        QString iconThemeName = QStringLiteral("edit-find");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnSDVAutodetect->setIcon(icon);

        formLayout->setWidget(8, QFormLayout::FieldRole, btnSDVAutodetect);

        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        sdvTechXNA = new QRadioButton(widget);
        sdvTechXNA->setObjectName(QStringLiteral("sdvTechXNA"));

        verticalLayout_4->addWidget(sdvTechXNA);

        sdvTechMonoGame = new QRadioButton(widget);
        sdvTechMonoGame->setObjectName(QStringLiteral("sdvTechMonoGame"));

        verticalLayout_4->addWidget(sdvTechMonoGame);


        formLayout->setWidget(6, QFormLayout::FieldRole, widget);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMinimumSize(QSize(140, 0));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_12);

        sdvUserDataDirectory = new FileSelectorEdit(groupBox);
        sdvUserDataDirectory->setObjectName(QStringLiteral("sdvUserDataDirectory"));
        sizePolicy.setHeightForWidth(sdvUserDataDirectory->sizePolicy().hasHeightForWidth());
        sdvUserDataDirectory->setSizePolicy(sizePolicy);

        formLayout->setWidget(2, QFormLayout::FieldRole, sdvUserDataDirectory);


        verticalLayout->addWidget(groupBox);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        launchersLauncherList = new QWidget(groupBox_3);
        launchersLauncherList->setObjectName(QStringLiteral("launchersLauncherList"));
        sizePolicy.setHeightForWidth(launchersLauncherList->sizePolicy().hasHeightForWidth());
        launchersLauncherList->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(launchersLauncherList);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(launchersLauncherList);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        verticalLayout_3->addWidget(radioButton);


        gridLayout->addWidget(launchersLauncherList, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        formLayout_3 = new QFormLayout(groupBox_4);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(140, 0));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_10);

        backupBeforeStart = new QCheckBox(groupBox_4);
        backupBeforeStart->setObjectName(QStringLiteral("backupBeforeStart"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, backupBeforeStart);

        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMinimumSize(QSize(140, 0));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_11);

        backupCheckExisting = new QCheckBox(groupBox_4);
        backupCheckExisting->setObjectName(QStringLiteral("backupCheckExisting"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, backupCheckExisting);

        backupInterval = new QSpinBox(groupBox_4);
        backupInterval->setObjectName(QStringLiteral("backupInterval"));
        backupInterval->setMaximum(999);
        backupInterval->setValue(1);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, backupInterval);


        verticalLayout->addWidget(groupBox_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        buttonBox = new QDialogButtonBox(ProfileSettings);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Discard);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(ProfileSettings);

        QMetaObject::connectSlotsByName(ProfileSettings);
    } // setupUi

    void retranslateUi(QWidget *ProfileSettings)
    {
        ProfileSettings->setWindowTitle(QApplication::translate("ProfileSettings", "Form", 0));
        groupBox_2->setTitle(QApplication::translate("ProfileSettings", "Profile", 0));
        label_3->setText(QApplication::translate("ProfileSettings", "Name", 0));
#ifndef QT_NO_TOOLTIP
        profileName->setToolTip(QApplication::translate("ProfileSettings", "The display name of this profile.", 0));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("ProfileSettings", "Description", 0));
        label_5->setText(QApplication::translate("ProfileSettings", "Directory", 0));
#ifndef QT_NO_TOOLTIP
        profileDirectory->setToolTip(QApplication::translate("ProfileSettings", "The directory this profile is stored in.", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        profileDescription->setToolTip(QApplication::translate("ProfileSettings", "The description of this profile. You can use Markdown syntax and HTML.", 0));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("ProfileSettings", "Stardew Valley", 0));
        label->setText(QApplication::translate("ProfileSettings", "Application directory", 0));
#ifndef QT_NO_TOOLTIP
        sdvApplicationDirectory->setToolTip(QApplication::translate("ProfileSettings", "The directory that contains the Stardew Valley installation.", 0));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("ProfileSettings", "Savegame directory", 0));
#ifndef QT_NO_TOOLTIP
        sdvSavegameDirectory->setToolTip(QApplication::translate("ProfileSettings", "The directory that contains the Stardew Valley savegames.", 0));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("ProfileSettings", "Version", 0));
#ifndef QT_NO_TOOLTIP
        sdvVersion->setToolTip(QApplication::translate("ProfileSettings", "The Stardew Valley version that is installed in the application directory.", 0));
#endif // QT_NO_TOOLTIP
        label_9->setText(QApplication::translate("ProfileSettings", "Set version to 0 to disable version checks", 0));
        label_7->setText(QApplication::translate("ProfileSettings", "Technology", 0));
        label_6->setText(QApplication::translate("ProfileSettings", "Utilities", 0));
        btnSDVAutodetect->setText(QApplication::translate("ProfileSettings", "Try to auto-detect", 0));
#ifndef QT_NO_TOOLTIP
        sdvTechXNA->setToolTip(QApplication::translate("ProfileSettings", "XNA technology. Default for Windows.", 0));
#endif // QT_NO_TOOLTIP
        sdvTechXNA->setText(QApplication::translate("ProfileSettings", "X&NA", 0));
#ifndef QT_NO_TOOLTIP
        sdvTechMonoGame->setToolTip(QApplication::translate("ProfileSettings", "MonoGame technology. Default for Mac and Linux.", 0));
#endif // QT_NO_TOOLTIP
        sdvTechMonoGame->setText(QApplication::translate("ProfileSettings", "&MonoGame", 0));
        label_12->setText(QApplication::translate("ProfileSettings", "User data directory", 0));
#ifndef QT_NO_TOOLTIP
        sdvUserDataDirectory->setToolTip(QApplication::translate("ProfileSettings", "The directory that contains other user data of Stardew Valley.", 0));
#endif // QT_NO_TOOLTIP
        groupBox_3->setTitle(QApplication::translate("ProfileSettings", "Launchers", 0));
        radioButton->setText(QApplication::translate("ProfileSettings", "&RadioButton", 0));
        groupBox_4->setTitle(QApplication::translate("ProfileSettings", "Savegames", 0));
        label_10->setText(QApplication::translate("ProfileSettings", "Auto-backup", 0));
#ifndef QT_NO_TOOLTIP
        backupBeforeStart->setToolTip(QApplication::translate("ProfileSettings", "Creates a backup of your savegame before it starts.", 0));
#endif // QT_NO_TOOLTIP
        backupBeforeStart->setText(QApplication::translate("ProfileSettings", "Backup before game starts", 0));
        label_11->setText(QApplication::translate("ProfileSettings", "Backup", 0));
#ifndef QT_NO_TOOLTIP
        backupCheckExisting->setToolTip(QApplication::translate("ProfileSettings", "If enabled, backups won't be created if nothing changed. But you can always create manual backups.", 0));
#endif // QT_NO_TOOLTIP
        backupCheckExisting->setText(QApplication::translate("ProfileSettings", "Avoid unnecessary backups", 0));
#ifndef QT_NO_TOOLTIP
        backupInterval->setToolTip(QApplication::translate("ProfileSettings", "Backup every x minutes while playing the game.", 0));
#endif // QT_NO_TOOLTIP
        backupInterval->setSpecialValueText(QApplication::translate("ProfileSettings", "No timed backup", 0));
        backupInterval->setSuffix(QApplication::translate("ProfileSettings", " min", 0));
        backupInterval->setPrefix(QApplication::translate("ProfileSettings", "Backup interval: ", 0));
    } // retranslateUi

};

namespace Ui {
    class ProfileSettings: public Ui_ProfileSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILESETTINGS_H

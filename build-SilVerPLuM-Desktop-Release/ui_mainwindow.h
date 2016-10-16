/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "modmanagerwidget.h"
#include "profilemanagerwidget.h"
#include "profilesettings.h"
#include "savegamemanagerwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenPasswordGenerator;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *mainTabWidget;
    QWidget *tabPlay;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QStackedWidget *playStackedWidget;
    QWidget *playLauncherPage;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *btnApplicationSettings;
    QToolButton *btnShowLog;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *cmbProfile;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_5;
    QLabel *profileInfo;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *label_2;
    QToolButton *btnPlay;
    QSpacerItem *horizontalSpacer_2;
    QWidget *playLogPage;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *playLogLog;
    QProgressBar *playLogProgress;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *playLogStop;
    QPushButton *playLogClose;
    QWidget *tabConfigure;
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    ProfileManagerWidget *configProfileList;
    ProfileSettings *configProfileConfig;
    QWidget *tabMod;
    QGridLayout *gridLayout_4;
    QSplitter *splitter_2;
    ProfileManagerWidget *modProfileList;
    ModManagerWidget *modManager;
    QWidget *tabManage;
    QGridLayout *gridLayout_6;
    QSplitter *splitter_3;
    ProfileManagerWidget *manageProfileList;
    SavegameManagerWidget *savegameManager;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(680, 402);
        QIcon icon;
        icon.addFile(QStringLiteral(":/resources/icons/application-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionOpenPasswordGenerator = new QAction(MainWindow);
        actionOpenPasswordGenerator->setObjectName(QStringLiteral("actionOpenPasswordGenerator"));
        QIcon icon1;
        QString iconThemeName = QStringLiteral("document-encrypt");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionOpenPasswordGenerator->setIcon(icon1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mainTabWidget = new QTabWidget(centralWidget);
        mainTabWidget->setObjectName(QStringLiteral("mainTabWidget"));
        mainTabWidget->setTabPosition(QTabWidget::South);
        tabPlay = new QWidget();
        tabPlay->setObjectName(QStringLiteral("tabPlay"));
        tabPlay->setAutoFillBackground(false);
        tabPlay->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(tabPlay);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(tabPlay);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        playStackedWidget = new QStackedWidget(widget);
        playStackedWidget->setObjectName(QStringLiteral("playStackedWidget"));
        playLauncherPage = new QWidget();
        playLauncherPage->setObjectName(QStringLiteral("playLauncherPage"));
        verticalLayout_2 = new QVBoxLayout(playLauncherPage);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnApplicationSettings = new QToolButton(playLauncherPage);
        btnApplicationSettings->setObjectName(QStringLiteral("btnApplicationSettings"));
        QIcon icon2;
        iconThemeName = QStringLiteral("configure");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnApplicationSettings->setIcon(icon2);
        btnApplicationSettings->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnApplicationSettings->setAutoRaise(true);

        horizontalLayout_2->addWidget(btnApplicationSettings);

        btnShowLog = new QToolButton(playLauncherPage);
        btnShowLog->setObjectName(QStringLiteral("btnShowLog"));
        QIcon icon3;
        iconThemeName = QStringLiteral("view-list-text");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnShowLog->setIcon(icon3);
        btnShowLog->setPopupMode(QToolButton::MenuButtonPopup);
        btnShowLog->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnShowLog->setAutoRaise(true);

        horizontalLayout_2->addWidget(btnShowLog);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        cmbProfile = new QComboBox(playLauncherPage);
        cmbProfile->setObjectName(QStringLiteral("cmbProfile"));
        cmbProfile->setMinimumSize(QSize(150, 0));

        horizontalLayout_2->addWidget(cmbProfile);


        verticalLayout_2->addLayout(horizontalLayout_2);

        scrollArea = new QScrollArea(playLauncherPage);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 624, 195));
        scrollAreaWidgetContents->setAutoFillBackground(false);
        scrollAreaWidgetContents->setStyleSheet(QStringLiteral(""));
        gridLayout_5 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        profileInfo = new QLabel(scrollAreaWidgetContents);
        profileInfo->setObjectName(QStringLiteral("profileInfo"));
        profileInfo->setMaximumSize(QSize(800, 16777215));
        profileInfo->setTextFormat(Qt::RichText);
        profileInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        profileInfo->setWordWrap(true);

        gridLayout_5->addWidget(profileInfo, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget_3 = new QWidget(playLauncherPage);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy1);
        horizontalLayout_4 = new QHBoxLayout(widget_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(widget_3);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(64, 64));
        label->setMaximumSize(QSize(64, 64));
        label->setPixmap(QPixmap(QString::fromUtf8(":/resources/icons/application-128.png")));
        label->setScaledContents(true);

        horizontalLayout_4->addWidget(label);

        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);


        horizontalLayout->addWidget(widget_3);

        btnPlay = new QToolButton(playLauncherPage);
        btnPlay->setObjectName(QStringLiteral("btnPlay"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnPlay->sizePolicy().hasHeightForWidth());
        btnPlay->setSizePolicy(sizePolicy3);
        btnPlay->setMinimumSize(QSize(150, 70));
        btnPlay->setBaseSize(QSize(0, 0));
        QFont font;
        font.setPointSize(16);
        btnPlay->setFont(font);
        btnPlay->setPopupMode(QToolButton::MenuButtonPopup);
        btnPlay->setArrowType(Qt::NoArrow);

        horizontalLayout->addWidget(btnPlay);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        playStackedWidget->addWidget(playLauncherPage);
        playLogPage = new QWidget();
        playLogPage->setObjectName(QStringLiteral("playLogPage"));
        verticalLayout_3 = new QVBoxLayout(playLogPage);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        playLogLog = new QTreeWidget(playLogPage);
        playLogLog->setObjectName(QStringLiteral("playLogLog"));
        playLogLog->setEditTriggers(QAbstractItemView::NoEditTriggers);
        playLogLog->setColumnCount(6);

        verticalLayout_3->addWidget(playLogLog);

        playLogProgress = new QProgressBar(playLogPage);
        playLogProgress->setObjectName(QStringLiteral("playLogProgress"));
        playLogProgress->setMaximum(0);
        playLogProgress->setValue(0);
        playLogProgress->setTextVisible(false);

        verticalLayout_3->addWidget(playLogProgress);

        widget_2 = new QWidget(playLogPage);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        playLogStop = new QPushButton(widget_2);
        playLogStop->setObjectName(QStringLiteral("playLogStop"));
        QIcon icon4;
        iconThemeName = QStringLiteral("dialog-cancel");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        playLogStop->setIcon(icon4);

        horizontalLayout_3->addWidget(playLogStop);

        playLogClose = new QPushButton(widget_2);
        playLogClose->setObjectName(QStringLiteral("playLogClose"));
        QIcon icon5;
        iconThemeName = QStringLiteral("window-close");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        playLogClose->setIcon(icon5);

        horizontalLayout_3->addWidget(playLogClose);


        verticalLayout_3->addWidget(widget_2);

        playStackedWidget->addWidget(playLogPage);

        gridLayout_3->addWidget(playStackedWidget, 0, 0, 1, 1);


        verticalLayout->addWidget(widget);

        mainTabWidget->addTab(tabPlay, QString());
        tabConfigure = new QWidget();
        tabConfigure->setObjectName(QStringLiteral("tabConfigure"));
        gridLayout_2 = new QGridLayout(tabConfigure);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter = new QSplitter(tabConfigure);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        configProfileList = new ProfileManagerWidget(splitter);
        configProfileList->setObjectName(QStringLiteral("configProfileList"));
        splitter->addWidget(configProfileList);
        configProfileConfig = new ProfileSettings(splitter);
        configProfileConfig->setObjectName(QStringLiteral("configProfileConfig"));
        splitter->addWidget(configProfileConfig);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);

        mainTabWidget->addTab(tabConfigure, QString());
        tabMod = new QWidget();
        tabMod->setObjectName(QStringLiteral("tabMod"));
        gridLayout_4 = new QGridLayout(tabMod);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        splitter_2 = new QSplitter(tabMod);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        modProfileList = new ProfileManagerWidget(splitter_2);
        modProfileList->setObjectName(QStringLiteral("modProfileList"));
        splitter_2->addWidget(modProfileList);
        modManager = new ModManagerWidget(splitter_2);
        modManager->setObjectName(QStringLiteral("modManager"));
        splitter_2->addWidget(modManager);

        gridLayout_4->addWidget(splitter_2, 0, 0, 1, 1);

        mainTabWidget->addTab(tabMod, QString());
        tabManage = new QWidget();
        tabManage->setObjectName(QStringLiteral("tabManage"));
        gridLayout_6 = new QGridLayout(tabManage);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        splitter_3 = new QSplitter(tabManage);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        manageProfileList = new ProfileManagerWidget(splitter_3);
        manageProfileList->setObjectName(QStringLiteral("manageProfileList"));
        splitter_3->addWidget(manageProfileList);
        savegameManager = new SavegameManagerWidget(splitter_3);
        savegameManager->setObjectName(QStringLiteral("savegameManager"));
        splitter_3->addWidget(savegameManager);

        gridLayout_6->addWidget(splitter_3, 0, 0, 1, 1);

        mainTabWidget->addTab(tabManage, QString());

        gridLayout->addWidget(mainTabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        mainTabWidget->setCurrentIndex(0);
        playStackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SilVerPLuM", 0));
        actionOpenPasswordGenerator->setText(QApplication::translate("MainWindow", "Encryped content password generator", 0));
#ifndef QT_NO_TOOLTIP
        actionOpenPasswordGenerator->setToolTip(QApplication::translate("MainWindow", "If you want to distribute encrypted content, you will need to supply a password. This tool will build a password out of the actual password.", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btnApplicationSettings->setToolTip(QApplication::translate("MainWindow", "Shows the application settings dialog", 0));
#endif // QT_NO_TOOLTIP
        btnApplicationSettings->setText(QApplication::translate("MainWindow", "Application settings", 0));
#ifndef QT_NO_TOOLTIP
        btnShowLog->setToolTip(QApplication::translate("MainWindow", "Opens the log of the current profile, containing information about errors and other general information.", 0));
#endif // QT_NO_TOOLTIP
        btnShowLog->setText(QApplication::translate("MainWindow", "Profile log", 0));
#ifndef QT_NO_TOOLTIP
        cmbProfile->setToolTip(QApplication::translate("MainWindow", "Select the profile you want to launch.", 0));
#endif // QT_NO_TOOLTIP
        profileInfo->setText(QString());
        label->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">SilVerPLuM<br/></span><span style=\" font-size:8pt;\">Stardew Valley launcher</span></p></body></html>", 0));
#ifndef QT_NO_TOOLTIP
        btnPlay->setToolTip(QApplication::translate("MainWindow", "Click to start the currently selected launcher. Click on the arrow to select another launcher.", 0));
#endif // QT_NO_TOOLTIP
        btnPlay->setText(QApplication::translate("MainWindow", "Play", 0));
        QTreeWidgetItem *___qtreewidgetitem = playLogLog->headerItem();
        ___qtreewidgetitem->setText(5, QApplication::translate("MainWindow", "Message", 0));
        ___qtreewidgetitem->setText(4, QApplication::translate("MainWindow", "Operation", 0));
        ___qtreewidgetitem->setText(3, QApplication::translate("MainWindow", "Subcomponent", 0));
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "Component", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Time", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Type", 0));
        label_3->setText(QApplication::translate("MainWindow", "You will find more information in the 'Profile log'", 0));
        playLogStop->setText(QApplication::translate("MainWindow", "Force stop", 0));
        playLogClose->setText(QApplication::translate("MainWindow", "Close", 0));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tabPlay), QApplication::translate("MainWindow", "Play", 0));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tabConfigure), QApplication::translate("MainWindow", "Configure", 0));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tabMod), QApplication::translate("MainWindow", "Modify", 0));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tabManage), QApplication::translate("MainWindow", "Manage", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'profilemanagerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILEMANAGERWIDGET_H
#define UI_PROFILEMANAGERWIDGET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProfileManagerWidget
{
public:
    QAction *actionImport;
    QVBoxLayout *verticalLayout;
    QListWidget *configProfileList;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *profileAdd;
    QToolButton *profileClone;
    QToolButton *btnExport;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *profileDelete;

    void setupUi(QWidget *ProfileManagerWidget)
    {
        if (ProfileManagerWidget->objectName().isEmpty())
            ProfileManagerWidget->setObjectName(QStringLiteral("ProfileManagerWidget"));
        ProfileManagerWidget->resize(400, 300);
        ProfileManagerWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionImport = new QAction(ProfileManagerWidget);
        actionImport->setObjectName(QStringLiteral("actionImport"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("document-open");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionImport->setIcon(icon);
        verticalLayout = new QVBoxLayout(ProfileManagerWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        configProfileList = new QListWidget(ProfileManagerWidget);
        configProfileList->setObjectName(QStringLiteral("configProfileList"));

        verticalLayout->addWidget(configProfileList);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        profileAdd = new QToolButton(ProfileManagerWidget);
        profileAdd->setObjectName(QStringLiteral("profileAdd"));
        QIcon icon1;
        iconThemeName = QStringLiteral("list-add");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        profileAdd->setIcon(icon1);
        profileAdd->setPopupMode(QToolButton::MenuButtonPopup);
        profileAdd->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_3->addWidget(profileAdd);

        profileClone = new QToolButton(ProfileManagerWidget);
        profileClone->setObjectName(QStringLiteral("profileClone"));
        QIcon icon2;
        iconThemeName = QStringLiteral("edit-copy");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        profileClone->setIcon(icon2);

        horizontalLayout_3->addWidget(profileClone);

        btnExport = new QToolButton(ProfileManagerWidget);
        btnExport->setObjectName(QStringLiteral("btnExport"));
        QIcon icon3;
        iconThemeName = QStringLiteral("document-save-as");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnExport->setIcon(icon3);

        horizontalLayout_3->addWidget(btnExport);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        profileDelete = new QToolButton(ProfileManagerWidget);
        profileDelete->setObjectName(QStringLiteral("profileDelete"));
        QIcon icon4;
        iconThemeName = QStringLiteral("list-remove");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        profileDelete->setIcon(icon4);

        horizontalLayout_3->addWidget(profileDelete);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(ProfileManagerWidget);

        QMetaObject::connectSlotsByName(ProfileManagerWidget);
    } // setupUi

    void retranslateUi(QWidget *ProfileManagerWidget)
    {
        ProfileManagerWidget->setWindowTitle(QApplication::translate("ProfileManagerWidget", "Form", 0));
        actionImport->setText(QApplication::translate("ProfileManagerWidget", "Import from file", 0));
#ifndef QT_NO_TOOLTIP
        actionImport->setToolTip(QApplication::translate("ProfileManagerWidget", "Import a profile from file", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        profileAdd->setToolTip(QApplication::translate("ProfileManagerWidget", "Creates a new profile", 0));
#endif // QT_NO_TOOLTIP
        profileAdd->setText(QApplication::translate("ProfileManagerWidget", "New profile", 0));
#ifndef QT_NO_TOOLTIP
        profileClone->setToolTip(QApplication::translate("ProfileManagerWidget", "Creates a copy of the selected profile.", 0));
#endif // QT_NO_TOOLTIP
        profileClone->setText(QApplication::translate("ProfileManagerWidget", "...", 0));
#ifndef QT_NO_TOOLTIP
        btnExport->setToolTip(QApplication::translate("ProfileManagerWidget", "Exports the selected profile to a *.zip file.", 0));
#endif // QT_NO_TOOLTIP
        btnExport->setText(QApplication::translate("ProfileManagerWidget", "...", 0));
#ifndef QT_NO_TOOLTIP
        profileDelete->setToolTip(QApplication::translate("ProfileManagerWidget", "Deletes the selected profile.", 0));
#endif // QT_NO_TOOLTIP
        profileDelete->setText(QApplication::translate("ProfileManagerWidget", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class ProfileManagerWidget: public Ui_ProfileManagerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILEMANAGERWIDGET_H

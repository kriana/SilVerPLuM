/********************************************************************************
** Form generated from reading UI file 'fileselectoredit.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESELECTOREDIT_H
#define UI_FILESELECTOREDIT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileSelectorEdit
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *pathNotFound;
    QLineEdit *pathEdit;
    QToolButton *pathSelect;
    QToolButton *pathOpen;

    void setupUi(QWidget *FileSelectorEdit)
    {
        if (FileSelectorEdit->objectName().isEmpty())
            FileSelectorEdit->setObjectName(QStringLiteral("FileSelectorEdit"));
        FileSelectorEdit->resize(627, 228);
        FileSelectorEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        horizontalLayout = new QHBoxLayout(FileSelectorEdit);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pathNotFound = new QLabel(FileSelectorEdit);
        pathNotFound->setObjectName(QStringLiteral("pathNotFound"));
        pathNotFound->setPixmap(QPixmap(QString::fromUtf8(":/resources/icons/emblem-warning-16.png")));

        horizontalLayout->addWidget(pathNotFound);

        pathEdit = new QLineEdit(FileSelectorEdit);
        pathEdit->setObjectName(QStringLiteral("pathEdit"));

        horizontalLayout->addWidget(pathEdit);

        pathSelect = new QToolButton(FileSelectorEdit);
        pathSelect->setObjectName(QStringLiteral("pathSelect"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pathSelect->sizePolicy().hasHeightForWidth());
        pathSelect->setSizePolicy(sizePolicy);
        QIcon icon;
        QString iconThemeName = QStringLiteral("folder");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        pathSelect->setIcon(icon);
        pathSelect->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(pathSelect);

        pathOpen = new QToolButton(FileSelectorEdit);
        pathOpen->setObjectName(QStringLiteral("pathOpen"));
        QIcon icon1;
        iconThemeName = QStringLiteral("system-run");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        pathOpen->setIcon(icon1);
        pathOpen->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(pathOpen);


        retranslateUi(FileSelectorEdit);

        QMetaObject::connectSlotsByName(FileSelectorEdit);
    } // setupUi

    void retranslateUi(QWidget *FileSelectorEdit)
    {
        FileSelectorEdit->setWindowTitle(QApplication::translate("FileSelectorEdit", "Form", 0));
        pathSelect->setText(QApplication::translate("FileSelectorEdit", "Select ...", 0));
        pathOpen->setText(QApplication::translate("FileSelectorEdit", "Open", 0));
    } // retranslateUi

};

namespace Ui {
    class FileSelectorEdit: public Ui_FileSelectorEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESELECTOREDIT_H

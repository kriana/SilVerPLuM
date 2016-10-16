/********************************************************************************
** Form generated from reading UI file 'filestash.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESTASH_H
#define UI_FILESTASH_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileStash
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *fileList;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QToolButton *btnAddFiles;
    QToolButton *btnRemoveFiles;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *FileStash)
    {
        if (FileStash->objectName().isEmpty())
            FileStash->setObjectName(QStringLiteral("FileStash"));
        FileStash->resize(400, 300);
        FileStash->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(FileStash);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        fileList = new QTreeWidget(FileStash);
        fileList->setObjectName(QStringLiteral("fileList"));
        fileList->setMinimumSize(QSize(0, 200));
        fileList->setColumnCount(2);

        verticalLayout->addWidget(fileList);

        widget = new QWidget(FileStash);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, 0, -1);
        btnAddFiles = new QToolButton(widget);
        btnAddFiles->setObjectName(QStringLiteral("btnAddFiles"));
        QIcon icon(QIcon::fromTheme(QStringLiteral("list-add")));
        btnAddFiles->setIcon(icon);
        btnAddFiles->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(btnAddFiles);

        btnRemoveFiles = new QToolButton(widget);
        btnRemoveFiles->setObjectName(QStringLiteral("btnRemoveFiles"));
        QIcon icon1(QIcon::fromTheme(QStringLiteral("list-remove")));
        btnRemoveFiles->setIcon(icon1);
        btnRemoveFiles->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(btnRemoveFiles);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget);


        retranslateUi(FileStash);

        QMetaObject::connectSlotsByName(FileStash);
    } // setupUi

    void retranslateUi(QWidget *FileStash)
    {
        FileStash->setWindowTitle(QApplication::translate("FileStash", "Form", 0));
        QTreeWidgetItem *___qtreewidgetitem = fileList->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("FileStash", "Source path", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("FileStash", "Filename", 0));
        btnAddFiles->setText(QApplication::translate("FileStash", "Add files", 0));
        btnRemoveFiles->setText(QApplication::translate("FileStash", "Remove selected", 0));
    } // retranslateUi

};

namespace Ui {
    class FileStash: public Ui_FileStash {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESTASH_H

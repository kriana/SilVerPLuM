/********************************************************************************
** Form generated from reading UI file 'savegameviewerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEGAMEVIEWERDIALOG_H
#define UI_SAVEGAMEVIEWERDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "fileselectoredit.h"

QT_BEGIN_NAMESPACE

class Ui_SavegameViewerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_10;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *label_11;
    FileSelectorEdit *widget;
    QLabel *label_12;
    QLabel *label_13;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SavegameViewerDialog)
    {
        if (SavegameViewerDialog->objectName().isEmpty())
            SavegameViewerDialog->setObjectName(QStringLiteral("SavegameViewerDialog"));
        SavegameViewerDialog->resize(620, 391);
        SavegameViewerDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(SavegameViewerDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollArea = new QScrollArea(SavegameViewerDialog);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 588, 339));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::FieldRole, label_2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(1, QFormLayout::FieldRole, label_4);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(2, QFormLayout::FieldRole, label_8);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(3, QFormLayout::FieldRole, label_6);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_9);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout->setWidget(4, QFormLayout::FieldRole, label_10);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_11);

        widget = new FileSelectorEdit(groupBox_2);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, widget);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_12);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, label_13);


        verticalLayout_2->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        buttonBox = new QDialogButtonBox(SavegameViewerDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SavegameViewerDialog);

        QMetaObject::connectSlotsByName(SavegameViewerDialog);
    } // setupUi

    void retranslateUi(QDialog *SavegameViewerDialog)
    {
        SavegameViewerDialog->setWindowTitle(QApplication::translate("SavegameViewerDialog", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("SavegameViewerDialog", "General information", 0));
        label->setText(QApplication::translate("SavegameViewerDialog", "Farmer", 0));
        label_2->setText(QApplication::translate("SavegameViewerDialog", "TextLabel", 0));
        label_3->setText(QApplication::translate("SavegameViewerDialog", "Farm", 0));
        label_4->setText(QApplication::translate("SavegameViewerDialog", "TextLabel", 0));
        label_7->setText(QApplication::translate("SavegameViewerDialog", "Ingame date", 0));
        label_8->setText(QApplication::translate("SavegameViewerDialog", "TextLabel", 0));
        label_5->setText(QApplication::translate("SavegameViewerDialog", "Money", 0));
        label_6->setText(QApplication::translate("SavegameViewerDialog", "TextLabel", 0));
        label_9->setText(QApplication::translate("SavegameViewerDialog", "Money earned", 0));
        label_10->setText(QApplication::translate("SavegameViewerDialog", "TextLabel", 0));
        groupBox_2->setTitle(QApplication::translate("SavegameViewerDialog", "Savegame", 0));
        label_11->setText(QApplication::translate("SavegameViewerDialog", "Directory", 0));
        label_12->setText(QApplication::translate("SavegameViewerDialog", "Backup date (if set)", 0));
        label_13->setText(QApplication::translate("SavegameViewerDialog", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class SavegameViewerDialog: public Ui_SavegameViewerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEGAMEVIEWERDIALOG_H

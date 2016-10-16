/********************************************************************************
** Form generated from reading UI file 'modimportercontentitem.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIMPORTERCONTENTITEM_H
#define UI_MODIMPORTERCONTENTITEM_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "filestash.h"
#include "identifierlineedit.h"
#include "markdowntexteditor.h"

QT_BEGIN_NAMESPACE

class Ui_ModImporterContentItem
{
public:
    QAction *actionRemove;
    QGridLayout *gridLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *lblInformation;
    QSpacerItem *horizontalSpacer;
    QToolButton *btnShowSettings;
    QWidget *expandWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *contentName;
    QLabel *label_2;
    MarkdownTextEditor *contentDescription;
    QLabel *label_3;
    QCheckBox *contentIsDefault;
    QLabel *label_4;
    QLabel *label_5;
    FileStash *contentFiles;
    QComboBox *contentInstallTo;
    QLabel *label_6;
    IdentifierLineEdit *contentId;
    QLabel *label_7;
    QSpinBox *contentPriority;

    void setupUi(QWidget *ModImporterContentItem)
    {
        if (ModImporterContentItem->objectName().isEmpty())
            ModImporterContentItem->setObjectName(QStringLiteral("ModImporterContentItem"));
        ModImporterContentItem->resize(656, 527);
        ModImporterContentItem->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionRemove = new QAction(ModImporterContentItem);
        actionRemove->setObjectName(QStringLiteral("actionRemove"));
        QIcon icon(QIcon::fromTheme(QStringLiteral("list-remove")));
        actionRemove->setIcon(icon);
        gridLayout = new QGridLayout(ModImporterContentItem);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame = new QFrame(ModImporterContentItem);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_2 = new QWidget(frame);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lblInformation = new QLabel(widget_2);
        lblInformation->setObjectName(QStringLiteral("lblInformation"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lblInformation->setFont(font);

        horizontalLayout->addWidget(lblInformation);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnShowSettings = new QToolButton(widget_2);
        btnShowSettings->setObjectName(QStringLiteral("btnShowSettings"));
        btnShowSettings->setCheckable(true);
        btnShowSettings->setPopupMode(QToolButton::MenuButtonPopup);
        btnShowSettings->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnShowSettings->setArrowType(Qt::DownArrow);

        horizontalLayout->addWidget(btnShowSettings);


        verticalLayout->addWidget(widget_2);

        expandWidget = new QWidget(frame);
        expandWidget->setObjectName(QStringLiteral("expandWidget"));
        formLayout = new QFormLayout(expandWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(expandWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(100, 0));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        contentName = new QLineEdit(expandWidget);
        contentName->setObjectName(QStringLiteral("contentName"));

        formLayout->setWidget(1, QFormLayout::FieldRole, contentName);

        label_2 = new QLabel(expandWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(100, 0));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        contentDescription = new MarkdownTextEditor(expandWidget);
        contentDescription->setObjectName(QStringLiteral("contentDescription"));
        contentDescription->setMinimumSize(QSize(0, 120));

        formLayout->setWidget(2, QFormLayout::FieldRole, contentDescription);

        label_3 = new QLabel(expandWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(100, 0));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        contentIsDefault = new QCheckBox(expandWidget);
        contentIsDefault->setObjectName(QStringLiteral("contentIsDefault"));
        contentIsDefault->setChecked(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, contentIsDefault);

        label_4 = new QLabel(expandWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(100, 0));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(expandWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(100, 0));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_5);

        contentFiles = new FileStash(expandWidget);
        contentFiles->setObjectName(QStringLiteral("contentFiles"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(contentFiles->sizePolicy().hasHeightForWidth());
        contentFiles->setSizePolicy(sizePolicy);

        formLayout->setWidget(5, QFormLayout::FieldRole, contentFiles);

        contentInstallTo = new QComboBox(expandWidget);
        contentInstallTo->setObjectName(QStringLiteral("contentInstallTo"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(contentInstallTo->sizePolicy().hasHeightForWidth());
        contentInstallTo->setSizePolicy(sizePolicy1);
        contentInstallTo->setEditable(true);

        formLayout->setWidget(6, QFormLayout::FieldRole, contentInstallTo);

        label_6 = new QLabel(expandWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(100, 0));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_6);

        contentId = new IdentifierLineEdit(expandWidget);
        contentId->setObjectName(QStringLiteral("contentId"));
        contentId->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(0, QFormLayout::FieldRole, contentId);

        label_7 = new QLabel(expandWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(100, 0));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_7);

        contentPriority = new QSpinBox(expandWidget);
        contentPriority->setObjectName(QStringLiteral("contentPriority"));

        formLayout->setWidget(4, QFormLayout::FieldRole, contentPriority);


        verticalLayout->addWidget(expandWidget);


        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(ModImporterContentItem);

        QMetaObject::connectSlotsByName(ModImporterContentItem);
    } // setupUi

    void retranslateUi(QWidget *ModImporterContentItem)
    {
        ModImporterContentItem->setWindowTitle(QApplication::translate("ModImporterContentItem", "Form", 0));
        actionRemove->setText(QApplication::translate("ModImporterContentItem", "Remove this content", 0));
        lblInformation->setText(QApplication::translate("ModImporterContentItem", "TextLabel", 0));
        btnShowSettings->setText(QApplication::translate("ModImporterContentItem", "Show settings", 0));
        label->setText(QApplication::translate("ModImporterContentItem", "Name", 0));
#ifndef QT_NO_TOOLTIP
        contentName->setToolTip(QApplication::translate("ModImporterContentItem", "The name displayed in the manager.", 0));
#endif // QT_NO_TOOLTIP
        contentName->setText(QApplication::translate("ModImporterContentItem", "The mod content", 0));
        label_2->setText(QApplication::translate("ModImporterContentItem", "Description", 0));
        label_3->setText(QApplication::translate("ModImporterContentItem", "Settings", 0));
#ifndef QT_NO_TOOLTIP
        contentIsDefault->setToolTip(QApplication::translate("ModImporterContentItem", "If enabled, this content entry will be enabled if the user enables a mod.", 0));
#endif // QT_NO_TOOLTIP
        contentIsDefault->setText(QApplication::translate("ModImporterContentItem", "Activate this content by default", 0));
        label_4->setText(QApplication::translate("ModImporterContentItem", "Files", 0));
        label_5->setText(QApplication::translate("ModImporterContentItem", "Install to", 0));
#ifndef QT_NO_TOOLTIP
        contentInstallTo->setToolTip(QApplication::translate("ModImporterContentItem", "The directory where the files should be installed to.", 0));
#endif // QT_NO_TOOLTIP
        contentInstallTo->setCurrentText(QApplication::translate("ModImporterContentItem", "Content", 0));
        label_6->setText(QApplication::translate("ModImporterContentItem", "Identifier", 0));
#ifndef QT_NO_TOOLTIP
        contentId->setToolTip(QApplication::translate("ModImporterContentItem", "The identifier of this content entry.", 0));
#endif // QT_NO_TOOLTIP
        contentId->setText(QApplication::translate("ModImporterContentItem", "content", 0));
        label_7->setText(QApplication::translate("ModImporterContentItem", "Priority", 0));
#ifndef QT_NO_TOOLTIP
        contentPriority->setToolTip(QApplication::translate("ModImporterContentItem", "The priority of this content. Higher numbers mean that they will overwrite existing files of other content entries with lower priority.", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class ModImporterContentItem: public Ui_ModImporterContentItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIMPORTERCONTENTITEM_H

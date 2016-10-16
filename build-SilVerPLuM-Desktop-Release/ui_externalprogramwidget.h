/********************************************************************************
** Form generated from reading UI file 'externalprogramwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTERNALPROGRAMWIDGET_H
#define UI_EXTERNALPROGRAMWIDGET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "fileselectoredit.h"
#include "identifierlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_ExternalProgramWidget
{
public:
    QAction *actionRemove;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *lblWarning;
    QLabel *lblIdentifier;
    QSpacerItem *horizontalSpacer;
    QToolButton *btnShowSettings;
    QWidget *expandingWidget;
    QFormLayout *formLayout_2;
    QLabel *label;
    IdentifierLineEdit *programId;
    QLabel *label_2;
    FileSelectorEdit *programExecutable;
    QLabel *label_3;
    QLineEdit *programArguments;
    QLabel *label_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *programMimeTypes;
    QToolButton *btnAddMimeType;
    QLabel *label_4;
    QCheckBox *programRunnable;

    void setupUi(QWidget *ExternalProgramWidget)
    {
        if (ExternalProgramWidget->objectName().isEmpty())
            ExternalProgramWidget->setObjectName(QStringLiteral("ExternalProgramWidget"));
        ExternalProgramWidget->resize(487, 242);
        ExternalProgramWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionRemove = new QAction(ExternalProgramWidget);
        actionRemove->setObjectName(QStringLiteral("actionRemove"));
        QIcon icon(QIcon::fromTheme(QStringLiteral("list-remove")));
        actionRemove->setIcon(icon);
        verticalLayout_2 = new QVBoxLayout(ExternalProgramWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        frame = new QFrame(ExternalProgramWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(frame);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lblWarning = new QLabel(widget);
        lblWarning->setObjectName(QStringLiteral("lblWarning"));
        lblWarning->setPixmap(QPixmap(QString::fromUtf8(":/resources/icons/emblem-warning-16.png")));

        horizontalLayout->addWidget(lblWarning);

        lblIdentifier = new QLabel(widget);
        lblIdentifier->setObjectName(QStringLiteral("lblIdentifier"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lblIdentifier->setFont(font);

        horizontalLayout->addWidget(lblIdentifier);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnShowSettings = new QToolButton(widget);
        btnShowSettings->setObjectName(QStringLiteral("btnShowSettings"));
        btnShowSettings->setCheckable(true);
        btnShowSettings->setPopupMode(QToolButton::MenuButtonPopup);
        btnShowSettings->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnShowSettings->setArrowType(Qt::DownArrow);

        horizontalLayout->addWidget(btnShowSettings);


        verticalLayout->addWidget(widget);

        expandingWidget = new QWidget(frame);
        expandingWidget->setObjectName(QStringLiteral("expandingWidget"));
        formLayout_2 = new QFormLayout(expandingWidget);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label = new QLabel(expandingWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(120, 0));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        programId = new IdentifierLineEdit(expandingWidget);
        programId->setObjectName(QStringLiteral("programId"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, programId);

        label_2 = new QLabel(expandingWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(120, 0));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        programExecutable = new FileSelectorEdit(expandingWidget);
        programExecutable->setObjectName(QStringLiteral("programExecutable"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(programExecutable->sizePolicy().hasHeightForWidth());
        programExecutable->setSizePolicy(sizePolicy);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, programExecutable);

        label_3 = new QLabel(expandingWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(120, 0));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        programArguments = new QLineEdit(expandingWidget);
        programArguments->setObjectName(QStringLiteral("programArguments"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, programArguments);

        label_5 = new QLabel(expandingWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(120, 0));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_5);

        widget_2 = new QWidget(expandingWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        programMimeTypes = new QLineEdit(widget_2);
        programMimeTypes->setObjectName(QStringLiteral("programMimeTypes"));

        horizontalLayout_2->addWidget(programMimeTypes);

        btnAddMimeType = new QToolButton(widget_2);
        btnAddMimeType->setObjectName(QStringLiteral("btnAddMimeType"));
        QIcon icon1(QIcon::fromTheme(QStringLiteral("list-add")));
        btnAddMimeType->setIcon(icon1);

        horizontalLayout_2->addWidget(btnAddMimeType);


        formLayout_2->setWidget(3, QFormLayout::FieldRole, widget_2);

        label_4 = new QLabel(expandingWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(120, 0));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_4);

        programRunnable = new QCheckBox(expandingWidget);
        programRunnable->setObjectName(QStringLiteral("programRunnable"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, programRunnable);


        verticalLayout->addWidget(expandingWidget);


        verticalLayout_2->addWidget(frame);


        retranslateUi(ExternalProgramWidget);

        QMetaObject::connectSlotsByName(ExternalProgramWidget);
    } // setupUi

    void retranslateUi(QWidget *ExternalProgramWidget)
    {
        ExternalProgramWidget->setWindowTitle(QApplication::translate("ExternalProgramWidget", "Form", 0));
        actionRemove->setText(QApplication::translate("ExternalProgramWidget", "Remove entry", 0));
        lblWarning->setText(QString());
        lblIdentifier->setText(QApplication::translate("ExternalProgramWidget", "Text&Label", 0));
        btnShowSettings->setText(QApplication::translate("ExternalProgramWidget", "Show settings", 0));
        label->setText(QApplication::translate("ExternalProgramWidget", "<html><head/><body><p>Identifier</p></body></html>", 0));
        label_2->setText(QApplication::translate("ExternalProgramWidget", "<html><head/><body><p>Executable</p></body></html>", 0));
        label_3->setText(QApplication::translate("ExternalProgramWidget", "<html><head/><body><p>Arguments</p></body></html>", 0));
        label_5->setText(QApplication::translate("ExternalProgramWidget", "<html><head/><body><p>Runs MIME-Types</p></body></html>", 0));
        btnAddMimeType->setText(QApplication::translate("ExternalProgramWidget", "...", 0));
        label_4->setText(QApplication::translate("ExternalProgramWidget", "Settings", 0));
        programRunnable->setText(QApplication::translate("ExternalProgramWidget", "Program is runnable", 0));
    } // retranslateUi

};

namespace Ui {
    class ExternalProgramWidget: public Ui_ExternalProgramWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTERNALPROGRAMWIDGET_H

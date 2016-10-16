/********************************************************************************
** Form generated from reading UI file 'externalprogramsettingswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTERNALPROGRAMSETTINGSWIDGET_H
#define UI_EXTERNALPROGRAMSETTINGSWIDGET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "fileselectoredit.h"

QT_BEGIN_NAMESPACE

class Ui_ExternalProgramSettingsWidget
{
public:
    QAction *actionRemove;
    QGridLayout *gridLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *lblWarning;
    QLabel *lblIdentifier;
    QSpacerItem *horizontalSpacer;
    QToolButton *btnShowSettings;
    QWidget *expandingWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *programId;
    FileSelectorEdit *programExecutable;
    QLineEdit *programArguments;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *programMimeTypes;
    QToolButton *btnAddMimeType;
    QCheckBox *programRunnable;

    void setupUi(QWidget *ExternalProgramSettingsWidget)
    {
        if (ExternalProgramSettingsWidget->objectName().isEmpty())
            ExternalProgramSettingsWidget->setObjectName(QStringLiteral("ExternalProgramSettingsWidget"));
        ExternalProgramSettingsWidget->resize(400, 300);
        ExternalProgramSettingsWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionRemove = new QAction(ExternalProgramSettingsWidget);
        actionRemove->setObjectName(QStringLiteral("actionRemove"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("list-remove");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionRemove->setIcon(icon);
        gridLayout = new QGridLayout(ExternalProgramSettingsWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame = new QFrame(ExternalProgramSettingsWidget);
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

        horizontalSpacer = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

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
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(expandingWidget->sizePolicy().hasHeightForWidth());
        expandingWidget->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(expandingWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(expandingWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(120, 0));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(expandingWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(120, 0));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(expandingWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(120, 0));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(expandingWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(120, 0));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(expandingWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(120, 0));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        programId = new QLineEdit(expandingWidget);
        programId->setObjectName(QStringLiteral("programId"));

        formLayout->setWidget(0, QFormLayout::FieldRole, programId);

        programExecutable = new FileSelectorEdit(expandingWidget);
        programExecutable->setObjectName(QStringLiteral("programExecutable"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(programExecutable->sizePolicy().hasHeightForWidth());
        programExecutable->setSizePolicy(sizePolicy1);

        formLayout->setWidget(1, QFormLayout::FieldRole, programExecutable);

        programArguments = new QLineEdit(expandingWidget);
        programArguments->setObjectName(QStringLiteral("programArguments"));

        formLayout->setWidget(2, QFormLayout::FieldRole, programArguments);

        widget_4 = new QWidget(expandingWidget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        sizePolicy1.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy1);
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        programMimeTypes = new QLineEdit(widget_4);
        programMimeTypes->setObjectName(QStringLiteral("programMimeTypes"));

        horizontalLayout_2->addWidget(programMimeTypes);

        btnAddMimeType = new QToolButton(widget_4);
        btnAddMimeType->setObjectName(QStringLiteral("btnAddMimeType"));
        QIcon icon1;
        iconThemeName = QStringLiteral("list-add");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnAddMimeType->setIcon(icon1);

        horizontalLayout_2->addWidget(btnAddMimeType);


        formLayout->setWidget(3, QFormLayout::FieldRole, widget_4);

        programRunnable = new QCheckBox(expandingWidget);
        programRunnable->setObjectName(QStringLiteral("programRunnable"));

        formLayout->setWidget(4, QFormLayout::FieldRole, programRunnable);


        verticalLayout->addWidget(expandingWidget);


        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(ExternalProgramSettingsWidget);

        QMetaObject::connectSlotsByName(ExternalProgramSettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *ExternalProgramSettingsWidget)
    {
        ExternalProgramSettingsWidget->setWindowTitle(QApplication::translate("ExternalProgramSettingsWidget", "Form", 0));
        actionRemove->setText(QApplication::translate("ExternalProgramSettingsWidget", "Remove entry", 0));
        lblWarning->setText(QString());
        lblIdentifier->setText(QApplication::translate("ExternalProgramSettingsWidget", "TextLabel", 0));
        btnShowSettings->setText(QApplication::translate("ExternalProgramSettingsWidget", "Show settings", 0));
        label->setText(QApplication::translate("ExternalProgramSettingsWidget", "Identifier", 0));
        label_2->setText(QApplication::translate("ExternalProgramSettingsWidget", "Executable", 0));
        label_3->setText(QApplication::translate("ExternalProgramSettingsWidget", "Arguments", 0));
        label_4->setText(QApplication::translate("ExternalProgramSettingsWidget", "MIME-Types", 0));
        label_5->setText(QApplication::translate("ExternalProgramSettingsWidget", "Settings", 0));
#ifndef QT_NO_TOOLTIP
        programId->setToolTip(QApplication::translate("ExternalProgramSettingsWidget", "Identifier of this program. It will be used to select this entry.", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        programExecutable->setToolTip(QApplication::translate("ExternalProgramSettingsWidget", "The executable of this external program", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        programArguments->setToolTip(QApplication::translate("ExternalProgramSettingsWidget", "<html><head/><body><p>The argument string of this external program. You can include program parameters using placeholders. Supported placeholders are {insertargs} to insert arguments into the argument list, {joinedargs} will be replaced with one string containing all arguments. {joinedfileargs} will be replaced with one string of the input file and additional args.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        programMimeTypes->setToolTip(QApplication::translate("ExternalProgramSettingsWidget", "<html><head/><body><p>This list contains all MIME-Types this entry should run. Separate them with space. To make it easier, click the 'Add' button on the right to add the MIME-Type from a file.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnAddMimeType->setText(QApplication::translate("ExternalProgramSettingsWidget", "...", 0));
#ifndef QT_NO_TOOLTIP
        programRunnable->setToolTip(QApplication::translate("ExternalProgramSettingsWidget", "<html><head/><body><p>If enabled, this program can run directly</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        programRunnable->setText(QApplication::translate("ExternalProgramSettingsWidget", "This program is runnable", 0));
    } // retranslateUi

};

namespace Ui {
    class ExternalProgramSettingsWidget: public Ui_ExternalProgramSettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTERNALPROGRAMSETTINGSWIDGET_H

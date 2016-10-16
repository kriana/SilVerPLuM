/********************************************************************************
** Form generated from reading UI file 'modmanagerwidgetpipelineitem.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODMANAGERWIDGETPIPELINEITEM_H
#define UI_MODMANAGERWIDGETPIPELINEITEM_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModManagerWidgetPipelineItem
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *lblIcon;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *lblName;
    QTextEdit *lblDescription;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblIdentifier;
    QSpacerItem *verticalSpacer;
    QLabel *lblInfo;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnDisable;
    QPushButton *btnEnable;

    void setupUi(QWidget *ModManagerWidgetPipelineItem)
    {
        if (ModManagerWidgetPipelineItem->objectName().isEmpty())
            ModManagerWidgetPipelineItem->setObjectName(QStringLiteral("ModManagerWidgetPipelineItem"));
        ModManagerWidgetPipelineItem->resize(650, 150);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ModManagerWidgetPipelineItem->sizePolicy().hasHeightForWidth());
        ModManagerWidgetPipelineItem->setSizePolicy(sizePolicy);
        ModManagerWidgetPipelineItem->setMinimumSize(QSize(0, 150));
        ModManagerWidgetPipelineItem->setMaximumSize(QSize(16777215, 150));
        ModManagerWidgetPipelineItem->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        horizontalLayout_2 = new QHBoxLayout(ModManagerWidgetPipelineItem);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        lblIcon = new QLabel(ModManagerWidgetPipelineItem);
        lblIcon->setObjectName(QStringLiteral("lblIcon"));
        lblIcon->setMinimumSize(QSize(75, 75));
        lblIcon->setMaximumSize(QSize(75, 75));
        lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/resources/icons/module-100.png")));
        lblIcon->setScaledContents(true);
        lblIcon->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_3->addWidget(lblIcon);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lblName = new QLabel(ModManagerWidgetPipelineItem);
        lblName->setObjectName(QStringLiteral("lblName"));
        QFont font;
        font.setPointSize(12);
        lblName->setFont(font);

        verticalLayout->addWidget(lblName);

        lblDescription = new QTextEdit(ModManagerWidgetPipelineItem);
        lblDescription->setObjectName(QStringLiteral("lblDescription"));
        lblDescription->setStyleSheet(QStringLiteral("QTextEdit { background-color: transparent; }"));
        lblDescription->setFrameShape(QFrame::NoFrame);
        lblDescription->setReadOnly(true);

        verticalLayout->addWidget(lblDescription);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lblIdentifier = new QLabel(ModManagerWidgetPipelineItem);
        lblIdentifier->setObjectName(QStringLiteral("lblIdentifier"));
        QFont font1;
        font1.setItalic(true);
        lblIdentifier->setFont(font1);
        lblIdentifier->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(lblIdentifier);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        lblInfo = new QLabel(ModManagerWidgetPipelineItem);
        lblInfo->setObjectName(QStringLiteral("lblInfo"));
        QFont font2;
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        lblInfo->setFont(font2);
        lblInfo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(lblInfo);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnDisable = new QPushButton(ModManagerWidgetPipelineItem);
        btnDisable->setObjectName(QStringLiteral("btnDisable"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("dialog-cancel");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnDisable->setIcon(icon);

        horizontalLayout->addWidget(btnDisable);

        btnEnable = new QPushButton(ModManagerWidgetPipelineItem);
        btnEnable->setObjectName(QStringLiteral("btnEnable"));
        QIcon icon1;
        iconThemeName = QStringLiteral("dialog-ok");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnEnable->setIcon(icon1);

        horizontalLayout->addWidget(btnEnable);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);


        retranslateUi(ModManagerWidgetPipelineItem);

        QMetaObject::connectSlotsByName(ModManagerWidgetPipelineItem);
    } // setupUi

    void retranslateUi(QWidget *ModManagerWidgetPipelineItem)
    {
        ModManagerWidgetPipelineItem->setWindowTitle(QApplication::translate("ModManagerWidgetPipelineItem", "Form", 0));
        lblIcon->setText(QString());
        lblName->setText(QApplication::translate("ModManagerWidgetPipelineItem", "Pipline name", 0));
        lblIdentifier->setText(QApplication::translate("ModManagerWidgetPipelineItem", "TextLabel", 0));
        lblInfo->setText(QApplication::translate("ModManagerWidgetPipelineItem", "TextLabel", 0));
#ifndef QT_NO_TOOLTIP
        btnDisable->setToolTip(QApplication::translate("ModManagerWidgetPipelineItem", "Disables this content.", 0));
#endif // QT_NO_TOOLTIP
        btnDisable->setText(QApplication::translate("ModManagerWidgetPipelineItem", "Disable", 0));
#ifndef QT_NO_TOOLTIP
        btnEnable->setToolTip(QApplication::translate("ModManagerWidgetPipelineItem", "Enables this content.", 0));
#endif // QT_NO_TOOLTIP
        btnEnable->setText(QApplication::translate("ModManagerWidgetPipelineItem", "Enable", 0));
    } // retranslateUi

};

namespace Ui {
    class ModManagerWidgetPipelineItem: public Ui_ModManagerWidgetPipelineItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODMANAGERWIDGETPIPELINEITEM_H

/********************************************************************************
** Form generated from reading UI file 'dependencycheckerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPENDENCYCHECKERWIDGET_H
#define UI_DEPENDENCYCHECKERWIDGET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DependencyCheckerWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnShow;
    QWidget *expandWidget;
    QGridLayout *gridLayout;
    QTextEdit *lblIssues;
    QLabel *label_3;

    void setupUi(QWidget *DependencyCheckerWidget)
    {
        if (DependencyCheckerWidget->objectName().isEmpty())
            DependencyCheckerWidget->setObjectName(QStringLiteral("DependencyCheckerWidget"));
        DependencyCheckerWidget->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DependencyCheckerWidget->sizePolicy().hasHeightForWidth());
        DependencyCheckerWidget->setSizePolicy(sizePolicy);
        DependencyCheckerWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(DependencyCheckerWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(DependencyCheckerWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/resources/icons/emblem-warning-16.png")));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(56, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnShow = new QPushButton(widget);
        btnShow->setObjectName(QStringLiteral("btnShow"));
        btnShow->setCheckable(true);

        horizontalLayout->addWidget(btnShow);


        verticalLayout->addWidget(widget);

        expandWidget = new QWidget(DependencyCheckerWidget);
        expandWidget->setObjectName(QStringLiteral("expandWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(expandWidget->sizePolicy().hasHeightForWidth());
        expandWidget->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(expandWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lblIssues = new QTextEdit(expandWidget);
        lblIssues->setObjectName(QStringLiteral("lblIssues"));
        lblIssues->setStyleSheet(QStringLiteral("QTextEdit { background-color: transparent; }"));
        lblIssues->setFrameShape(QFrame::NoFrame);
        lblIssues->setReadOnly(true);

        gridLayout->addWidget(lblIssues, 0, 0, 1, 1);

        label_3 = new QLabel(expandWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setWordWrap(true);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);


        verticalLayout->addWidget(expandWidget);


        retranslateUi(DependencyCheckerWidget);

        QMetaObject::connectSlotsByName(DependencyCheckerWidget);
    } // setupUi

    void retranslateUi(QWidget *DependencyCheckerWidget)
    {
        DependencyCheckerWidget->setWindowTitle(QApplication::translate("DependencyCheckerWidget", "Form", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("DependencyCheckerWidget", "Dependency problems detected!", 0));
        btnShow->setText(QApplication::translate("DependencyCheckerWidget", "Show", 0));
        label_3->setText(QApplication::translate("DependencyCheckerWidget", "<html><head/><body><p>If you enabled priority-aware dependency check (default: on), a dependency is <span style=\" font-weight:600;\">not</span> satisfied only by having the missing mod being activated - It must be 'on top' of the requesting mod, as a mod 'builds' on another mod.</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class DependencyCheckerWidget: public Ui_DependencyCheckerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPENDENCYCHECKERWIDGET_H

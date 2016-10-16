/********************************************************************************
** Form generated from reading UI file 'markdownviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKDOWNVIEWER_H
#define UI_MARKDOWNVIEWER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "qwebengineview.h"

QT_BEGIN_NAMESPACE

class Ui_MarkdownViewer
{
public:
    QGridLayout *gridLayout;
    QWebEngineView *preview;

    void setupUi(QWidget *MarkdownViewer)
    {
        if (MarkdownViewer->objectName().isEmpty())
            MarkdownViewer->setObjectName(QStringLiteral("MarkdownViewer"));
        MarkdownViewer->resize(400, 300);
        MarkdownViewer->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout = new QGridLayout(MarkdownViewer);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        preview = new QWebEngineView(MarkdownViewer);
        preview->setObjectName(QStringLiteral("preview"));

        gridLayout->addWidget(preview, 0, 0, 1, 1);


        retranslateUi(MarkdownViewer);

        QMetaObject::connectSlotsByName(MarkdownViewer);
    } // setupUi

    void retranslateUi(QWidget *MarkdownViewer)
    {
        MarkdownViewer->setWindowTitle(QApplication::translate("MarkdownViewer", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class MarkdownViewer: public Ui_MarkdownViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKDOWNVIEWER_H

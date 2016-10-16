/********************************************************************************
** Form generated from reading UI file 'logviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGVIEWER_H
#define UI_LOGVIEWER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LogViewer
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *lblLog;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LogViewer)
    {
        if (LogViewer->objectName().isEmpty())
            LogViewer->setObjectName(QStringLiteral("LogViewer"));
        LogViewer->resize(596, 389);
        QIcon icon;
        icon.addFile(QStringLiteral(":/resources/icons/application-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        LogViewer->setWindowIcon(icon);
        LogViewer->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(LogViewer);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lblLog = new QTextEdit(LogViewer);
        lblLog->setObjectName(QStringLiteral("lblLog"));
        lblLog->setReadOnly(true);

        verticalLayout->addWidget(lblLog);

        buttonBox = new QDialogButtonBox(LogViewer);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(LogViewer);

        QMetaObject::connectSlotsByName(LogViewer);
    } // setupUi

    void retranslateUi(QDialog *LogViewer)
    {
        LogViewer->setWindowTitle(QApplication::translate("LogViewer", "Logviewer", 0));
    } // retranslateUi

};

namespace Ui {
    class LogViewer: public Ui_LogViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGVIEWER_H

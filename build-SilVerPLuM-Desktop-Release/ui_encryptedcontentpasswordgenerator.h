/********************************************************************************
** Form generated from reading UI file 'encryptedcontentpasswordgenerator.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENCRYPTEDCONTENTPASSWORDGENERATOR_H
#define UI_ENCRYPTEDCONTENTPASSWORDGENERATOR_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EncryptedContentPasswordGenerator
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *password;
    QLabel *label_2;
    QLineEdit *encryptedPassword;
    QLabel *label_3;
    QLineEdit *decryptedPassword;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EncryptedContentPasswordGenerator)
    {
        if (EncryptedContentPasswordGenerator->objectName().isEmpty())
            EncryptedContentPasswordGenerator->setObjectName(QStringLiteral("EncryptedContentPasswordGenerator"));
        EncryptedContentPasswordGenerator->resize(400, 162);
        EncryptedContentPasswordGenerator->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(EncryptedContentPasswordGenerator);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(EncryptedContentPasswordGenerator);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        password = new QLineEdit(EncryptedContentPasswordGenerator);
        password->setObjectName(QStringLiteral("password"));

        formLayout->setWidget(0, QFormLayout::FieldRole, password);

        label_2 = new QLabel(EncryptedContentPasswordGenerator);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        encryptedPassword = new QLineEdit(EncryptedContentPasswordGenerator);
        encryptedPassword->setObjectName(QStringLiteral("encryptedPassword"));
        encryptedPassword->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, encryptedPassword);

        label_3 = new QLabel(EncryptedContentPasswordGenerator);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        decryptedPassword = new QLineEdit(EncryptedContentPasswordGenerator);
        decryptedPassword->setObjectName(QStringLiteral("decryptedPassword"));
        decryptedPassword->setEnabled(false);
        decryptedPassword->setReadOnly(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, decryptedPassword);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(EncryptedContentPasswordGenerator);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(EncryptedContentPasswordGenerator);

        QMetaObject::connectSlotsByName(EncryptedContentPasswordGenerator);
    } // setupUi

    void retranslateUi(QDialog *EncryptedContentPasswordGenerator)
    {
        EncryptedContentPasswordGenerator->setWindowTitle(QApplication::translate("EncryptedContentPasswordGenerator", "Encrypted content password generator", 0));
        label->setText(QApplication::translate("EncryptedContentPasswordGenerator", "*.zip file password", 0));
#ifndef QT_NO_TOOLTIP
        password->setToolTip(QApplication::translate("EncryptedContentPasswordGenerator", "Insert the password of the *.zip file you used for your encrypted content", 0));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("EncryptedContentPasswordGenerator", "Password for mod.json", 0));
#ifndef QT_NO_TOOLTIP
        encryptedPassword->setToolTip(QApplication::translate("EncryptedContentPasswordGenerator", "Copy this password into the mod configuration", 0));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("EncryptedContentPasswordGenerator", "Decrypted password", 0));
#ifndef QT_NO_TOOLTIP
        decryptedPassword->setToolTip(QApplication::translate("EncryptedContentPasswordGenerator", "To check if your password can be correctly decrypted", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class EncryptedContentPasswordGenerator: public Ui_EncryptedContentPasswordGenerator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENCRYPTEDCONTENTPASSWORDGENERATOR_H

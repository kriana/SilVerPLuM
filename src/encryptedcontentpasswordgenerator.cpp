#include "encryptedcontentpasswordgenerator.h"
#include "ui_encryptedcontentpasswordgenerator.h"
#include "utils.h"

EncryptedContentPasswordGenerator::EncryptedContentPasswordGenerator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EncryptedContentPasswordGenerator)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(close()));
    connect(ui->password, SIGNAL(textChanged(QString)), this, SLOT(encrypt()));
}

EncryptedContentPasswordGenerator::~EncryptedContentPasswordGenerator()
{
    delete ui;
}

void EncryptedContentPasswordGenerator::encrypt()
{
    QString encr = utils::ecryptedContentEncryptPassword(ui->password->text());

    ui->encryptedPassword->setText(encr);
    ui->decryptedPassword->setText(utils::encryptedContentDecryptPassword(encr));

}

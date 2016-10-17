#ifndef ENCRYPTEDCONTENTPASSWORDGENERATOR_H
#define ENCRYPTEDCONTENTPASSWORDGENERATOR_H

#include <QDialog>

namespace Ui {
class EncryptedContentPasswordGenerator;
}

class EncryptedContentPasswordGenerator : public QDialog
{
    Q_OBJECT

public:
    explicit EncryptedContentPasswordGenerator(QWidget *parent = 0);
    ~EncryptedContentPasswordGenerator();

private slots:

    void encrypt();

private:
    Ui::EncryptedContentPasswordGenerator *ui;
};

#endif // ENCRYPTEDCONTENTPASSWORDGENERATOR_H

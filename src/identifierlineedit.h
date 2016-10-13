#ifndef IDENTIIFERLINEEDIT_H
#define IDENTIFIERLINEEDIT_H

#include <QLineEdit>


class IdentifierLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit IdentifierLineEdit(QWidget *parent = 0);

protected slots:

    void checkText(const QString &text);

signals:

public slots:
};

#endif // IDENTIFIERLINEEDIT_H

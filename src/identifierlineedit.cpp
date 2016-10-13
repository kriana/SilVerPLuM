#include "identifierlineedit.h"
#include <QRegExp>

IdentifierLineEdit::IdentifierLineEdit(QWidget *parent) : QLineEdit(parent)
{
    connect(this, SIGNAL(textChanged(QString)), this, SLOT(checkText(QString)));
}

void IdentifierLineEdit::checkText(const QString & text)
{
    QString t = text.toLower();
    setText(t.replace(" ", "-").replace(QRegExp("[^a-z0-9_.\\-]+"), "").trimmed());
}

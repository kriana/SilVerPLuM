#include "identifierlineedit.h"
#include <QRegExp>
#include "utils.h"

IdentifierLineEdit::IdentifierLineEdit(QWidget *parent) : QLineEdit(parent)
{
    connect(this, SIGNAL(textChanged(QString)), this, SLOT(checkText(QString)));
}

void IdentifierLineEdit::checkText(const QString & text)
{
    setText(utils::makeValidModId(text));
}

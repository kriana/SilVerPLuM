#ifndef MARKDOWNTEXTEDITOR_H
#define MARKDOWNTEXTEDITOR_H

#include <QPlainTextEdit>

class MarkdownTextEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    MarkdownTextEditor(QWidget *parent = 0);

    virtual bool event( QEvent* event );

public slots:
    void indentOrUnindent( bool doIndent );

private:
    void onTabKey( QKeyEvent* event );
    void onShiftTabKey(QKeyEvent* event );
    int firstNonSpace( const QString& text ) const;
    int columnAt( const QString& text, int position ) const;
    int indentedColumn( int column, bool doIndent ) const;
};

#endif // MARKDOWNTEXTEDITOR_H

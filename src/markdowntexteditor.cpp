#include "markdowntexteditor.h"
#include <QDebug>
#include <QTextBlock>

/*
 * Taken from https://github.com/sschober/qarkdown/blob/master/PlainTextEditor.cpp
 */

#define IndentSize 4
#define TabSize 4

MarkdownTextEditor::MarkdownTextEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    setTabStopWidth( 40 );
    setTabChangesFocus( false );
}

bool MarkdownTextEditor::event( QEvent* event )
{
    if ( event->type() == QEvent::KeyPress ) {
        QKeyEvent* ke = static_cast<QKeyEvent*>( event );
        const bool isBackTab =
                ( ke->key() == Qt::Key_Backtab && ( ke->modifiers() == Qt::NoModifier || ke->modifiers() == Qt::ShiftModifier ) ) ||
                ( ke->key() == Qt::Key_Tab && ke->modifiers() == Qt::ShiftModifier )
                ;
        const bool isTab = ke->key() == Qt::Key_Tab && ke->modifiers() == Qt::NoModifier;

        if ( isTab ) {
            onTabKey( ke );
            return true;
        }
        else if ( isBackTab ) {
            onShiftTabKey( ke );
            return true;
        }
    }

    return QPlainTextEdit::event( event );
}

void MarkdownTextEditor::onTabKey( QKeyEvent* event )
{
    Q_UNUSED( event );

    if ( !textCursor().hasSelection() ) {
        textCursor().insertText( QString( IndentSize, QLatin1Char( ' ' ) ) );
    }
    else {
        indentOrUnindent( true );
    }
}

void MarkdownTextEditor::onShiftTabKey( QKeyEvent* event )
{
    Q_UNUSED( event );

    if ( !textCursor().hasSelection() ) {
        QTextCursor cursor = textCursor();
        int newPos = cursor.position() -IndentSize;

        if ( newPos < 0 ) {
            newPos = 0;
        }

        cursor.setPosition( newPos );
        setTextCursor( cursor );
    }
    else {
        indentOrUnindent( false );
    }
}

void MarkdownTextEditor::indentOrUnindent( bool doIndent )
{
    QTextCursor cursor = textCursor();
    cursor.beginEditBlock();

    // Indent or unindent the selected lines
    int pos = cursor.position();
    int anchor = cursor.anchor();
    int start = qMin( anchor, pos );
    int end = qMax( anchor, pos );

    QTextDocument* doc = document();
    QTextBlock startBlock = doc->findBlock(start);
    QTextBlock endBlock = doc->findBlock( end -1 ).next();

    for ( QTextBlock block = startBlock; block != endBlock; block = block.next() ) {
        QString text = block.text();

        if ( doIndent ) {
            const int indentPosition = firstNonSpace( text );
            cursor.setPosition( block.position() +indentPosition );
            cursor.insertText( QString( IndentSize, QLatin1Char( ' ' ) ) );
        } else {
            const int indentPosition = firstNonSpace( text );
            const int targetColumn = indentedColumn( columnAt( text, indentPosition ), false );
            cursor.setPosition( block.position() +indentPosition );
            cursor.setPosition( block.position() +targetColumn, QTextCursor::KeepAnchor );
            cursor.removeSelectedText();
        }
    }

    // Reselect the selected lines
    cursor.setPosition( startBlock.position() );
    cursor.setPosition( endBlock.previous().position(), QTextCursor::KeepAnchor );
    cursor.movePosition( QTextCursor::EndOfBlock, QTextCursor::KeepAnchor );

    cursor.endEditBlock();
    setTextCursor( cursor );
}

int MarkdownTextEditor::firstNonSpace( const QString& text ) const
{
    int i = 0;

    while ( i < text.size() ) {
        if ( !text.at( i ).isSpace() ) {
            return i;
        }

        ++i;
    }

    return i;
}

int MarkdownTextEditor::columnAt( const QString& text, int position ) const
{
    int column = 0;

    for ( int i = 0; i < position; ++i ) {
        if ( text.at( i ) == QLatin1Char( '\t' ) ) {
            column = column -( column %TabSize ) +TabSize;
        }
        else {
            ++column;
        }
    }

    return column;
}

int MarkdownTextEditor::indentedColumn( int column, bool doIndent ) const
{
    const int aligned = ( column /IndentSize ) *IndentSize;

    if ( doIndent ) {
        return aligned +IndentSize;
    }

    if ( aligned < column ) {
        return aligned;
    }

    return qMax( 0, aligned -IndentSize );
}

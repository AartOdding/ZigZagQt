#include "operatornametag.h"

#include "operatorview.h"

#include <array>
#include <iostream>

#include <QKeyEvent>
#include <QTextCursor>
#include <QTextDocument>
#include <QGraphicsSceneMouseEvent>


OperatorNameTag::OperatorNameTag(const QString &text, OperatorView *parent)
    : QGraphicsTextItem(text, parent), parent_operator(parent)
{
    setTabChangesFocus(true);
    setDefaultTextColor(QColor(255, 255, 255));
    setFont(QFont("Helvetica", 14));
    setTextInteractionFlags(Qt::TextEditorInteraction);
}



// static here means limited to this file
static constexpr bool is_allowed(const char key)
{
    constexpr std::array<char, 10> not_allowed = { '"', ',', '.', '/', ';', '[', ']', '\\', '^', '`' };

    for (const char c : not_allowed)
    {
        if (key == c)
        {
            return false;
        }
    }
    return true;
}


void OperatorNameTag::keyPressEvent(QKeyEvent *event)
{
    const int key = event->key();

    // Key is one of all printable ascii characters, and not one of the non-allowed ones.
    if ((key >= ' ' && key <= '~' && is_allowed(key)) || key == Qt::Key_Delete
            || key == Qt::Key_Backspace ||  key == Qt::Key_Left   || key == Qt::Key_Right)
    {
        QGraphicsTextItem::keyPressEvent(event);
        return;
    }

    if (key == Qt::Key_Enter || key == Qt::Key_Return)
    {
        parent_operator->setFocus();
    }
}


void OperatorNameTag::focusOutEvent(QFocusEvent *event)
{
    // Clear the undo redo stack so that it is impossible to redo name changes that have become invalid
    document()->clearUndoRedoStacks();
    QTextCursor c = textCursor();
    c.clearSelection();
    setTextCursor(c);
    QGraphicsTextItem::focusOutEvent(event);
}

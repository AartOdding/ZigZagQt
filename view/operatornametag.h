#pragma once


#include <QGraphicsTextItem>


class OperatorView;


class OperatorNameTag : public QGraphicsTextItem
{
public:

    OperatorNameTag(const QString &text, OperatorView *parent = nullptr);



protected:


    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override { QGraphicsTextItem::keyReleaseEvent(event); }

    void focusOutEvent(QFocusEvent *event) override;

    // Overload to disable context menu's
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override { }

    OperatorView *parent_operator;


};

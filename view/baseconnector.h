#pragma once

#include <QGraphicsWidget>



class ConnectionManager;


class BaseConnector : public QGraphicsWidget
{
public:

    BaseConnector(ConnectionManager* manager, QGraphicsItem* parent = nullptr);

    virtual ~BaseConnector() override = default;


    void try_connect();

    bool is_connecting() const;


    //bool is_highlighted() const { return highlighted; }

    //void set_highlighted(bool highlighted);

    virtual bool can_connect_with(BaseConnector* other) const = 0;

    virtual void connection_requested_event(BaseConnector* other) = 0;

    virtual void connection_aborted_event() { }



    //void grabMouseEvent(QEvent *event) override;
    //void ungrabMouseEvent(QEvent *event) override;

    //void focusInEvent(QFocusEvent *) override { }
    //void focusOutEvent(QFocusEvent *event) override;

    //void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    //void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    //virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    //virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override { }
    //virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


private:


    ConnectionManager* manager = nullptr;

    //bool highlighted = false;

};

#pragma once

#include <QGraphicsWidget>



class ProjectSurface;


class BaseConnector : public QGraphicsWidget
{
    friend class ProjectSurface;

public:

    BaseConnector(ProjectSurface* surface, QGraphicsItem* parent = nullptr);

    virtual ~BaseConnector() override = default;


    bool is_connecting() const;

    virtual bool can_connect_with(BaseConnector* other) const = 0;


    bool is_highlighted() const { return highlighted; }

    void set_highlighted(bool highlighted);

protected:

    virtual void connection_made_event(BaseConnector* other) = 0;
    virtual void connection_aborted_event() { }

    //void grabMouseEvent(QEvent *event) override;
    //void ungrabMouseEvent(QEvent *event) override;

    void focusInEvent(QFocusEvent *) override { }
    void focusOutEvent(QFocusEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *) override { }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


private:


    ProjectSurface* surface = nullptr;

    bool highlighted = false;

};

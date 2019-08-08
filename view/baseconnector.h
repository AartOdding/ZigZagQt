#pragma once

#include <QGraphicsItem>



class ProjectSurface;


class BaseConnector : public QGraphicsItem
{
    friend class ProjectSurface;

public:

    BaseConnector(ProjectSurface* surface, QGraphicsItem* parent = nullptr);

    virtual ~BaseConnector() override = default;


    bool is_connecting() const;

    virtual bool can_connect_with(BaseConnector* other) const = 0;

    void set_highlighted(bool value);


protected:

    virtual void highlight_on_event() { }
    virtual void highlight_off_event() { }

    virtual void connection_made_event(BaseConnector* other) = 0;
    virtual void connection_aborted_event() { }



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

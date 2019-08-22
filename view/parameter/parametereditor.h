#pragma once

#include <QWheelEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QSizeGrip>


class QScrollArea;
class QGraphicsScene;
class ParameterPanel;
class ParameterPanelHeader;



class ParameterEditor : public QWidget
{

public:

    ParameterEditor(QWidget* parent);

    void set_scene(QGraphicsScene* scene);

protected:

    void resizeEvent(QResizeEvent *event) override;


    void wheelEvent(QWheelEvent * e) override { e->accept(); }
    void mouseMoveEvent(QMouseEvent *e) override { e->accept(); }
    void mousePressEvent(QMouseEvent *e) override { e->accept(); }
    void mouseReleaseEvent(QMouseEvent *e) override { e->accept(); }

private:


    ParameterPanelHeader* header;
    QScrollArea* body;
    ParameterPanel* content;

    QSizeGrip size_grip;

};





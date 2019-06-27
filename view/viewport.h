#pragma once

#include <QWidget>
#include <QGraphicsView>

#include "programview.h"



class Viewport : public QGraphicsView
{
    Q_OBJECT

public:

    Viewport(QWidget* parent = nullptr);

    void set_view(ProgramView* view_model /* , ProgramScope scope */);

    void wheelEvent(QWheelEvent *event) override { }

    void enterEvent(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;


signals:


public slots:


private:


    ProgramView* view_model;

};

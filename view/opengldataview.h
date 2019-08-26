#pragma once


#include <QOpenGLFunctions_3_2_Core>

#include "basedataview.h"


class OpenGLDataView : public BaseDataView,
                       public QOpenGLFunctions_3_2_Core
{

public:

    OpenGLDataView();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;

    virtual void paint_opengl(int res_x, int res_y) = 0;


};


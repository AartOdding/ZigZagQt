#include "opengldataview.h"
#include "Viewport.hpp"

#include <QDebug>
#include <QWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QOpenGLFunctions>


#include <iostream>


OpenGLDataView::OpenGLDataView(BaseOperator * parent_operator, const DataViewDescription * type_info)
    : BaseDataView(parent_operator, type_info)
{
    initializeOpenGLFunctions();
}


void OpenGLDataView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* widget)
{


    QGraphicsView* view = nullptr;

    for (auto& v : scene()->views())
    {
        if (v->viewport() == widget)
        {
            view = v;
            break;
        }
    }

    Viewport* viewport = dynamic_cast<Viewport*>(view);


    if (viewport)
    {
        auto scene_top_left = mapToScene(boundingRect().topLeft());
        auto scene_bot_right = mapToScene(boundingRect().bottomRight());
        auto view_top_left = viewport->mapFromScene(scene_top_left);
        auto view_bot_right = viewport->mapFromScene(scene_bot_right);

        double scale_factor = viewport->getWindow()->devicePixelRatio();

        auto x = scale_factor * view_top_left.x();
        auto y = scale_factor * (viewport->height() - view_bot_right.y());
        auto w = scale_factor * (view_bot_right.x() - view_top_left.x());
        auto h = scale_factor * (view_bot_right.y() - view_top_left.y());

        painter->beginNativePainting();

        std::cout<< "current context: " << QOpenGLContext::currentContext();

        //auto context = QOpenGLContext::currentContext();
        //std::cout << "default fbo: " << context->defaultFramebufferObject() << std::endl;

        //GLint old_fbo;
        //context->functions()->glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &old_fbo);

        //std::cout << "was bound fbo: " << old_fbo << std::endl;

        //glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

//        glClearColor(1, 1, 0, 1);
//        glClear(GL_COLOR_BUFFER_BIT);


        glEnable(GL_SCISSOR_TEST);

        glScissor(x, y, w, h);
        glViewport(x, y, w, h);

        paint_opengl(w, h);

        glDisable(GL_SCISSOR_TEST);

        painter->endNativePainting();
    }
}

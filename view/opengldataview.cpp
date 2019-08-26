#include "opengldataview.h"

#include <QGraphicsView>
#include <QGraphicsScene>

OpenGLDataView::OpenGLDataView()
{
    initializeOpenGLFunctions();
}


void OpenGLDataView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    if (view)
    {
        auto scene_top_left = mapToScene(boundingRect().topLeft());
        auto scene_bot_right = mapToScene(boundingRect().bottomRight());
        auto view_top_left = view->mapFromScene(scene_top_left);
        auto view_bot_right = view->mapFromScene(scene_bot_right);

        auto x = view_top_left.x();
        auto y = view->height() - view_bot_right.y() - 2; // -2 seems to be necessary to be placed right
        auto w = view_bot_right.x() - x;
        auto h = view_bot_right.y() - view_top_left.y();

        painter->beginNativePainting();

        glEnable(GL_SCISSOR_TEST);

        glScissor(x, y, w, h);
        glViewport(x, y, w, h);

        paint_opengl(w, h);

        glDisable(GL_SCISSOR_TEST);

        painter->endNativePainting();
    }
}

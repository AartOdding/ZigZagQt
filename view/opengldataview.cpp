#include "opengldataview.h"

#include <QWindow>
#include <QGraphicsView>
#include <QGraphicsScene>




OpenGLDataView::OpenGLDataView(BaseOperator * parent_operator, const DataViewTypeInfo * type_info)
    : BaseDataView(parent_operator, type_info)
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

        double scale_factor = view->windowHandle()->devicePixelRatio();

        auto x = scale_factor * view_top_left.x();
        auto y = scale_factor * (view->height() - view_bot_right.y());
        auto w = scale_factor * (view_bot_right.x() - view_top_left.x());
        auto h = scale_factor * (view_bot_right.y() - view_top_left.y());

        painter->beginNativePainting();

        glEnable(GL_SCISSOR_TEST);

        glScissor(x, y, w, h);
        glViewport(x, y, w, h);

        paint_opengl(w, h);

        glDisable(GL_SCISSOR_TEST);

        painter->endNativePainting();
    }
}

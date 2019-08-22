#include "parameterpanelheader.h"

#include "parametereditor.h"

#include <QMouseEvent>
#include <QGuiApplication>


ParameterPanelHeader::ParameterPanelHeader(ParameterEditor* e)
    : QWidget(e), editor(*e)
{
    setAutoFillBackground(true);
    setCursor(Qt::SizeVerCursor);
    auto p = QGuiApplication::palette();
    p.setColor(QPalette::All, QPalette::Window, QColor(160, 160, 160));
    setPalette(p);
    setMinimumSize(QSize(50, 24));
}


void ParameterPanelHeader::mouseMoveEvent(QMouseEvent * event)
{
    event->accept();
    auto viewport = static_cast<QWidget*>(editor.parent());
    auto y = mapTo(viewport, event->pos()).y();
    auto top = y - offset_y;

    if (top < 1) top = 1;
    if (top > viewport->height() - height()) top = viewport->height() - height();

    auto g = editor.geometry();
    g.moveTop(top);
    editor.setGeometry(g);
}



void ParameterPanelHeader::mouseReleaseEvent(QMouseEvent * event)
{
    event->accept();
}

void ParameterPanelHeader::mousePressEvent(QMouseEvent * event)
{
    event->accept();
    start_y = mapTo(static_cast<QWidget*>(editor.parent()), event->pos()).y();
    offset_y = event->y();
}

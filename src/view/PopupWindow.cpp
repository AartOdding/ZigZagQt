#include "PopupWindow.hpp"

#include <QEvent>
#include <QMouseEvent>
#include <QApplication>



PopupWindow::PopupWindow(QWidget* presentedWidget, QWidget *parent)
    : QWidget(parent)
{
    m_layout.setMargin(3);
    setPresentedWidget(presentedWidget);
    QApplication::instance()->installEventFilter(this);
}



QWidget * PopupWindow::presentedWidget() const
{
    return m_presentedWidget;
}



void PopupWindow::setPresentedWidget(QWidget * widget)
{
    if (m_presentedWidget)
    {
        m_layout.removeWidget(m_presentedWidget);
        delete m_presentedWidget;
        m_presentedWidget = nullptr;
    }
    if (widget)
    {
        widget->setParent(this);
        m_layout.addWidget(widget);
        m_presentedWidget = widget;
    }
}



bool PopupWindow::eventFilter(QObject * object, QEvent * event)
{
    if (event->type() == QEvent::WindowDeactivate)
    {
        if (object == this)
        {
            QApplication::instance()->removeEventFilter(this);
            close();
        }
    }
    return false;
}

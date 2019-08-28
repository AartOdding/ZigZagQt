#include "parametereditor.h"
#include "parameterpanel.h"
#include "parametereditorheader.h"

#include <QScrollArea>
#include <QVBoxLayout>



ParameterEditor::ParameterEditor(QWidget* parent)
    : QWidget(parent), size_grip(this)
{
    setWindowFlags(Qt::SubWindow);

    header = new ParameterEditorHeader(this);
    content = new ParameterPanel(this);
    body = new QScrollArea(this);
    body->setWidgetResizable(true);
    body->setWidget(content);

    auto layout = new QVBoxLayout();
    layout->addWidget(header);
    layout->addWidget(body);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);

    content->show();
    size_grip.raise();
    setVisible(false);
}


void ParameterEditor::set_scene(QGraphicsScene* scene)
{
    content->set_scene(scene);
}

/*
size_grip.setGeometry(0, height() - 10, 10, 10);
header.setGeometry(0, 0, width(), 25);

setVisible(false);
*/


void ParameterEditor::resizeEvent(QResizeEvent *event)
{
    //header.setGeometry(0, 0, width(), 25);
    //QScrollArea::resizeEvent(event);
    QWidget::resizeEvent(event);
    size_grip.setGeometry(0, height() - 10, 10, 10);
}

#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QBoxLayout>

#include "parametergroup.h"


class BaseOperator;
class QGraphicsScene;



class ParameterEditor : public QWidget
{
    Q_OBJECT

public:

    ParameterEditor(QWidget* parent = nullptr);

    void set_scene(QGraphicsScene* scene);

public slots:

    void on_selection_changed();

private:

    QScrollArea scroll_area;
    QWidget parameter_area;
    QBoxLayout outer_layout{ QBoxLayout::TopToBottom, this };
    QBoxLayout inner_layout{ QBoxLayout::TopToBottom, &parameter_area };

    ParameterGroup * parameters = nullptr;

    QGraphicsScene* model = nullptr;


};





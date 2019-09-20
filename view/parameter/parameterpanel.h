#pragma once

#include <QWidget>
#include <QBoxLayout>


class BaseOperator;
class ParameterEditor;
class QGraphicsScene;
class ParameterPanelGroup;




class ParameterPanel : public QWidget
{
    Q_OBJECT

public:

    ParameterPanel(ParameterEditor* editor);

    void set_scene(QGraphicsScene* scene);


public slots:

    void on_selection_changed();


private:

    void build_ui(BaseOperator& op);

    QBoxLayout layout{ QBoxLayout::TopToBottom, this };
    QGraphicsScene* scene = nullptr;
    ParameterEditor* editor = nullptr;

    ParameterPanelGroup * parameters = nullptr;

};

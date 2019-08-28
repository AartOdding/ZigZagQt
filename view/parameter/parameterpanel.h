#pragma once

#include <QWidget>
#include <QVBoxLayout>


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

    void clear();

    void build_ui(BaseOperator& op);

    QVBoxLayout layout{ this };
    QGraphicsScene* scene = nullptr;
    ParameterEditor* editor = nullptr;

};

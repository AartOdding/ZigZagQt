#pragma once

#include <QWidget>

class BaseOperator;
class BaseParameter;
class ParameterEditor;
class QFormLayout;
class QGraphicsScene;



class ParameterPanel : public QWidget
{
    Q_OBJECT

public:

    ParameterPanel(ParameterEditor* editor);

    void set_scene(QGraphicsScene* scene);

    //QSize sizeHint() const override { return QSize(400, 500); }


public slots:

    void on_selection_changed();


private:

    void clear();

    void build_ui(BaseOperator& op);

    void reset_layout();

    void add_parameters(const std::vector<BaseParameter*>& parameters);


    QGraphicsScene* scene = nullptr;

    QFormLayout * layout = nullptr;

    ParameterEditor* editor = nullptr;

    QFont MontSerrat = QFont("MontSerrat");

};

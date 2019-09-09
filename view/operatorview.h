#pragma once

#include <unordered_map>

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QGraphicsRectItem>

#include "operatornametag.h"


class BaseOperator;
class DataConnector;
class ParameterConnector;
class DataInput;
class BaseDataType;
class BaseDataView;
class ProjectScopeView;



class OperatorView : public QObject,
                     public QGraphicsItem
{
    Q_OBJECT

public:

    OperatorView(BaseOperator& operator_model);

    QRectF boundingRect() const override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;


    BaseOperator& operator_model;

    ProjectScopeView * scope_view();

    DataConnector* data_connector_in(const DataInput* input);
    DataConnector* data_connector_out(const BaseDataType* output);
    ParameterConnector* parameter_connector_in() const;
    ParameterConnector* parameter_connector_out() const;


public slots:

    void on_operator_moved(int to_x, int to_y);


signals:

    void has_moved();


protected:

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;


private:

    static constexpr int width = 200;
    static constexpr int height = 160;

    int position_x;
    int position_y;

    bool was_dragged = false;

    std::unordered_map<const DataInput*, DataConnector*> inputs;
    std::unordered_map<const BaseDataType*, DataConnector*> outputs;

    QGraphicsWidget inputs_panel{ this };
    QGraphicsWidget outputs_panel{ this };

    OperatorNameTag name_tag;
    BaseDataView* data_view = nullptr;
    QGraphicsRectItem selection_rect{ this };

};

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
class OperatorNetworkView;



class OperatorView : public QGraphicsWidget
{
    Q_OBJECT

public:

    OperatorView(BaseOperator* operatorModel);

    virtual ~OperatorView() override;

    //QRectF boundingRect() const override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem*, QWidget* = nullptr) override;


    DataConnector* getDataInput(const DataInput* input);
    DataConnector* getDataOutput(const BaseDataType* output);
    ParameterConnector* getParameterInput() const;
    ParameterConnector* getParameterOutput() const;

    BaseOperator* getOperatorModel();
    OperatorNetworkView * getNetworkView();


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

    void focusInEvent(QFocusEvent * event) override;
    void focusOutEvent(QFocusEvent * event) override;

private:

    static constexpr int width = 200;
    static constexpr int height = 160;

    BaseOperator* m_operatorModel;

    int m_posX;
    int m_posY;

    bool was_dragged = false;

    std::unordered_map<const DataInput*, DataConnector*> inputs;
    std::unordered_map<const BaseDataType*, DataConnector*> outputs;
    QList<BaseDataView*> m_dataViews;

    QGraphicsWidget inputs_panel{ this };
    QGraphicsWidget outputs_panel{ this };

    OperatorNameTag name_tag;
    BaseDataView* data_view = nullptr;
    QGraphicsRectItem selection_rect{ this };

};

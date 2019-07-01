#pragma once

#include <QObject>
#include <QGraphicsItem>

class BaseOperator;
class OperatorView;



class ConnectorView : public QObject,
                      public QGraphicsItem
{
    Q_OBJECT


public:

    ConnectorView(OperatorView& parent, BaseOperator* operator_model, int index, bool is_input);

    QRectF boundingRect() const override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;



public slots:


private:

    BaseOperator* operator_model;
    int index;
    bool is_input;

};

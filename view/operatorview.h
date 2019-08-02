#pragma once

#include <unordered_map>

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

#include "operatornametag.h"


class BaseOperator;
class ProgramModel;
class DataConnectorView;
class BaseDataBlock;
class DataBlockInput;


class OperatorView : public QObject,
                     public QGraphicsItem
{
    Q_OBJECT

public:

    OperatorView(BaseOperator& operator_model);

    QRectF boundingRect() const override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    DataConnectorView* get_view_of(const DataBlockInput* input);

    DataConnectorView* get_view_of(const BaseDataBlock* output);


    BaseOperator& operator_model;

public slots:

    void on_operator_moved(int to_x, int to_y);

    void on_inputs_modified();
    void on_outputs_modified();
    void on_parameters_modified();

signals:

    void has_moved();


protected:

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;


private:

    static constexpr int width = 200;
    static constexpr int height = 160;

    int position_x;
    int position_y;

    bool was_dragged = false;

    std::unordered_map<const DataBlockInput*, DataConnectorView*> inputs;
    std::unordered_map<const BaseDataBlock*, DataConnectorView*> outputs;

    OperatorNameTag name_tag;
    QGraphicsRectItem selection_rect{ this };

};

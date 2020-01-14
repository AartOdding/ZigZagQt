#pragma once

#include "view/basedataview.h"
#include "model/parameter/BaseComponent.hpp"
#include <QObject>


class BaseOperator;

class ParameterView : public BaseDataView
{
    Q_OBJECT

public:

    ParameterView(BaseOperator* parent_operator, const BaseComponent* component);


    static BaseDataView* create(BaseOperator* parent_operator) { return new ParameterView(parent_operator, nullptr); }

    static const inline DataViewTypeInfo Type { "Parameter Preview", "Control", DataViewGraphicsApi::QPainter, &create };


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;


public slots:

    void onValueChangedDouble(double newValue);

    void onValueChangedInt(int64_t newValue);

    void onUpdateNecessary();

private:

    const BaseDataType* viewed_data;

    bool is_int = true;

    const BaseComponent * m_viewedComponent;

    double floatValue = 0;
    int64_t intValue = 0;

};



#include "parameterpanelgroup.h"

#include "model/parameter/baseparameter.h"
#include "model/parameter/parameterowner.h"
#include "model/parameter/parameterrow.h"

#include "intwidget.h"
#include "floatwidget.h"
#include "enumwidget.h"


#include <QLabel>



ParameterPanelGroup::ParameterPanelGroup(QWidget *parent, ParameterOwner& group_owner)
    : QWidget(parent), owner(&group_owner)
{
    layout.setContentsMargins(0, 0, 0, 0);
    layout.addRow(new QLabel("Parameters"));

    for (auto par : owner->parameters())
    {
        layout.addRow(par->name(), new_widget_for_parameter(par));
    }

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout.addRow(line);
}


QWidget* ParameterPanelGroup::new_widget_for_parameter(BaseParameter* par)
{
    if (par)
    {
        switch (par->type())
        {
            case ParameterType::Int:
                return new IntWidget(this, static_cast<IntPar*>(par));
            case ParameterType::Int2:
                return new IntWidget(this, static_cast<Int2Par*>(par));
            case ParameterType::Int3:
                return new IntWidget(this, static_cast<Int3Par*>(par));
            case ParameterType::Int4:
                return new IntWidget(this, static_cast<Int4Par*>(par));

            case ParameterType::Float:
                return new FloatWidget(this, static_cast<FloatPar*>(par));
            case ParameterType::Float2:
                return new FloatWidget(this, static_cast<Float2Par*>(par));
            case ParameterType::Float3:
                return new FloatWidget(this, static_cast<Float3Par*>(par));
            case ParameterType::Float4:
                return new FloatWidget(this, static_cast<Float4Par*>(par));

            case ParameterType::Enum:
                return new EnumWidget(this, static_cast<EnumPar*>(par));

            case ParameterType::ParameterRow:
                return new_widget_for_row(static_cast<ParameterRow*>(par));
        }
    }
    return nullptr;
}



QWidget* ParameterPanelGroup::new_widget_for_row(ParameterRow* parameter_row)
{
    if (parameter_row->parameters().size() > 0)
    {
        auto * widget = new QWidget(this);
        auto * l = new QHBoxLayout(widget);
        l->setContentsMargins(0, 0, 0, 0);

        for (auto par : parameter_row->parameters())
        {
            l->addWidget(new_widget_for_parameter(par));
        }
        return widget;
    }
    return nullptr;
}

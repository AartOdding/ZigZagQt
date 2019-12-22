#pragma once

#include <QColor>

#include "model/parameter/BaseParameter.hpp"
#include "model/parameter/Float64Component.hpp"



class ColorParameter : public BaseParameter
{
public:

    ColorParameter(BaseZigZagObject * parent, const QString& name, QColor color = Qt::black);

    void set(const QColor& color);

    QColor get() const;

private:


    Float64Component m_red   { this, 0, 0, 1 };
    Float64Component m_green { this, 0, 0, 1 };
    Float64Component m_blue  { this, 0, 0, 1 };
    Float64Component m_alpha { this, 0, 0, 1 };

};


using ColorPar = ColorParameter;

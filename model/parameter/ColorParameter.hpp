#pragma once

#include <QColor>

#include "model/parameter/BaseParameter.hpp"
#include "model/parameter/Float64Component.hpp"



class ColorParameter : public BaseParameter
{
    Q_OBJECT

public:

    ColorParameter(BaseZigZagObject * parent, const QString& name, QColor color = Qt::black);

    void set(const QColor& color);

    QColor get() const;

private:


    Float64Component m_red   { this, QStringLiteral("Red"),   0, 0, 1 };
    Float64Component m_green { this, QStringLiteral("Green"), 0, 0, 1 };
    Float64Component m_blue  { this, QStringLiteral("Blue"),  0, 0, 1 };
    Float64Component m_alpha { this, QStringLiteral("Alpha"), 0, 0, 1 };

};


using ColorPar = ColorParameter;

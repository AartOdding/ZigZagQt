#pragma once

#include <array>

#include "BaseParameter.hpp"
#include "Float64Component.hpp"



using double_2 = std::array<double, 2>;
using double_3 = std::array<double, 3>;
using double_4 = std::array<double, 4>;



class FloatParameter : public BaseParameter
{
    Q_OBJECT

public:

    FloatParameter(BaseZigZagObject * parent, const QString& name, double value = 0);
    FloatParameter(BaseZigZagObject * parent, const QString& name, double value, double min, double max);

    double get() const;
    double value() const;

    void set(double value);

private:

    Float64Component m_value;

};




class Float2Parameter : public BaseParameter
{
    Q_OBJECT

public:

    Float2Parameter(BaseZigZagObject * parent, const QString& name, double_2 value = double_2());
    Float2Parameter(BaseZigZagObject * parent, const QString& name, double_2 value, double_2 min, double_2 max);

    double x() const;
    double y() const;

    void setX(double x);
    void setY(double y);

    void set(double x, double y);

private:

    Float64Component m_xValue;
    Float64Component m_yValue;

};




class Float3Parameter : public BaseParameter
{
    Q_OBJECT

public:

    Float3Parameter(BaseZigZagObject * parent, const QString& name, double_3 value = double_3());
    Float3Parameter(BaseZigZagObject * parent, const QString& name, double_3 value, double_3 min, double_3 max);

    double x() const;
    double y() const;
    double z() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    void set(double x, double y, double z);

private:

    Float64Component m_xValue;
    Float64Component m_yValue;
    Float64Component m_zValue;

};




class Float4Parameter : public BaseParameter
{
    Q_OBJECT

public:

    Float4Parameter(BaseZigZagObject * parent, const QString& name, double_4 value = double_4());
    Float4Parameter(BaseZigZagObject * parent, const QString& name, double_4 value, double_4 min, double_4 max);

    double x() const;
    double y() const;
    double z() const;
    double w() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setW(double w);

    void set(double x, double y, double z, double w);

private:

    Float64Component m_xValue;
    Float64Component m_yValue;
    Float64Component m_zValue;
    Float64Component m_wValue;

};

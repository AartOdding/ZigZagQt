#pragma once

#include <array>
#include <cstdint>

#include "BaseParameter.hpp"
#include "Int64Component.hpp"



using int64 = int64_t;
using int64_2 = std::array<int64, 2>;
using int64_3 = std::array<int64, 3>;
using int64_4 = std::array<int64, 4>;



class IntParameter : public BaseParameter
{
    Q_OBJECT

public:

    IntParameter(BaseZigZagObject * parent, const QString& name, int64 value = 0);
    IntParameter(BaseZigZagObject * parent, const QString& name, int64 value, int64 min, int64 max);

    int64 get() const;
    int64 value() const;

    void set(int64 value);

private:

    Int64Component m_value;

};




class Int2Parameter : public BaseParameter
{
    Q_OBJECT

public:

    Int2Parameter(BaseZigZagObject * parent, const QString& name, int64_2 value = int64_2());
    Int2Parameter(BaseZigZagObject * parent, const QString& name, int64_2 value, int64_2 min, int64_2 max);

    int64 x() const;
    int64 y() const;

    void setX(int64 x);
    void setY(int64 y);

    void set(int64 x, int64 y);

private:

    Int64Component m_xValue;
    Int64Component m_yValue;

};




class Int3Parameter : public BaseParameter
{
    Q_OBJECT

public:

    Int3Parameter(BaseZigZagObject * parent, const QString& name, int64_3 value = int64_3());
    Int3Parameter(BaseZigZagObject * parent, const QString& name, int64_3 value, int64_3 min, int64_3 max);

    int64 x() const;
    int64 y() const;
    int64 z() const;

    void setX(int64 x);
    void setY(int64 y);
    void setZ(int64 z);

    void set(int64 x, int64 y, int64 z);

private:

    Int64Component m_xValue;
    Int64Component m_yValue;
    Int64Component m_zValue;

};




class Int4Parameter : public BaseParameter
{
    Q_OBJECT

public:

    Int4Parameter(BaseZigZagObject * parent, const QString& name, int64_4 value = int64_4());
    Int4Parameter(BaseZigZagObject * parent, const QString& name, int64_4 value, int64_4 min, int64_4 max);

    int64 x() const;
    int64 y() const;
    int64 z() const;
    int64 w() const;

    void setX(int64 x);
    void setY(int64 y);
    void setZ(int64 z);
    void setW(int64 w);

    void set(int64 x, int64 y, int64 z, int64 w);

private:

    Int64Component m_xValue;
    Int64Component m_yValue;
    Int64Component m_zValue;
    Int64Component m_wValue;

};



using IntPar  = IntParameter;
using Int2Par = Int2Parameter;
using Int3Par = Int3Parameter;
using Int4Par = Int4Parameter;

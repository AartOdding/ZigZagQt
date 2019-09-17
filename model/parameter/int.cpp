#include "int.h"


IntPar::IntPar(ParameterOwner * owner, const char * name, int32 value)
    : ArithmeticParameter(owner, ParameterType::Int, name),
      m_value(value)
{

}


IntPar::IntPar(ParameterOwner * owner, const char * name, int32 value, int32 min, int32 max)
    : ArithmeticParameter(owner, ParameterType::Int, name),
      m_value(value, min, max)
{

}


int32 IntPar::value() const
{
    return m_value;
}


void IntPar::set_value(int32 new_value)
{
    bool changed;
    m_value.set(new_value, changed);
    if (changed)
    {
        flag_changed();
        emit value_changed();
        emit value_changed_to(m_value);
    }
}


int32 IntPar::min() const
{
    return m_value.get_min();
}


int32 IntPar::max() const
{
    return m_value.get_max();
}


void IntPar::set_min(int32 new_min)
{
    bool changed;
    m_value.set_min(new_min, changed);
    if (changed)
    {
        flag_changed();
        emit value_changed();
        emit value_changed_to(m_value);
    }
}


void IntPar::set_max(int32 new_max)
{
    bool changed;
    m_value.set_max(new_max, changed);
    if (changed)
    {
        flag_changed();
        emit value_changed();
        emit value_changed_to(m_value);
    }
}


IntPar::operator int32() const
{
    return value();
}


void IntPar::operator=(int32 new_value)
{
    set_value(new_value);
}


int32 IntPar::int_at(unsigned index) const
{
    return index == 0 ? value() : 0;
}


double IntPar::double_at(unsigned index) const
{
    return index == 0 ? value() : 0;
}


void IntPar::import_flagged_changed()
{
    Q_ASSERT(dynamic_cast<ArithmeticParameter*>(get_import()));
    auto i = static_cast<ArithmeticParameter*>(get_import());
    set_value(i->int_at(0));
}


/*********************/
/*                   */
/*      Int2Par      */
/*                   */
/*********************/


Int2Par::Int2Par(ParameterOwner * owner, const char * name, int32 val)
    : Int2Par(owner, name, { val, val })
{

}


Int2Par::Int2Par(ParameterOwner * owner, const char * name, int32 val, int32 min, int32 max)
    : Int2Par(owner, name, { val, val }, min, max)
{

}


Int2Par::Int2Par(ParameterOwner * owner, const char * name, int32_2 values)
    : ArithmeticParameter(owner, ParameterType::Int2, name),
      x_value(this, "X", values[0]),
      y_value(this, "Y", values[1])
{

}


Int2Par::Int2Par(ParameterOwner * owner, const char * name, int32_2 values, int32 min, int32 max)
    : ArithmeticParameter(owner, ParameterType::Int2, name),
      x_value(this, "X", values[0], min, max),
      y_value(this, "Y", values[1], min, max)
{

}


int32 Int2Par::x() const
{
    return x_value.value();
}


int32 Int2Par::y() const
{
    return y_value.value();
}


void Int2Par::set_x(int32 new_x)
{
    x_value.set_value(new_x);
}


void Int2Par::set_y(int32 new_y)
{
    y_value.set_value(new_y);
}


int32 Int2Par::min() const
{
    return x_value.min();
}


int32 Int2Par::max() const
{
    return x_value.max();
}


void Int2Par::set_min(int32 new_min)
{
    x_value.set_min(new_min);
    y_value.set_min(new_min);
}


void Int2Par::set_max(int32 new_max)
{
    x_value.set_max(new_max);
    y_value.set_max(new_max);
}


int32_2 Int2Par::get() const
{
    return { x_value.value(), y_value.value() };
}


void Int2Par::set(int32_2 new_values)
{
    x_value.set_value(new_values[0]);
    y_value.set_value(new_values[1]);
}


void Int2Par::set(int32 x, int32 y)
{
    x_value.set_value(x);
    y_value.set_value(y);
}


Int2Par::operator int32_2() const
{
    return get();
}


void Int2Par::operator=(int32_2 new_values)
{
    set(new_values);
}


int32 Int2Par::int_at(unsigned index) const
{
    return index < 2 ? get()[index] : 0;
}


double Int2Par::double_at(unsigned index) const
{
    return index < 2 ? get()[index] : 0;
}


void Int2Par::import_flagged_changed()
{
    Q_ASSERT(dynamic_cast<ArithmeticParameter*>(get_import()));
    auto i = static_cast<ArithmeticParameter*>(get_import());
    set_x(i->int_at(0));
    set_y(i->int_at(1));
}


/*********************/
/*                   */
/*      Int3Par      */
/*                   */
/*********************/


Int3Par::Int3Par(ParameterOwner * owner, const char * name, int32 val)
    : Int3Par(owner, name, { val, val, val })
{

}


Int3Par::Int3Par(ParameterOwner * owner, const char * name, int32 val, int32 min, int32 max)
    : Int3Par(owner, name, { val, val, val }, min, max)
{

}


Int3Par::Int3Par(ParameterOwner * owner, const char * name, int32_3 values)
    : ArithmeticParameter(owner, ParameterType::Int3, name),
      x_value(this, "X", values[0]),
      y_value(this, "Y", values[1]),
      z_value(this, "Z", values[2])
{

}


Int3Par::Int3Par(ParameterOwner * owner, const char * name, int32_3 values, int32 min, int32 max)
    : ArithmeticParameter(owner, ParameterType::Int3, name),
      x_value(this, "X", values[0], min, max),
      y_value(this, "Y", values[1], min, max),
      z_value(this, "Z", values[2], min, max)
{

}


int32 Int3Par::x() const
{
    return x_value.value();
}


int32 Int3Par::y() const
{
    return y_value.value();
}


int32 Int3Par::z() const
{
    return z_value.value();
}


void Int3Par::set_x(int32 new_x)
{
    x_value.set_value(new_x);
}


void Int3Par::set_y(int32 new_y)
{
    y_value.set_value(new_y);
}


void Int3Par::set_z(int32 new_z)
{
    z_value.set_value(new_z);
}


int32 Int3Par::min() const
{
    return x_value.min();
}


int32 Int3Par::max() const
{
    return x_value.max();
}


void Int3Par::set_min(int32 new_min)
{
    x_value.set_min(new_min);
    y_value.set_min(new_min);
    z_value.set_min(new_min);
}


void Int3Par::set_max(int32 new_max)
{
    x_value.set_max(new_max);
    y_value.set_max(new_max);
    z_value.set_max(new_max);
}


int32_3 Int3Par::get() const
{
    return { x_value.value(), y_value.value(), z_value.value() };
}


void Int3Par::set(int32_3 new_values)
{
    x_value.set_value(new_values[0]);
    y_value.set_value(new_values[1]);
    z_value.set_value(new_values[2]);
}


void Int3Par::set(int32 x, int32 y, int32 z)
{
    x_value.set_value(x);
    y_value.set_value(y);
    z_value.set_value(z);
}


Int3Par::operator int32_3() const
{
    return get();
}


void Int3Par::operator=(int32_3 new_values)
{
    set(new_values);
}


int32 Int3Par::int_at(unsigned index) const
{
    return index < 3 ? get()[index] : 0;
}


double Int3Par::double_at(unsigned index) const
{
    return index < 3 ? get()[index] : 0;
}


void Int3Par::import_flagged_changed()
{
    Q_ASSERT(dynamic_cast<ArithmeticParameter*>(get_import()));
    auto i = static_cast<ArithmeticParameter*>(get_import());
    set_x(i->int_at(0));
    set_y(i->int_at(1));
    set_z(i->int_at(2));
}


/*********************/
/*                   */
/*      Int4Par      */
/*                   */
/*********************/


Int4Par::Int4Par(ParameterOwner * owner, const char * name, int32 val)
    : Int4Par(owner, name, { val, val, val, val })
{

}


Int4Par::Int4Par(ParameterOwner * owner, const char * name, int32 val, int32 min, int32 max)
    : Int4Par(owner, name, { val, val, val, val }, min, max)
{

}


Int4Par::Int4Par(ParameterOwner * owner, const char * name, int32_4 values)
    : ArithmeticParameter(owner, ParameterType::Int4, name),
      x_value(this, "X", values[0]),
      y_value(this, "Y", values[1]),
      z_value(this, "Z", values[2]),
      w_value(this, "W", values[3])
{

}


Int4Par::Int4Par(ParameterOwner * owner, const char * name, int32_4 values, int32 min, int32 max)
    : ArithmeticParameter(owner, ParameterType::Int4, name),
      x_value(this, "X", values[0], min, max),
      y_value(this, "Y", values[1], min, max),
      z_value(this, "Z", values[2], min, max),
      w_value(this, "W", values[3], min, max)
{

}


int32 Int4Par::x() const
{
    return x_value.value();
}


int32 Int4Par::y() const
{
    return y_value.value();
}


int32 Int4Par::z() const
{
    return z_value.value();
}


int32 Int4Par::w() const
{
    return w_value.value();
}


void Int4Par::set_x(int32 new_x)
{
    x_value.set_value(new_x);
}


void Int4Par::set_y(int32 new_y)
{
    y_value.set_value(new_y);
}


void Int4Par::set_z(int32 new_z)
{
    z_value.set_value(new_z);
}


void Int4Par::set_w(int32 new_w)
{
    w_value.set_value(new_w);
}


int32 Int4Par::min() const
{
    //Q_ASSERT(x_value.get_min() == y_value.get_min() == z_value.get_min() == w_value.get_min());
    return x_value.min();
}


int32 Int4Par::max() const
{
    //Q_ASSERT(x_value.get_max() == y_value.get_max() == z_value.get_max() == w_value.get_max());
    return x_value.max();
}


void Int4Par::set_min(int32 new_min)
{
    x_value.set_min(new_min);
    y_value.set_min(new_min);
    z_value.set_min(new_min);
    w_value.set_min(new_min);
}


void Int4Par::set_max(int32 new_max)
{
    x_value.set_max(new_max);
    y_value.set_max(new_max);
    z_value.set_max(new_max);
    w_value.set_max(new_max);
}


int32_4 Int4Par::get() const
{
    return { x_value.value(), y_value.value(), z_value.value(), w_value.value() };
}


void Int4Par::set(int32_4 new_values)
{
    x_value.set_value(new_values[0]);
    y_value.set_value(new_values[1]);
    z_value.set_value(new_values[2]);
    w_value.set_value(new_values[3]);
}


void Int4Par::set(int32 x, int32 y, int32 z, int32 w)
{
    x_value.set_value(x);
    y_value.set_value(y);
    z_value.set_value(z);
    w_value.set_value(w);
}


Int4Par::operator int32_4() const
{
    return get();
}


void Int4Par::operator=(int32_4 new_values)
{
    set(new_values);
}


int32 Int4Par::int_at(unsigned index) const
{
    return index < 4 ? get()[index] : 0;
}


double Int4Par::double_at(unsigned index) const
{
    return index < 4 ? get()[index] : 0;
}


void Int4Par::import_flagged_changed()
{
    Q_ASSERT(dynamic_cast<ArithmeticParameter*>(get_import()));
    auto i = static_cast<ArithmeticParameter*>(get_import());
    set_x(i->int_at(0));
    set_y(i->int_at(1));
    set_z(i->int_at(2));
    set_w(i->int_at(3));
}

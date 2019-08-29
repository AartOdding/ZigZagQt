#include "int.h"


IntPar::IntPar(ParameterOwner * owner, const char * name, int32 val)
    : ArithmeticParameter(owner, ParameterType::Int, name),
      value(val)
{

}


IntPar::IntPar(ParameterOwner * owner, const char * name, int32 val, int32 min, int32 max)
    : ArithmeticParameter(owner, ParameterType::Int, name),
      value(val, min, max)
{

}


int32 IntPar::get() const
{
    return value.get();
}


void IntPar::set(int32 new_value)
{
    bool changed;
    value.set(new_value, changed);
    if (changed) flag_changed();
}


int32 IntPar::min() const
{
    return value.get_min();
}


int32 IntPar::max() const
{
    return value.get_max();
}


void IntPar::set_min(int32 new_min)
{
    bool changed;
    value.set_min(new_min, changed);
    if (changed) flag_changed();
}


void IntPar::set_max(int32 new_max)
{
    bool changed;
    value.set_max(new_max, changed);
    if (changed) flag_changed();
}


IntPar::operator int32() const
{
    return get();
}


void IntPar::operator=(int32 new_value)
{
    set(new_value);
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
      x_value(values[0]),
      y_value(values[1])
{

}


Int2Par::Int2Par(ParameterOwner * owner, const char * name, int32_2 values, int32 min, int32 max)
    : ArithmeticParameter(owner, ParameterType::Int2, name),
      x_value(values[0], min, max),
      y_value(values[1], min, max)
{

}


int32 Int2Par::x() const
{
    return x_value.get();
}


int32 Int2Par::y() const
{
    return y_value.get();
}


void Int2Par::set_x(int32 new_x)
{
    bool changed;
    x_value.set(new_x, changed);
    if (changed) flag_changed();
}


void Int2Par::set_y(int32 new_y)
{
    bool changed;
    y_value.set(new_y, changed);
    if (changed) flag_changed();
}


int32 Int2Par::min() const
{
    //Q_ASSERT(x_value.get_min() == y_value.get_min());
    return x_value.get_min();
}


int32 Int2Par::max() const
{
    //Q_ASSERT(x_value.get_max() == y_value.get_max());
    return x_value.get_max();
}


void Int2Par::set_min(int32 new_min)
{
    bool x_changed, y_changed;
    x_value.set_min(new_min, x_changed);
    y_value.set_min(new_min, y_changed);
    if (x_changed || y_changed) flag_changed();
}


void Int2Par::set_max(int32 new_max)
{
    bool x_changed, y_changed;
    x_value.set_max(new_max, x_changed);
    y_value.set_max(new_max, y_changed);
    if (x_changed || y_changed) flag_changed();
}


int32_2 Int2Par::get() const
{
    return { x_value.get(), y_value.get() };
}


void Int2Par::set(int32_2 new_values)
{
    bool x_changed, y_changed;
    x_value.set(new_values[0], x_changed);
    y_value.set(new_values[1], y_changed);
    if (x_changed || y_changed) flag_changed();
}


void Int2Par::set(int32 x, int32 y)
{
    bool x_changed, y_changed;
    x_value.set(x, x_changed);
    y_value.set(y, y_changed);
    if (x_changed || y_changed) flag_changed();
}


Int2Par::operator int32_2() const
{
    return get();
}


void Int2Par::operator=(int32_2 new_values)
{
    set(new_values);
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
      x_value(values[0]),
      y_value(values[1]),
      z_value(values[2])
{

}


Int3Par::Int3Par(ParameterOwner * owner, const char * name, int32_3 values, int32 min, int32 max)
    : ArithmeticParameter(owner, ParameterType::Int3, name),
      x_value(values[0], min, max),
      y_value(values[1], min, max),
      z_value(values[2], min, max)
{

}


int32 Int3Par::x() const
{
    return x_value.get();
}


int32 Int3Par::y() const
{
    return y_value.get();
}


int32 Int3Par::z() const
{
    return z_value.get();
}


void Int3Par::set_x(int32 new_x)
{
    bool changed;
    x_value.set(new_x, changed);
    if (changed) flag_changed();
}


void Int3Par::set_y(int32 new_y)
{
    bool changed;
    y_value.set(new_y, changed);
    if (changed) flag_changed();
}


void Int3Par::set_z(int32 new_z)
{
    bool changed;
    z_value.set(new_z, changed);
    if (changed) flag_changed();
}


int32 Int3Par::min() const
{
    //Q_ASSERT(x_value.get_min() == y_value.get_min() == z_value.get_min());
    return x_value.get_min();
}


int32 Int3Par::max() const
{
    //Q_ASSERT(x_value.get_max() == y_value.get_max() == z_value.get_max());
    return x_value.get_max();
}


void Int3Par::set_min(int32 new_min)
{
    bool x_changed, y_changed, z_changed;
    x_value.set_min(new_min, x_changed);
    y_value.set_min(new_min, y_changed);
    z_value.set_min(new_min, z_changed);
    if (x_changed || y_changed || z_changed) flag_changed();
}


void Int3Par::set_max(int32 new_max)
{
    bool x_changed, y_changed, z_changed;
    x_value.set_max(new_max, x_changed);
    y_value.set_max(new_max, y_changed);
    z_value.set_max(new_max, z_changed);
    if (x_changed || y_changed || z_changed) flag_changed();
}


int32_3 Int3Par::get() const
{
    return { x_value.get(), y_value.get(), z_value.get() };
}


void Int3Par::set(int32_3 new_values)
{
    bool x_changed, y_changed, z_changed;
    x_value.set(new_values[0], x_changed);
    y_value.set(new_values[1], y_changed);
    z_value.set(new_values[2], z_changed);
    if (x_changed || y_changed || z_changed) flag_changed();
}


void Int3Par::set(int32 x, int32 y, int32 z)
{
    bool x_changed, y_changed, z_changed;
    x_value.set(x, x_changed);
    y_value.set(y, y_changed);
    z_value.set(z, z_changed);
    if (x_changed || y_changed || z_changed) flag_changed();
}


Int3Par::operator int32_3() const
{
    return get();
}


void Int3Par::operator=(int32_3 new_values)
{
    set(new_values);
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
      x_value(values[0]),
      y_value(values[1]),
      z_value(values[2]),
      w_value(values[3])
{

}


Int4Par::Int4Par(ParameterOwner * owner, const char * name, int32_4 values, int32 min, int32 max)
    : ArithmeticParameter(owner, ParameterType::Int4, name),
      x_value(values[0], min, max),
      y_value(values[1], min, max),
      z_value(values[2], min, max),
      w_value(values[3], min, max)
{

}


int32 Int4Par::x() const
{
    return x_value.get();
}


int32 Int4Par::y() const
{
    return y_value.get();
}


int32 Int4Par::z() const
{
    return z_value.get();
}


int32 Int4Par::w() const
{
    return w_value.get();
}


void Int4Par::set_x(int32 new_x)
{
    bool changed;
    x_value.set(new_x, changed);
    if (changed) flag_changed();
}


void Int4Par::set_y(int32 new_y)
{
    bool changed;
    y_value.set(new_y, changed);
    if (changed) flag_changed();
}


void Int4Par::set_z(int32 new_z)
{
    bool changed;
    z_value.set(new_z, changed);
    if (changed) flag_changed();
}


void Int4Par::set_w(int32 new_w)
{
    bool changed;
    w_value.set(new_w, changed);
    if (changed) flag_changed();
}


int32 Int4Par::min() const
{
    //Q_ASSERT(x_value.get_min() == y_value.get_min() == z_value.get_min() == w_value.get_min());
    return x_value.get_min();
}


int32 Int4Par::max() const
{
    //Q_ASSERT(x_value.get_max() == y_value.get_max() == z_value.get_max() == w_value.get_max());
    return x_value.get_max();
}


void Int4Par::set_min(int32 new_min)
{
    bool x_changed, y_changed, z_changed, w_changed;
    x_value.set_min(new_min, x_changed);
    y_value.set_min(new_min, y_changed);
    z_value.set_min(new_min, z_changed);
    w_value.set_min(new_min, w_changed);
    if (x_changed || y_changed || z_changed || w_changed) flag_changed();
}


void Int4Par::set_max(int32 new_max)
{
    bool x_changed, y_changed, z_changed, w_changed;
    x_value.set_max(new_max, x_changed);
    y_value.set_max(new_max, y_changed);
    z_value.set_max(new_max, z_changed);
    w_value.set_max(new_max, w_changed);
    if (x_changed || y_changed || z_changed || w_changed) flag_changed();
}


int32_4 Int4Par::get() const
{
    return { x_value.get(), y_value.get(), z_value.get(), w_value.get() };
}


void Int4Par::set(int32_4 new_values)
{
    bool x_changed, y_changed, z_changed, w_changed;
    x_value.set(new_values[0], x_changed);
    y_value.set(new_values[1], y_changed);
    z_value.set(new_values[2], z_changed);
    w_value.set(new_values[3], w_changed);
    if (x_changed || y_changed || z_changed || w_changed) flag_changed();
}


void Int4Par::set(int32 x, int32 y, int32 z, int32 w)
{
    bool x_changed, y_changed, z_changed, w_changed;
    x_value.set(x, x_changed);
    y_value.set(y, y_changed);
    z_value.set(z, z_changed);
    w_value.set(w, w_changed);
    if (x_changed || y_changed || z_changed || w_changed) flag_changed();
}


Int4Par::operator int32_4() const
{
    return get();
}


void Int4Par::operator=(int32_4 new_values)
{
    set(new_values);
}

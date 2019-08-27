#include "float.h"


FloatPar::FloatPar(ParameterOwner * owner, const char * name, float64 val)
    : BaseParameter(owner, ParameterType::Float, name),
      value(val)
{

}


FloatPar::FloatPar(ParameterOwner * owner, const char * name, float64 val, float64 min, float64 max)
    : BaseParameter(owner, ParameterType::Float, name),
      value(val, min, max)
{

}


float64 FloatPar::get() const
{
    return value.get();
}


void FloatPar::set(float64 new_value)
{
    bool changed;
    value.set(new_value, changed);
    if (changed) flag_changed();
}


float64 FloatPar::min() const
{
    return value.get_min();
}


float64 FloatPar::max() const
{
    return value.get_max();
}


void FloatPar::set_min(float64 new_min)
{
    bool changed;
    value.set_min(new_min, changed);
    if (changed) flag_changed();
}


void FloatPar::set_max(float64 new_max)
{
    bool changed;
    value.set_max(new_max, changed);
    if (changed) flag_changed();
}


FloatPar::operator float64() const
{
    return get();
}


void FloatPar::operator=(float64 new_value)
{
    set(new_value);
}


/*********************/
/*                   */
/*      Int2Par      */
/*                   */
/*********************/


Float2Par::Float2Par(ParameterOwner * owner, const char * name, float64 val)
    : Float2Par(owner, name, { val, val })
{

}


Float2Par::Float2Par(ParameterOwner * owner, const char * name, float64 val, float64 min, float64 max)
    : Float2Par(owner, name, { val, val }, min, max)
{

}


Float2Par::Float2Par(ParameterOwner * owner, const char * name, float64_2 values)
    : BaseParameter(owner, ParameterType::Float2, name),
      x_value(values[0]),
      y_value(values[1])
{

}


Float2Par::Float2Par(ParameterOwner * owner, const char * name, float64_2 values, float64 min, float64 max)
    : BaseParameter(owner, ParameterType::Float2, name),
      x_value(values[0], min, max),
      y_value(values[1], min, max)
{

}


float64 Float2Par::x() const
{
    return x_value.get();
}


float64 Float2Par::y() const
{
    return y_value.get();
}


void Float2Par::set_x(float64 new_x)
{
    bool changed;
    x_value.set(new_x, changed);
    if (changed) flag_changed();
}


void Float2Par::set_y(float64 new_y)
{
    bool changed;
    y_value.set(new_y, changed);
    if (changed) flag_changed();
}


float64 Float2Par::min() const
{
    //Q_ASSERT(x_value.get_min() == y_value.get_min());
    return x_value.get_min();
}


float64 Float2Par::max() const
{
    //Q_ASSERT(x_value.get_max() == y_value.get_max());
    return x_value.get_max();
}


void Float2Par::set_min(float64 new_min)
{
    bool x_changed, y_changed;
    x_value.set_min(new_min, x_changed);
    y_value.set_min(new_min, y_changed);
    if (x_changed || y_changed) flag_changed();
}


void Float2Par::set_max(float64 new_max)
{
    bool x_changed, y_changed;
    x_value.set_max(new_max, x_changed);
    y_value.set_max(new_max, y_changed);
    if (x_changed || y_changed) flag_changed();
}


float64_2 Float2Par::get() const
{
    return { x_value.get(), y_value.get() };
}


void Float2Par::set(float64_2 new_values)
{
    bool x_changed, y_changed;
    x_value.set(new_values[0], x_changed);
    y_value.set(new_values[1], y_changed);
    if (x_changed || y_changed) flag_changed();
}


void Float2Par::set(float64 x, float64 y)
{
    bool x_changed, y_changed;
    x_value.set(x, x_changed);
    y_value.set(y, y_changed);
    if (x_changed || y_changed) flag_changed();
}


Float2Par::operator float64_2() const
{
    return get();
}


void Float2Par::operator=(float64_2 new_values)
{
    set(new_values);
}


/*********************/
/*                   */
/*      Int3Par      */
/*                   */
/*********************/


Float3Par::Float3Par(ParameterOwner * owner, const char * name, float64 val)
    : Float3Par(owner, name, { val, val, val })
{

}


Float3Par::Float3Par(ParameterOwner * owner, const char * name, float64 val, float64 min, float64 max)
    : Float3Par(owner, name, { val, val, val }, min, max)
{

}


Float3Par::Float3Par(ParameterOwner * owner, const char * name, float64_3 values)
    : BaseParameter(owner, ParameterType::Float3, name),
      x_value(values[0]),
      y_value(values[1]),
      z_value(values[2])
{

}


Float3Par::Float3Par(ParameterOwner * owner, const char * name, float64_3 values, float64 min, float64 max)
    : BaseParameter(owner, ParameterType::Float3, name),
      x_value(values[0], min, max),
      y_value(values[1], min, max),
      z_value(values[2], min, max)
{

}


float64 Float3Par::x() const
{
    return x_value.get();
}


float64 Float3Par::y() const
{
    return y_value.get();
}


float64 Float3Par::z() const
{
    return z_value.get();
}


void Float3Par::set_x(float64 new_x)
{
    bool changed;
    x_value.set(new_x, changed);
    if (changed) flag_changed();
}


void Float3Par::set_y(float64 new_y)
{
    bool changed;
    y_value.set(new_y, changed);
    if (changed) flag_changed();
}


void Float3Par::set_z(float64 new_z)
{
    bool changed;
    z_value.set(new_z, changed);
    if (changed) flag_changed();
}


float64 Float3Par::min() const
{
    //Q_ASSERT(x_value.get_min() == y_value.get_min() == z_value.get_min());
    return x_value.get_min();
}


float64 Float3Par::max() const
{
    //Q_ASSERT(x_value.get_max() == y_value.get_max() == z_value.get_max());
    return x_value.get_max();
}


void Float3Par::set_min(float64 new_min)
{
    bool x_changed, y_changed, z_changed;
    x_value.set_min(new_min, x_changed);
    y_value.set_min(new_min, y_changed);
    z_value.set_min(new_min, z_changed);
    if (x_changed || y_changed || z_changed) flag_changed();
}


void Float3Par::set_max(float64 new_max)
{
    bool x_changed, y_changed, z_changed;
    x_value.set_max(new_max, x_changed);
    y_value.set_max(new_max, y_changed);
    z_value.set_max(new_max, z_changed);
    if (x_changed || y_changed || z_changed) flag_changed();
}


float64_3 Float3Par::get() const
{
    return { x_value.get(), y_value.get(), z_value.get() };
}


void Float3Par::set(float64_3 new_values)
{
    bool x_changed, y_changed, z_changed;
    x_value.set(new_values[0], x_changed);
    y_value.set(new_values[1], y_changed);
    z_value.set(new_values[2], z_changed);
    if (x_changed || y_changed || z_changed) flag_changed();
}


void Float3Par::set(float64 x, float64 y, float64 z)
{
    bool x_changed, y_changed, z_changed;
    x_value.set(x, x_changed);
    y_value.set(y, y_changed);
    z_value.set(z, z_changed);
    if (x_changed || y_changed || z_changed) flag_changed();
}


Float3Par::operator float64_3() const
{
    return get();
}


void Float3Par::operator=(float64_3 new_values)
{
    set(new_values);
}


/*********************/
/*                   */
/*      Int4Par      */
/*                   */
/*********************/


Float4Par::Float4Par(ParameterOwner * owner, const char * name, float64 val)
    : Float4Par(owner, name, { val, val, val, val })
{

}


Float4Par::Float4Par(ParameterOwner * owner, const char * name, float64 val, float64 min, float64 max)
    : Float4Par(owner, name, { val, val, val, val }, min, max)
{

}


Float4Par::Float4Par(ParameterOwner * owner, const char * name, float64_4 values)
    : BaseParameter(owner, ParameterType::Float4, name),
      x_value(values[0]),
      y_value(values[1]),
      z_value(values[2]),
      w_value(values[3])
{

}


Float4Par::Float4Par(ParameterOwner * owner, const char * name, float64_4 values, float64 min, float64 max)
    : BaseParameter(owner, ParameterType::Float4, name),
      x_value(values[0], min, max),
      y_value(values[1], min, max),
      z_value(values[2], min, max),
      w_value(values[3], min, max)
{

}


float64 Float4Par::x() const
{
    return x_value.get();
}


float64 Float4Par::y() const
{
    return y_value.get();
}


float64 Float4Par::z() const
{
    return z_value.get();
}


float64 Float4Par::w() const
{
    return w_value.get();
}


void Float4Par::set_x(float64 new_x)
{
    bool changed;
    x_value.set(new_x, changed);
    if (changed) flag_changed();
}


void Float4Par::set_y(float64 new_y)
{
    bool changed;
    y_value.set(new_y, changed);
    if (changed) flag_changed();
}


void Float4Par::set_z(float64 new_z)
{
    bool changed;
    z_value.set(new_z, changed);
    if (changed) flag_changed();
}


void Float4Par::set_w(float64 new_w)
{
    bool changed;
    w_value.set(new_w, changed);
    if (changed) flag_changed();
}


float64 Float4Par::min() const
{
    //Q_ASSERT(x_value.get_min() == y_value.get_min() == z_value.get_min() == w_value.get_min());
    return x_value.get_min();
}


float64 Float4Par::max() const
{
    //Q_ASSERT(x_value.get_max() == y_value.get_max() == z_value.get_max() == w_value.get_max());
    return x_value.get_max();
}


void Float4Par::set_min(float64 new_min)
{
    bool x_changed, y_changed, z_changed, w_changed;
    x_value.set_min(new_min, x_changed);
    y_value.set_min(new_min, y_changed);
    z_value.set_min(new_min, z_changed);
    w_value.set_min(new_min, w_changed);
    if (x_changed || y_changed || z_changed || w_changed) flag_changed();
}


void Float4Par::set_max(float64 new_max)
{
    bool x_changed, y_changed, z_changed, w_changed;
    x_value.set_max(new_max, x_changed);
    y_value.set_max(new_max, y_changed);
    z_value.set_max(new_max, z_changed);
    w_value.set_max(new_max, w_changed);
    if (x_changed || y_changed || z_changed || w_changed) flag_changed();
}


float64_4 Float4Par::get() const
{
    return { x_value.get(), y_value.get(), z_value.get(), w_value.get() };
}


void Float4Par::set(float64_4 new_values)
{
    bool x_changed, y_changed, z_changed, w_changed;
    x_value.set(new_values[0], x_changed);
    y_value.set(new_values[1], y_changed);
    z_value.set(new_values[2], z_changed);
    w_value.set(new_values[3], w_changed);
    if (x_changed || y_changed || z_changed || w_changed) flag_changed();
}


void Float4Par::set(float64 x, float64 y, float64 z, float64 w)
{
    bool x_changed, y_changed, z_changed, w_changed;
    x_value.set(x, x_changed);
    y_value.set(y, y_changed);
    z_value.set(z, z_changed);
    w_value.set(w, w_changed);
    if (x_changed || y_changed || z_changed || w_changed) flag_changed();
}


Float4Par::operator float64_4() const
{
    return get();
}


void Float4Par::operator=(float64_4 new_values)
{
    set(new_values);
}

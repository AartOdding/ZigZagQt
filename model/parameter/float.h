#pragma once

#include <array>

#include "baseparameter.h"
#include "utility/bounded_value.h"



using float64 = double;
using float64_2 = std::array<float64, 2>;
using float64_3 = std::array<float64, 3>;
using float64_4 = std::array<float64, 4>;



class FloatPar : public BaseParameter
{
public:

    FloatPar(ParameterOwner * owner, const char * name, float64 value = 0);
    FloatPar(ParameterOwner * owner, const char * name, float64 value, float64 min, float64 max);

    float64 get() const;

    void set(float64 new_value);

    float64 min() const;
    float64 max() const;

    void set_min(float64 new_min);
    void set_max(float64 new_max);

    operator float64() const;
    void operator=(float64 new_value);


private:

    bounded_value<float64> value;

};




class Float2Par : public BaseParameter
{
public:

    Float2Par(ParameterOwner * owner, const char * name, float64 value = 0);
    Float2Par(ParameterOwner * owner, const char * name, float64 value, float64 min, float64 max);

    Float2Par(ParameterOwner * owner, const char * name, float64_2 values);
    Float2Par(ParameterOwner * owner, const char * name, float64_2 values, float64 min, float64 max);


    float64 x() const;
    float64 y() const;

    void set_x(float64 new_x);
    void set_y(float64 new_y);

    float64 min() const;
    float64 max() const;

    void set_min(float64 new_min);
    void set_max(float64 new_max);

    float64_2 get() const;

    void set(float64_2 new_values);
    void set(float64 x, float64 y);

    operator float64_2() const;
    void operator=(float64_2 new_values);


private:

    bounded_value<float64> x_value;
    bounded_value<float64> y_value;

};




class Float3Par : public BaseParameter
{
public:

    Float3Par(ParameterOwner * owner, const char * name, float64 value = 0);
    Float3Par(ParameterOwner * owner, const char * name, float64 value, float64 min, float64 max);

    Float3Par(ParameterOwner * owner, const char * name, float64_3 values);
    Float3Par(ParameterOwner * owner, const char * name, float64_3 values, float64 min, float64 max);


    float64 x() const;
    float64 y() const;
    float64 z() const;

    void set_x(float64 new_x);
    void set_y(float64 new_y);
    void set_z(float64 new_z);

    float64 min() const;
    float64 max() const;

    void set_min(float64 new_min);
    void set_max(float64 new_max);

    float64_3 get() const;

    void set(float64_3 new_values);
    void set(float64 x, float64 y, float64 z);

    operator float64_3() const;
    void operator=(float64_3 new_values);


private:

    bounded_value<float64> x_value;
    bounded_value<float64> y_value;
    bounded_value<float64> z_value;

};




class Float4Par : public BaseParameter
{
public:

    Float4Par(ParameterOwner * owner, const char * name, float64 value = 0);
    Float4Par(ParameterOwner * owner, const char * name, float64 value, float64 min, float64 max);

    Float4Par(ParameterOwner * owner, const char * name, float64_4 values);
    Float4Par(ParameterOwner * owner, const char * name, float64_4 values, float64 min, float64 max);


    float64 x() const;
    float64 y() const;
    float64 z() const;
    float64 w() const;

    void set_x(float64 new_x);
    void set_y(float64 new_y);
    void set_z(float64 new_z);
    void set_w(float64 new_w);

    float64 min() const;
    float64 max() const;

    void set_min(float64 new_min);
    void set_max(float64 new_max);

    float64_4 get() const;

    void set(float64_4 new_values);
    void set(float64 x, float64 y, float64 z, float64 w);

    operator float64_4() const;
    void operator=(float64_4 new_values);


private:

    bounded_value<float64> x_value;
    bounded_value<float64> y_value;
    bounded_value<float64> z_value;
    bounded_value<float64> w_value;


};



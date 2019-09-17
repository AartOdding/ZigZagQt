#pragma once

#include <array>
#include <cstdint>
#include <QMetaType>

#include "baseparameter.h"
#include "parameterowner.h"
#include "utility/constrained.h"



using int32 = int32_t;
using int32_2 = std::array<int32, 2>;
using int32_3 = std::array<int32, 3>;
using int32_4 = std::array<int32, 4>;

Q_DECLARE_METATYPE(int32);
Q_DECLARE_METATYPE(int32_2);
Q_DECLARE_METATYPE(int32_3);
Q_DECLARE_METATYPE(int32_4);




class IntPar : public ArithmeticParameter
{
    Q_OBJECT

public:

    IntPar(ParameterOwner * owner, const char * name, int32 value = 0);
    IntPar(ParameterOwner * owner, const char * name, int32 value, int32 min, int32 max);

    int32 value() const;
    int32 min() const;
    int32 max() const;

    operator int32() const;
    void operator=(int32 new_value);

    int32_t int_at(unsigned index) const override;
    double double_at(unsigned index) const override;


public slots:

    void set_value(int32 new_value);
    void set_min(int32 new_min);
    void set_max(int32 new_max);


protected slots:

    void import_flagged_changed() override;


signals:

    void value_changed();
    void value_changed_to(int32 new_value);


private:

    constrained<int32> m_value;

};




class Int2Par : public ArithmeticParameter,
                public ParameterOwner
{
public:

    Int2Par(ParameterOwner * owner, const char * name, int32 value = 0);
    Int2Par(ParameterOwner * owner, const char * name, int32 value, int32 min, int32 max);

    Int2Par(ParameterOwner * owner, const char * name, int32_2 values);
    Int2Par(ParameterOwner * owner, const char * name, int32_2 values, int32 min, int32 max);


    void flag_parameters_changed() override
    {
        ParameterOwner::flag_parameters_changed();
        BaseParameter::flag_changed();
    }

    int32 x() const;
    int32 y() const;

    void set_x(int32 new_x);
    void set_y(int32 new_y);

    int32 min() const;
    int32 max() const;

    void set_min(int32 new_min);
    void set_max(int32 new_max);

    int32_2 get() const;

    void set(int32_2 new_values);
    void set(int32 x, int32 y);

    operator int32_2() const;
    void operator=(int32_2 new_values);

    int32_t int_at(unsigned index) const override;
    double double_at(unsigned index) const override;

protected:

    void import_flagged_changed() override;

private:

    IntPar x_value;
    IntPar y_value;

};




class Int3Par : public ArithmeticParameter,
                public ParameterOwner
{
public:

    Int3Par(ParameterOwner * owner, const char * name, int32 value = 0);
    Int3Par(ParameterOwner * owner, const char * name, int32 value, int32 min, int32 max);

    Int3Par(ParameterOwner * owner, const char * name, int32_3 values);
    Int3Par(ParameterOwner * owner, const char * name, int32_3 values, int32 min, int32 max);


    void flag_parameters_changed() override
    {
        ParameterOwner::flag_parameters_changed();
        BaseParameter::flag_changed();
    }

    int32 x() const;
    int32 y() const;
    int32 z() const;

    void set_x(int32 new_x);
    void set_y(int32 new_y);
    void set_z(int32 new_z);

    int32 min() const;
    int32 max() const;

    void set_min(int32 new_min);
    void set_max(int32 new_max);

    int32_3 get() const;

    void set(int32_3 new_values);
    void set(int32 x, int32 y, int32 z);

    operator int32_3() const;
    void operator=(int32_3 new_values);

    int32_t int_at(unsigned index) const override;
    double double_at(unsigned index) const override;

protected:

    void import_flagged_changed() override;

private:

    IntPar x_value;
    IntPar y_value;
    IntPar z_value;

};




class Int4Par : public ArithmeticParameter,
                public ParameterOwner
{
public:

    Int4Par(ParameterOwner * owner, const char * name, int32 value = 0);
    Int4Par(ParameterOwner * owner, const char * name, int32 value, int32 min, int32 max);

    Int4Par(ParameterOwner * owner, const char * name, int32_4 values);
    Int4Par(ParameterOwner * owner, const char * name, int32_4 values, int32 min, int32 max);


    void flag_parameters_changed() override
    {
        ParameterOwner::flag_parameters_changed();
        BaseParameter::flag_changed();
    }

    int32 x() const;
    int32 y() const;
    int32 z() const;
    int32 w() const;

    void set_x(int32 new_x);
    void set_y(int32 new_y);
    void set_z(int32 new_z);
    void set_w(int32 new_w);

    int32 min() const;
    int32 max() const;

    void set_min(int32 new_min);
    void set_max(int32 new_max);

    int32_4 get() const;

    void set(int32_4 new_values);
    void set(int32 x, int32 y, int32 z, int32 w);

    operator int32_4() const;
    void operator=(int32_4 new_values);

    int32_t int_at(unsigned index) const override;
    double double_at(unsigned index) const override;

protected:

    void import_flagged_changed() override;

private:

    IntPar x_value;
    IntPar y_value;
    IntPar z_value;
    IntPar w_value;


};


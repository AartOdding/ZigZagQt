#pragma once

#include <array>
#include <cstdint>

#include "baseparameter.h"
#include "utility/bounded_value.h"



using int32 = int32_t;
using int32_2 = std::array<int32, 2>;
using int32_3 = std::array<int32, 3>;
using int32_4 = std::array<int32, 4>;



class IntPar : public ArithmeticParameter
{
public:

    IntPar(ParameterOwner * owner, const char * name, int32 value = 0);
    IntPar(ParameterOwner * owner, const char * name, int32 value, int32 min, int32 max);

    int32 get() const;

    void set(int32 new_value);

    int32 min() const;
    int32 max() const;

    void set_min(int32 new_min);
    void set_max(int32 new_max);

    operator int32() const;
    void operator=(int32 new_value);

private:

    bounded_value<int32> value;

};




class Int2Par : public ArithmeticParameter
{
public:

    Int2Par(ParameterOwner * owner, const char * name, int32 value = 0);
    Int2Par(ParameterOwner * owner, const char * name, int32 value, int32 min, int32 max);

    Int2Par(ParameterOwner * owner, const char * name, int32_2 values);
    Int2Par(ParameterOwner * owner, const char * name, int32_2 values, int32 min, int32 max);


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


private:

    bounded_value<int32> x_value;
    bounded_value<int32> y_value;

};




class Int3Par : public ArithmeticParameter
{
public:

    Int3Par(ParameterOwner * owner, const char * name, int32 value = 0);
    Int3Par(ParameterOwner * owner, const char * name, int32 value, int32 min, int32 max);

    Int3Par(ParameterOwner * owner, const char * name, int32_3 values);
    Int3Par(ParameterOwner * owner, const char * name, int32_3 values, int32 min, int32 max);


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


private:

    bounded_value<int32> x_value;
    bounded_value<int32> y_value;
    bounded_value<int32> z_value;

};




class Int4Par : public ArithmeticParameter
{
public:

    Int4Par(ParameterOwner * owner, const char * name, int32 value = 0);
    Int4Par(ParameterOwner * owner, const char * name, int32 value, int32 min, int32 max);

    Int4Par(ParameterOwner * owner, const char * name, int32_4 values);
    Int4Par(ParameterOwner * owner, const char * name, int32_4 values, int32 min, int32 max);


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


private:

    bounded_value<int32> x_value;
    bounded_value<int32> y_value;
    bounded_value<int32> z_value;
    bounded_value<int32> w_value;


};



/*
namespace parameter
{


    template <typename COMPONENT_TYPE, int NUM_COMPONENTS, typename INTERFACE_TYPE, ParameterType PARAMETER_TYPE>
    class ArithmeticParameter : public BaseParameter
    {

    public:

        constexpr static int num_components = NUM_COMPONENTS;
        static_assert(NUM_COMPONENTS >= 1 && NUM_COMPONENTS <= 4, "Invalid number of components!");
        static_assert(std::is_arithmetic<COMPONENT_TYPE>::value, "Only fundamental arithmetic types can be components!");
        static_assert(std::is_default_constructible<INTERFACE_TYPE>::value, "INTERFACE_TYPE must be default-constructible!");*/
        /*
         * INTERFACE_TYPE must also store the components contiguously in memory, and as the first thing in the class.
         * so that the address of component 0 is the same as the address of the whole object. Unfortunately this is
         * hard to check with static asserts.
         */

/*
        ArithmeticParameter(ParameterOwner * owner, const char * name, INTERFACE_TYPE values = INTERFACE_TYPE())
            : BaseParameter (owner, PARAMETER_TYPE, name)
        {
            for (int i = 0; i < NUM_COMPONENTS; ++i)
            {
                components[i] = bounded_value<COMPONENT_TYPE>(((COMPONENT_TYPE*)&values)[i]);
            }
            Q_ASSERT(num_components == components.size());
        }


        ArithmeticParameter(ParameterOwner * owner, const char * name, INTERFACE_TYPE values, INTERFACE_TYPE min, INTERFACE_TYPE max)
            : BaseParameter (owner, PARAMETER_TYPE, name)
        {
            for (int i = 0; i < NUM_COMPONENTS; ++i)
            {
                components[i] = bounded_value<COMPONENT_TYPE>(((COMPONENT_TYPE*)&values)[i], ((COMPONENT_TYPE*)&min)[i], ((COMPONENT_TYPE*)&max)[i]);
            }
            Q_ASSERT(num_components == components.size());
            std::cout << "num components " << num_components << "\n";
        }

*/
        /* Getters of one component at a time. */
/*
        template<int INDEX>
        COMPONENT_TYPE get() const
        {
            static_assert(INDEX >= 0 && INDEX < NUM_COMPONENTS, "Index out of bounds!");
            return components[INDEX].get();
        }


        template<int INDEX>
        COMPONENT_TYPE get_min() const
        {
            static_assert(INDEX >= 0 && INDEX < NUM_COMPONENTS, "Index out of bounds!");
            return components[INDEX].get_min();
        }


        template<int INDEX>
        COMPONENT_TYPE get_max() const
        {
            static_assert(INDEX >= 0 && INDEX < NUM_COMPONENTS, "Index out of bounds!");
            return components[INDEX].get_max();
        }


        COMPONENT_TYPE x() const { return get<0>(); }
        COMPONENT_TYPE y() const { return get<1>(); }
        COMPONENT_TYPE z() const { return get<2>(); }
        COMPONENT_TYPE w() const { return get<3>(); }

        COMPONENT_TYPE r() const { return get<0>(); }
        COMPONENT_TYPE g() const { return get<1>(); }
        COMPONENT_TYPE b() const { return get<2>(); }
        COMPONENT_TYPE a() const { return get<3>(); }

*/
        /* Setters of one component at a time. */
/*
        template<int INDEX>
        void set(const COMPONENT_TYPE& new_value)
        {
            std::cout << "set " << name << " to value: " << new_value << "\n";
            static_assert(INDEX >= 0 && INDEX < NUM_COMPONENTS, "Index out of bounds!");
            bool changed = false;
            components[INDEX].set(new_value, changed);
            if (changed)
            {
                flag_changed();
            }
        }


        template<int INDEX>
        void set_min(const COMPONENT_TYPE& new_min)
        {
            static_assert(INDEX >= 0 && INDEX < NUM_COMPONENTS, "Index out of bounds!");
            bool changed = false;
            components[INDEX].set_min(new_min, changed);
            if (changed)
            {
                flag_changed();
            }
        }


        template<int INDEX>
        void set_max(const COMPONENT_TYPE& new_max)
        {
            static_assert(INDEX >= 0 && INDEX < NUM_COMPONENTS, "Index out of bounds!");
            bool changed = false;
            components[INDEX].set_max(new_max, changed);
            if (changed)
            {
                flag_changed();
            }
        }


        void set_x(const COMPONENT_TYPE& val) const { set<0>(val); }
        void set_y(const COMPONENT_TYPE& val) const { set<1>(val); }
        void set_z(const COMPONENT_TYPE& val) const { set<2>(val); }
        void set_w(const COMPONENT_TYPE& val) const { set<3>(val); }

        void set_r(const COMPONENT_TYPE& val) const { set<0>(val); }
        void set_g(const COMPONENT_TYPE& val) const { set<1>(val); }
        void set_b(const COMPONENT_TYPE& val) const { set<2>(val); }
        void set_a(const COMPONENT_TYPE& val) const { set<3>(val); }

*/
        /* Getters and setters for the full composite type. */
/*
        INTERFACE_TYPE get() const
        {
            if constexpr(std::is_same<COMPONENT_TYPE, INTERFACE_TYPE>::value)
            {
                return components[0].get();
            }
            else
            {
                INTERFACE_TYPE result;
                for (int i = 0; i < NUM_COMPONENTS; ++i)
                {
                    result[i] = components[i].get();
                }
                return result;
            }
        }


        void set(INTERFACE_TYPE new_values)
        {
            //std::cout << "set " << name << " to value: " << new_values << "\n";
            bool any_changed = false;
            for (int i = 0; i < NUM_COMPONENTS; ++i)
            {
                bool changed = false;
                components[i].set(((COMPONENT_TYPE*)&new_values)[i], changed);
                any_changed = any_changed || changed;
            }
            if (any_changed)
            {
                flag_changed();
            }
        }


        void operator=(INTERFACE_TYPE new_values)
        {
            set(new_values);
        }


        operator INTERFACE_TYPE() const
        {
            return get();
        }

*/
/*      INTERFACE_TYPE get_min() const;
        INTERFACE_TYPE get_max() const;
        void set_min(INTERFACE_TYPE min);
        void set_max(INTERFACE_TYPE max);
        void set_limits(INTERFACE_TYPE min, INTERFACE_TYPE max);   */
/*

    private:

        std::array<bounded_value<COMPONENT_TYPE>, NUM_COMPONENTS> components;


    };


    using Int  = ArithmeticParameter<int32_t, 1, int32_t, ParameterType::Int>;
    using Int2 = ArithmeticParameter<int32_t, 2, std::array<int32_t, 2>, ParameterType::Int2>;
    using Int3 = ArithmeticParameter<int32_t, 3, std::array<int32_t, 3>, ParameterType::Int3>;
    using Int4 = ArithmeticParameter<int32_t, 4, std::array<int32_t, 4>, ParameterType::Int4>;

    using Float  = ArithmeticParameter<double, 1, double, ParameterType::Float>;
    using Float2 = ArithmeticParameter<double, 2, std::array<double, 2>, ParameterType::Float2>;
    using Float3 = ArithmeticParameter<double, 3, std::array<double, 3>, ParameterType::Float3>;
    using Float4 = ArithmeticParameter<double, 4, std::array<double, 4>, ParameterType::Float4>;
}
*/

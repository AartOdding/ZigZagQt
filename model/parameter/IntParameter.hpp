#pragma once

#include <array>
#include <tuple>
#include <optional>
#include <cstdint>

#include "BaseParameter.hpp"
#include "Int64Component.hpp"



using int64 = int64_t;
using int64_2 = std::array<int64, 2>;
using int64_3 = std::array<int64, 3>;
using int64_4 = std::array<int64, 4>;



template<int NUM_COMPONENTS>
class IntParameter : public BaseParameter
{
public:

    static_assert(NUM_COMPONENTS >= 1 && NUM_COMPONENTS <= 4, "Invalid number of components!");

    using interface_types = std::tuple<int64, int64_2, int64_3, int64_4>;
    using interface_type = typename std::tuple_element<NUM_COMPONENTS - 1, interface_types>::type;


    IntParameter(BaseZigZagObject * parent, const char * name, interface_type value = interface_type())
        : BaseParameter(parameter_types[NUM_COMPONENTS - 1], parent, name)
    {
        if constexpr(NUM_COMPONENTS == 1)
        {
            components[0].emplace(this, value);
        }
        else
        {
            for (int i = 0; i < NUM_COMPONENTS; ++i)
            {
                components[i].emplace(this, value[i]);
            }
        }
    }


    IntParameter(BaseZigZagObject * parent, const char * name, interface_type value, int64 min, int64 max)
        : BaseParameter(parameter_types[NUM_COMPONENTS - 1], parent, name)
    {
        if constexpr(NUM_COMPONENTS == 1)
        {
            components[0].emplace(this, value, min, max);
        }
        else
        {
            for (int i = 0; i < NUM_COMPONENTS; ++i)
            {
                components[i].emplace(this, value[i], min, max);
            }
        }
    }


    interface_type get() const
    {
        if constexpr(NUM_COMPONENTS == 1)
        {
            return components[0]->getValue();
        }
        else
        {
            interface_type return_value;
            for (int i = 0; i < NUM_COMPONENTS; ++i)
            {
                return_value[i] = components[i]->getValue();
            }
            return return_value;
        }
    }


    int64 get(int index) const
    {
        if (index >= 0 && index < NUM_COMPONENTS)
        {
            return components[index]->getValue();
        }
        return 0;
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 1), int64> x() const
    {
        return components[0]->getValue();
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 1), int64> y() const
    {
        return components[1]->getValue();
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 2), int64> z() const
    {
        return components[2]->getValue();
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 3), int64> w() const
    {
        return components[3]->getValue();
    }


    void set(int64 value)
    {
        for (auto& component : components)
        {
            component->setValue(value);
        }
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM == 2), void> set(int64 x, int64 y)
    {
        components[0]->setValue(x);
        components[1]->setValue(y);
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM == 3), void> set(int64 x, int64 y, int64 z)
    {
        components[0]->setValue(x);
        components[1]->setValue(y);
        components[2]->setValue(z);
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM == 4), void> set(int64 x, int64 y, int64 z, int64 w)
    {
        components[0]->setValue(x);
        components[1]->setValue(y);
        components[2]->setValue(z);
        components[3]->setValue(w);
    }


private:

    static constexpr std::array parameter_types{ ParameterType::Int, ParameterType::Int2, ParameterType::Int3, ParameterType::Int4 };

    std::array<std::optional<Int64Component>, NUM_COMPONENTS> components;


};


using IntPar  = IntParameter<1>;
using Int2Par = IntParameter<2>;
using Int3Par = IntParameter<3>;
using Int4Par = IntParameter<4>;

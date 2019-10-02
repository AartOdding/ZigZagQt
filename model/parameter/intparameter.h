#pragma once

#include <array>
#include <tuple>
#include <optional>
#include <cstdint>

#include "baseparameter.h"
#include "intparametercomponent.h"



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


    IntParameter(ParameterOwner * owner, const char * name, interface_type value = interface_type())
        : BaseParameter(owner, parameter_types[NUM_COMPONENTS - 1], name)
    {
        if constexpr(NUM_COMPONENTS == 1)
        {
            components[0].emplace(value, this);
        }
        else
        {
            for (int i = 0; i < NUM_COMPONENTS; ++i)
            {
                components[i].emplace(value[i], this);
            }
        }
    }


    IntParameter(ParameterOwner * owner, const char * name, interface_type value, int64 min, int64 max)
        : BaseParameter(owner, parameter_types[NUM_COMPONENTS - 1], name)
    {
        if constexpr(NUM_COMPONENTS == 1)
        {
            components[0].emplace(value, min, max, this);
        }
        else
        {
            for (int i = 0; i < NUM_COMPONENTS; ++i)
            {
                components[i].emplace(value[i], min, max, this);
            }
        }
    }


    int num_components() const override
    {
        return NUM_COMPONENTS;
    }


    BaseParameterComponent* get_component(int index) override
    {
        if (index >= 0 && index < NUM_COMPONENTS)
        {
            return &(*components[index]);
        }
        return nullptr;
    }


    const BaseParameterComponent* get_component(int index) const override
    {
        if (index >= 0 && index < NUM_COMPONENTS)
        {
            return &(*components[index]);
        }
        return nullptr;
    }


    interface_type get() const
    {
        if constexpr(NUM_COMPONENTS == 1)
        {
            return components[0]->get();
        }
        else
        {
            interface_type return_value;
            for (int i = 0; i < NUM_COMPONENTS; ++i)
            {
                return_value[i] = components[i]->get();
            }
            return return_value;
        }
    }


    int64 get(int index) const
    {
        if (index >= 0 && index < NUM_COMPONENTS)
        {
            return components[index]->get();
        }
        return 0;
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 1), int64> x() const
    {
        return components[0]->get();
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 1), int64> y() const
    {
        return components[1]->get();
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 2), int64> z() const
    {
        return components[2]->get();
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 3), int64> w() const
    {
        return components[3]->get();
    }


    void set(int64 value)
    {
        for (auto& component : components)
        {
            component->set(value);
        }
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM == 2), void> set(int64 x, int64 y)
    {
        components[0]->set(x);
        components[1]->set(y);
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM == 3), void> set(int64 x, int64 y, int64 z)
    {
        components[0]->set(x);
        components[1]->set(y);
        components[2]->set(z);
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM == 4), void> set(int64 x, int64 y, int64 z, int64 w)
    {
        components[0]->set(x);
        components[1]->set(y);
        components[2]->set(z);
        components[3]->set(w);
    }


private:

    static constexpr std::array parameter_types{ ParameterType::Int, ParameterType::Int2, ParameterType::Int3, ParameterType::Int4 };

    std::array<std::optional<IntParameterComponent>, NUM_COMPONENTS> components;


};


using IntPar  = IntParameter<1>;
using Int2Par = IntParameter<2>;
using Int3Par = IntParameter<3>;
using Int4Par = IntParameter<4>;

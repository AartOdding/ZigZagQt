#pragma once

#include <array>
#include <tuple>
#include <optional>

#include "baseparameter.h"
#include "parametercomponentdouble.h"



using double_2 = std::array<double, 2>;
using double_3 = std::array<double, 3>;
using double_4 = std::array<double, 4>;



template<int NUM_COMPONENTS>
class DoubleParameter : public BaseParameter
{
public:

    static_assert(NUM_COMPONENTS >= 1 && NUM_COMPONENTS <= 4, "Invalid number of components!");

    using interface_types = std::tuple<double, double_2, double_3, double_4>;
    using interface_type = typename std::tuple_element<NUM_COMPONENTS - 1, interface_types>::type;


    DoubleParameter(ParameterOwner * owner, const char * name, interface_type value = interface_type())
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


    DoubleParameter(ParameterOwner * owner, const char * name, interface_type value, double min, double max)
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


    ParameterComponent* get_component(int index) override
    {
        if (index >= 0 && index < NUM_COMPONENTS)
        {
            return &(components[index].value());
        }
        else
        {
            return nullptr;
        }
    }


    const ParameterComponent* get_component(int index) const override
    {
        if (index >= 0 && index < NUM_COMPONENTS)
        {
            return &(components[index].value());
        }
        else
        {
            return nullptr;
        }
    }


    interface_type get() const
    {
        if constexpr(NUM_COMPONENTS == 1)
        {
            return components[0].value().get();
        }
        else
        {
            interface_type return_value;
            for (int i = 0; i < NUM_COMPONENTS; ++i)
            {
                return_value[i] = components[i].value().get();
            }
            return return_value;
        }
    }


    double get(int index) const
    {
        if (index >= 0 && index < NUM_COMPONENTS)
        {
            return components[index].value().get();
        }
        return 0.0;
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 1), double> x() const
    {
        return components[0].value().get();
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 1), double> y() const
    {
        return components[1].value().get();
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 2), double> z() const
    {
        return components[2].value().get();
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 3), double> w() const
    {
        return components[3].value().get();
    }


    void set(double value)
    {
        for (auto& component : components)
        {
            component.value().set(value);
        }
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM == 2), void> set(double x, double y)
    {
        components[0].value().set(x);
        components[1].value().set(y);
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM == 3), void> set(double x, double y, double z)
    {
        components[0].value().set(x);
        components[1].value().set(y);
        components[2].value().set(z);
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM == 4), void> set(double x, double y, double z, double w)
    {
        components[0].value().set(x);
        components[1].value().set(y);
        components[2].value().set(z);
        components[3].value().set(w);
    }


private:

    static constexpr std::array parameter_types{ ParameterType::Float, ParameterType::Float2, ParameterType::Float3, ParameterType::Float4 };

    std::array<std::optional<ParameterComponentDouble>, NUM_COMPONENTS> components;


};


using DoublePar = DoubleParameter<1>;
using Double2Par = DoubleParameter<2>;
using Double3Par = DoubleParameter<3>;
using Double4Par = DoubleParameter<4>;

#pragma once

#include <array>
#include <tuple>
#include <optional>

#include "baseparameterold.h"
#include "Float64Component.hpp"



using double_2 = std::array<double, 2>;
using double_3 = std::array<double, 3>;
using double_4 = std::array<double, 4>;



template<int NUM_COMPONENTS>
class FloatParameter : public BaseParameterOld
{
public:

    static_assert(NUM_COMPONENTS >= 1 && NUM_COMPONENTS <= 4, "Invalid number of components!");

    using interface_types = std::tuple<double, double_2, double_3, double_4>;
    using interface_type = typename std::tuple_element<NUM_COMPONENTS - 1, interface_types>::type;


    FloatParameter(BaseParameterOld * parent, const char * name, interface_type value = interface_type())
        : BaseParameterOld(parent, parameter_types[NUM_COMPONENTS - 1], name)
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


    FloatParameter(BaseParameterOld * parent, const char * name, interface_type value, double min, double max)
        : BaseParameterOld(parent, parameter_types[NUM_COMPONENTS - 1], name)
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


    BaseComponent* get_component(int index) override
    {
        if (index >= 0 && index < NUM_COMPONENTS)
        {
            return &(*components[index]);
        }
        else
        {
            return nullptr;
        }
    }


    const BaseComponent* get_component(int index) const override
    {
        if (index >= 0 && index < NUM_COMPONENTS)
        {
            return &(*components[index]);
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
            return components[0]->get_value();
        }
        else
        {
            interface_type return_value;
            for (int i = 0; i < NUM_COMPONENTS; ++i)
            {
                return_value[i] = components[i]->get_value();
            }
            return return_value;
        }
    }


    double get(int index) const
    {
        if (index >= 0 && index < NUM_COMPONENTS)
        {
            return components[index]->get_value();
        }
        return 0.0;
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 1), double> x() const
    {
        return components[0]->get_value();
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 1), double> y() const
    {
        return components[1]->get_value();
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 2), double> z() const
    {
        return components[2]->get_value();
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM > 3), double> w() const
    {
        return components[3]->get_value();
    }


    void set(double value)
    {
        for (auto& component : components)
        {
            component->set(value);
        }
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM == 2), void> set(double x, double y)
    {
        components[0]->set(x);
        components[1]->set(y);
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM == 3), void> set(double x, double y, double z)
    {
        components[0]->set(x);
        components[1]->set(y);
        components[2]->set(z);
    }


    template<int NUM = NUM_COMPONENTS>
    typename std::enable_if_t<(NUM == 4), void> set(double x, double y, double z, double w)
    {
        components[0]->set(x);
        components[1]->set(y);
        components[2]->set(z);
        components[3]->set(w);
    }


private:

    static constexpr std::array parameter_types{ ParameterType::Float, ParameterType::Float2, ParameterType::Float3, ParameterType::Float4 };

    std::array<std::optional<Float64Component>, NUM_COMPONENTS> components;


};


using FloatPar  = FloatParameter<1>;
using Float2Par = FloatParameter<2>;
using Float3Par = FloatParameter<3>;
using Float4Par = FloatParameter<4>;

#pragma once

#include "BaseComponent.hpp"



class FloatParameterComponent : public BaseComponent
{
    Q_OBJECT

public:

    FloatParameterComponent(double value, BaseParameterOld* parameter);
    FloatParameterComponent(double value, double min, double max, BaseParameterOld* parameter);

    bool update() override;

    double get_value() const;
    double get_min() const;
    double get_max() const;

public slots:

    void set_value(double value);
    void set_min(double min);
    void set_max(double max);

    void set(int64_t value) override;
    void set(double value) override;

signals:

    void min_changed(double new_min);
    void max_changed(double new_max);

private:

    double current_value;
    double min_value;
    double max_value;
    double pending_value;
    bool new_value_pending = false;

};

#pragma once

#include "baseparametercomponent.h"



class FloatParameterComponent : public BaseParameterComponent
{
    Q_OBJECT

public:

    FloatParameterComponent(double value, BaseParameter* parameter);
    FloatParameterComponent(double value, double min, double max, BaseParameter* parameter);

    bool process_changes() override;

    double get() const;
    double get_min() const;
    double get_max() const;

public slots:

    void set(double value);
    void set_min(double min);
    void set_max(double max);

    void set_later(int64_t value) override;
    void set_later(double value) override;

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

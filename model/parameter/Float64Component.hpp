#pragma once

#include "BaseComponent.hpp"



class Float64Component : public BaseComponent
{
    Q_OBJECT

public:

    Float64Component(BaseParameter * parameter, double value = 0.0);
    Float64Component(BaseParameter * parameter, double value, double min, double max);

    bool update() override;

    double getValue() const;
    double getMin() const;
    double getMax() const;

public slots:

    // Will return true if the component's value changed.
    bool setValue(double value, bool overwritePendingChanges = true);
    void setMin(double min);
    void setMax(double max);

    void change(int64_t value) override;
    void change(double value) override;

signals:

    void minChanged(double newMin);
    void maxChanged(double newMax);

private:

    double m_value;
    double m_min;
    double m_max;
    double m_pending;
    bool m_newValuePending = false;

};

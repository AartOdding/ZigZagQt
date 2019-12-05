#pragma once

#include "BaseComponent.hpp"



class PulseParameterComponent : public BaseComponent
{
    Q_OBJECT

public:

    PulseParameterComponent(BaseParameterOld* parameter);

    bool run() override;

public slots:

    void change(int64_t value) override;
    void change(double value) override;

private:

    bool received_signal = false;

};

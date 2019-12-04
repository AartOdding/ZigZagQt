#pragma once

#include "BaseComponent.hpp"



class PulseParameterComponent : public BaseComponent
{
    Q_OBJECT

public:

    PulseParameterComponent(BaseParameterOld* parameter);

    bool update() override;

public slots:

    void store(int64_t value) override;
    void store(double value) override;

private:

    bool received_signal = false;

};

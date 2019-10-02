#pragma once

#include "baseparametercomponent.h"



class PulseParameterComponent : public BaseParameterComponent
{
    Q_OBJECT

public:

    PulseParameterComponent(BaseParameter* parameter);

    bool process_changes() override;

public slots:

    void set_later(int64_t value) override;
    void set_later(double value) override;

private:

    bool received_signal = false;

};

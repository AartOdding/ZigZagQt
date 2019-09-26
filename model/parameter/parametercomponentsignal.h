#pragma once

#include "parametercomponent.h"



class ParameterComponentSignal : public ParameterComponent
{
    Q_OBJECT

public:

    ParameterComponentSignal(BaseParameter* parameter);

    bool process_changes() override;

public slots:

    void set_later(int64_t value) override;
    void set_later(double value) override;

private:

    bool received_signal = false;

};

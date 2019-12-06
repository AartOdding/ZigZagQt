#pragma once

#include "BaseComponent.hpp"



class TriggerComponent : public BaseComponent
{
    Q_OBJECT

public:

    TriggerComponent(BaseParameter* parameter);

    bool update() override;

public slots:

    void change() override;
    void change(int64_t value) override;
    void change(double value) override;
    void change(const QString&) override;

private:

    bool m_triggerReceived = false;

};

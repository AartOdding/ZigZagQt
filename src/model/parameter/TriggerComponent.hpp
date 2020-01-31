#pragma once

#include "BaseComponent.hpp"



class TriggerComponent : public BaseComponent
{
    Q_OBJECT

public:

    TriggerComponent(BaseParameter* parameter, const QString& name);

    bool update() override;

    virtual void loadState(const QVariantMap&) override;
    virtual QVariantMap storeState() const override;

public slots:

    void importChange() override;
    void importChange(int64_t value) override;
    void importChange(double value) override;
    void importChange(const QString&) override;

private:

    bool m_triggerReceived = false;

};

#pragma once

#include "BaseComponent.hpp"



class Int64Component : public BaseComponent
{
    Q_OBJECT

public:

    Int64Component(BaseParameter * parameter, int64_t value = 0);
    Int64Component(BaseParameter * parameter, int64_t value, int64_t min, int64_t max);

    bool update() override;

    int64_t getValue() const;
    int64_t getMin() const;
    int64_t getMax() const;

    virtual void loadState(const QVariantMap&) override;
    virtual QVariantMap storeState() const override;

public slots:

    // Will return true if the component's value changed.
    bool setValue(int64_t value, bool overwritePendingChanges = true);
    void setMin(int64_t min);
    void setMax(int64_t max);

    void change(int64_t value) override;
    void change(double value) override;

signals:

    void minChanged(int64_t new_min);
    void maxChanged(int64_t new_max);

private:

    int64_t m_value;
    int64_t m_min;
    int64_t m_max;
    int64_t m_pending;
    bool m_newValuePending = false;

};

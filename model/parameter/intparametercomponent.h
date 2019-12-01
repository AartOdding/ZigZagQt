#pragma once

#include "BaseComponent.hpp"



class IntParameterComponent : public BaseComponent
{
    Q_OBJECT

public:

    IntParameterComponent(int64_t value, BaseParameterOld* parameter);
    IntParameterComponent(int64_t value, int64_t min, int64_t max, BaseParameterOld* parameter);

    bool update() override;

    int64_t get() const;
    int64_t get_min() const;
    int64_t get_max() const;

    void readXml(QXmlStreamReader& xml) override;
    void writeXml(XmlSerializer& xml) override;

public slots:

    void set_value(int64_t value);
    void set_min(int64_t min);
    void set_max(int64_t max);

    void set(int64_t value) override;
    void set(double value) override;

signals:

    void min_changed(int64_t new_min);
    void max_changed(int64_t new_max);

private:

    int64_t current_value;
    int64_t min_value;
    int64_t max_value;
    int64_t pending_value;
    bool new_value_pending = false;

};

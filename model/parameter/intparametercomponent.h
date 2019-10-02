#pragma once

#include "baseparametercomponent.h"



class IntParameterComponent : public BaseParameterComponent
{
    Q_OBJECT

public:

    IntParameterComponent(int64_t value, BaseParameter* parameter);
    IntParameterComponent(int64_t value, int64_t min, int64_t max, BaseParameter* parameter);

    bool process_changes() override;

    int64_t get() const;
    int64_t get_min() const;
    int64_t get_max() const;

    void set_from_xml(QXmlStreamReader& xml) override;
    void write_to_xml(XmlSerializer& xml) override;

public slots:

    void set(int64_t value);
    void set_min(int64_t min);
    void set_max(int64_t max);

    void set_later(int64_t value) override;
    void set_later(double value) override;

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

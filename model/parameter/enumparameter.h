#pragma once

#include <QObject>
#include "baseparameter.h"
#include "intparametercomponent.h"
#include "model/enumdefinition.h"



class EnumPar : public BaseParameter
{
public:

    EnumPar(BaseParameter * parent, const QString& name, const EnumDefinition& definition, int index = 0);
    EnumPar(BaseParameter * parent, const QString& name, const EnumDefinition& definition, const QString& value);

    int get_index() const;
    const QString& get_text() const;

    void set(int index);
    void set(const QString& value);

    void operator=(int index);
    void operator=(const QString& value);

    const EnumDefinition * get_enum() const;

    int num_components() const override;
    BaseParameterComponent* get_component(int index) override;
    const BaseParameterComponent* get_component(int index) const override;


private:

    const EnumDefinition * definition;

    IntParameterComponent index;

};


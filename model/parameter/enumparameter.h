#pragma once

#include <QObject>
#include "baseparameterold.h"
#include "intparametercomponent.h"
#include "model/enumdefinition.h"



class EnumPar : public BaseParameterOld
{
public:

    EnumPar(BaseParameterOld * parent, const QString& name, const EnumDefinition& definition, int index = 0);
    EnumPar(BaseParameterOld * parent, const QString& name, const EnumDefinition& definition, const QString& value);

    int get_index() const;
    const QString& get_text() const;

    void set(int index);
    void set(const QString& value);

    void operator=(int index);
    void operator=(const QString& value);

    const EnumDefinition * get_enum() const;

    int num_components() const override;
    BaseComponent* get_component(int index) override;
    const BaseComponent* get_component(int index) const override;


private:

    const EnumDefinition * definition;

    IntParameterComponent index;

};


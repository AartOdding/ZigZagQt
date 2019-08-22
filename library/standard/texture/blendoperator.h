#pragma once

#include "model/baseoperator.h"
#include "model/datainput.h"
#include "model/enumdefinition.h"
#include "model/parameter/enumparameter.h"

#include "library/standard/texturedata.h"


const inline EnumDefinition BlendMode
{
    "BlendMode",
    {
        "Add",
        "Subtract",
        "Average",
        "Over",
        "Under"
    }
};


class BlendOperator : public BaseOperator
{

public:

    BlendOperator();

    ~BlendOperator() override;


    void run() override;


    static BaseOperator* create();

    static const inline OperatorTypeInfo Type { "Blend Operator", &create };

private:

    DataInput texture_a{ this, TextureData::Type };
    DataInput texture_b{ this, TextureData::Type };

    EnumParameter blend_mode{ this, BlendMode, "Blend Mode", 0 };

    TextureData output_texture{ this };

};

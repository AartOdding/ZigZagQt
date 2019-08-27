#pragma once

#include "model/baseoperator.h"
#include "model/datainput.h"
#include "model/enumdefinition.h"
#include "model/parameter/enum.h"

#include "library/standard/texture/texturedata.h"
#include "library/standard/test/testdata.h"


const inline EnumDefinition BlendMode
{
    "BlendMode",
    {
        "Over",
        "Add",
        "Subtract",
        "Multiply",
        "Divide",
        "Average",
        "Difference",
    }
};


class BlendOperator : public BaseOperator
{

public:

    BlendOperator();

    ~BlendOperator() override;


    void run() override;


    static BaseOperator* create();

    static const inline OperatorTypeInfo Type { "Blend Operator", "Standard/Texture",
        { &TextureData::Type, &TextureData::Type },
        { &TextureData::Type }, true, &create };

private:

    DataInput texture_a{ this, TextureData::Type };
    DataInput texture_b{ this, TextureData::Type };


    //DataInput texture_a{ this, TestData::Type };

    EnumPar blend_mode{ this, BlendMode, "Blend Mode", 0 };

    //TestData test_data{ this };

    TextureData output_texture{ this };

};

#pragma once

#include "model/baseoperator.h"
#include "model/parameter/int.h"

#include "library/standard/texture/texturedata.h"

#include <QOpenGLFunctions_3_2_Core>

class ColorOperator : public BaseOperator,
                      public QOpenGLFunctions_3_2_Core

{

public:

    ColorOperator();

    ~ColorOperator() override;


    void run() override;


    static BaseOperator* create();

    static const inline OperatorTypeInfo Type { "Color Operator", "Standard/Texture",
        {  }, { &TextureData::Type }, true, &create };

private:

    parameter::Int red_value  { this, "Red",   0, 0, 255 };
    parameter::Int green_value{ this, "Green", 0, 0, 255 };
    parameter::Int blue_value { this, "Blue",  0, 0, 255 };
    parameter::Int alpha_value{ this, "Alpha", 255, 0, 255 };
    //parameter::Float4 color { this, "Color", {0, 0, 0, 0}, { -1000, -1000, -1000, -1000 }, {1000, 1000, 1000, 1000} };

    //parameter::Int3 test{ this, "tets", {5, 6, 2} };
   // parameter::Float4 test2{ this, "tets", {5, 6, 2, 4}, {5, 6, 2, 4}, {5, 6, 2, 4}};
    //parameter::Float test3{ this, "tets"};

    TextureData output_texture{ this };

};

#pragma once

#include "model/baseoperator.h"
#include "model/parameter/IntParameter.hpp"

#include "library/standard/texture/texturedata.h"
#include "library/standard/texture/textureview.h"


#include <QOpenGLFunctions_3_2_Core>

class ColorOperator : public BaseOperator,
                      public QOpenGLFunctions_3_2_Core

{

public:

    ColorOperator();

    ~ColorOperator() override;


    void run() override;


    static BaseOperator* create();

    static const OperatorDescription Type;

private:

    //ParameterRow row  { this, "Color RGBA" };
    IntPar red_value  { this, "Red", 0, 0, 255 };
    IntPar green_value{ this, "Green", 0, 0, 255 };
    IntPar blue_value { this, "Blue",  0, 0, 255 };
    IntPar alpha_value{ this, "Alpha", 255, 0, 255 };

    //parameter::Float4 color { this, "Color", {0, 0, 0, 0}, { -1000, -1000, -1000, -1000 }, {1000, 1000, 1000, 1000} };

    //parameter::Int3 test{ this, "tets", {5, 6, 2} };
   // parameter::Float4 test2{ this, "tets", {5, 6, 2, 4}, {5, 6, 2, 4}, {5, 6, 2, 4}};
    //parameter::Float test3{ this, "tets"};

    TextureData output_texture{ this, "Output Texture" };

};

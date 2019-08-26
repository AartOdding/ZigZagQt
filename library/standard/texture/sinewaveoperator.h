#pragma once


#include "model/baseoperator.h"
#include "texturedata.h"



class SineWaveOperator : public BaseOperator
{

public:

    SineWaveOperator();

    void run() override { }

    static BaseOperator * create() { return new SineWaveOperator(); }

    static const inline OperatorTypeInfo Type { "Sine Wave", "Standard/Texture", { },
                                                { &TextureData::Type }, true, &create };


protected:

    TextureData output_texture{ this };

};

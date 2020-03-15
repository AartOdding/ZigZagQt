#include "OpenGLTexturePackage.hpp"

#include "sinewaveoperator.h"
#include "squarewaveoperator.h"
#include "sawtoothwaveoperator.h"
#include "noiseoperator.h"
#include "blendoperator.h"



OperatorPackage OpenGLTexturePackage
{
    "Texture",
    {
        { &SineWaveOperator::description, &SineWaveOperator::create },
        { &SquareWaveOperator::description, &SquareWaveOperator::create },
        { &SawtoothWaveOperator::description, &SawtoothWaveOperator::create },
        { &NoiseOperator::description, &NoiseOperator::create },
        { &BlendOperator::description, &BlendOperator::create }
    }
};

OperatorPackage OpenGLMeshPackage{ "Mesh" };
OperatorPackage OpenGLPointCloudPackage{ "Point cloud" };

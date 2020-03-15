#include "ControlPackage.hpp"

#include "increasingvalueoperator.h"
#include "sinewavecontroloperator.h"
#include "noisewavecontroloperator.h"



OperatorPackage ControlPackage
{
    "Control",
    {
        { &IncreasingValueOperator::description, &IncreasingValueOperator::create },
        { &SineWaveControlOperator::description, &SineWaveControlOperator::create },
        { &NoiseWaveControlOperator::description, &NoiseWaveControlOperator::create }
    }
};


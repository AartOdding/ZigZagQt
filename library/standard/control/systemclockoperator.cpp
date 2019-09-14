#include "systemclockoperator.h"

SystemClockOperator::SystemClockOperator()
    : BaseOperator(Type)
{

}

void SystemClockOperator::run()
{
    frame = frame + 1;

    if (frame > 1000)
    {
        frame = 0;
    }

    seconds = seconds + 0.02;
    if (seconds > 5)
    {
        seconds = 0;
    }
}

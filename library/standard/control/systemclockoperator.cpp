#include "systemclockoperator.h"
#include <ctime>



SystemClockOperator::SystemClockOperator()
    : BaseOperator(Type)
{

}

void SystemClockOperator::run()
{
    frame.set(frame.get() + 1);

    if (frame.get() >= 1000)
    {
        frame.set(0);
    }


/*
    seconds = seconds + 0.02;
    if (seconds > 5)
    {
        seconds = 0;
    }*/
}

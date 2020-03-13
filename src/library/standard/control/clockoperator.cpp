#include "clockoperator.h"
#include <ctime>

#include "application.h"


const OperatorKind ClockOperator::description { "Clock", "Control" };


BaseOperator * ClockOperator::create(BaseZigZagObject* parent)
{
    return new ClockOperator(parent);
}


ClockOperator::ClockOperator(BaseZigZagObject* parent)
    : BaseOperator(parent, description)
{
    frames.getComponents()[0]->setFlag(ParameterFlag::IsEditable, false);
    seconds.getComponents()[0]->setFlag(ParameterFlag::IsEditable, false);
    minutes.getComponents()[0]->setFlag(ParameterFlag::IsEditable, false);
    hours.getComponents()[0]->setFlag(ParameterFlag::IsEditable, false);
    seconds_whole.getComponents()[0]->setFlag(ParameterFlag::IsEditable, false);
    minutes_whole.getComponents()[0]->setFlag(ParameterFlag::IsEditable, false);
    hours_whole.getComponents()[0]->setFlag(ParameterFlag::IsEditable, false);
}


void ClockOperator::run()
{
    frames.set(application::instance()->get_clock()->get_frame_count());
    seconds.set(application::instance()->get_clock()->get_elapsed_seconds());
    minutes.set(application::instance()->get_clock()->get_elapsed_minutes());
    hours.set(application::instance()->get_clock()->get_elapsed_hours());
    seconds_whole.set(application::instance()->get_clock()->get_elapsed_seconds());
    minutes_whole.set(application::instance()->get_clock()->get_elapsed_minutes());
    hours_whole.set(application::instance()->get_clock()->get_elapsed_hours());
}

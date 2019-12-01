#include "clockoperator.h"
#include <ctime>

#include "application.h"


const OperatorDescription ClockOperator::description { "Clock", "Control", &create };


BaseOperator * ClockOperator::create()
{
    return new ClockOperator();
}


ClockOperator::ClockOperator()
    : BaseOperator(description)
{
    frames.get_component(0)->setFlag(BaseComponent::IsEditable, false);
    seconds.get_component(0)->setFlag(BaseComponent::IsEditable, false);
    minutes.get_component(0)->setFlag(BaseComponent::IsEditable, false);
    hours.get_component(0)->setFlag(BaseComponent::IsEditable, false);
    seconds_whole.get_component(0)->setFlag(BaseComponent::IsEditable, false);
    minutes_whole.get_component(0)->setFlag(BaseComponent::IsEditable, false);
    hours_whole.get_component(0)->setFlag(BaseComponent::IsEditable, false);
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

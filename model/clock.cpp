#include "clock.h"


#include <iostream>

Clock::Clock(double target)
    : target_frame_rate(target), target_frame_period(1.0 / target)
{
    wakeup_timer.setTimerType(Qt::PreciseTimer);
    connect(&wakeup_timer, &QTimer::timeout, this, &Clock::on_wakeup);
    wakeup_timer.start(1000.0 / target_frame_rate);
}


double Clock::get_target_framerate() const
{

}


double Clock::get_actual_framerate() const
{

}


uint64_t Clock::get_frame_count() const
{

}


double Clock::get_elapsed_seconds() const
{

}


double Clock::get_elapsed_minutes() const
{

}


double Clock::get_elapsed_hours() const
{

}


void Clock::reset()
{

}


void Clock::set_realtime(bool value)
{

}


void Clock::set_target_framerate(double target)
{
    Q_ASSERT(target > 0);

    if (target != target_frame_rate)
    {
        target_frame_rate = target;
        target_frame_period = 1.0 / target;
        current_frame_count = 0;
    }
}


void Clock::set_framerate_uncontrolled(bool value)
{

}


void Clock::on_wakeup()
{
    ++frame_count;
    emit begin_new_frame();

    if (framerate_uncontrolled)
    {
        // wakeup in 0
    }
    else
    {
        // calculate next wakeup

    }
}

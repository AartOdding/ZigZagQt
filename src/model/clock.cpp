#include "clock.h"


#include <iostream>

Clock::Clock(double target)
    : target_frame_rate(target), target_frame_period(1.0 / target)
{
    time_begin = actual_clock.now();
    wakeup_timer.setTimerType(Qt::PreciseTimer);
    connect(&wakeup_timer, &QTimer::timeout, this, &Clock::on_wakeup);
    wakeup_timer.start(1000.0 / target_frame_rate);
}


double Clock::get_target_framerate() const
{
    return target_frame_rate;
}


double Clock::get_actual_framerate() const
{
    return 0; // TODO: implement later
}


uint64_t Clock::get_frame_count() const
{
    return frame_count;
}


double Clock::get_elapsed_seconds() const
{
    if (realtime)
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(time_now - time_begin).count() * 0.000001;
    }
    else
    {
        return current_frame_count * target_frame_period;
    }
}


double Clock::get_elapsed_minutes() const
{
    return get_elapsed_seconds() / 60.0;
}


double Clock::get_elapsed_hours() const
{
    return get_elapsed_seconds() / 3600.0;
}


void Clock::reset()
{
    current_frame_count = 0;
    time_begin = actual_clock.now();
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
    ++current_frame_count;

    time_now = actual_clock.now();

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

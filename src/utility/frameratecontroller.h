#pragma once

#include <chrono>
#include <thread>
#include <QObject>

#include <iostream> // TEMPORARY

/*
 * FrameRateController: This class does two things:
 * - It measures the frequency at which the end_frame() function is called.
 * - It emits a signal at the target framerate, which can be used to control framerate in
 * an application. When the target framerate is set to 0 new_frame signals will no longer
 * be emitted, and the FramerateController will only act as a measurement for the frequency
 * at which end_frame() is called.
 */
class FramerateController : public QObject
{
    Q_OBJECT

public:


    FramerateController(double target_fps = 0.0/*, bool wait_active = false*/)
        //: is_active_waiting(wait_active)
    {
        auto now = clock.now();
        set_target_framerate(target_fps);
        next_wake_up_time = now + period;
        last_framecount_reset = now;
        num_frames_counted = 0;
    }


    void set_target_framerate(double target)
    {
        if (target > 0)
        {
            target_framerate = target;
            period = std::chrono::microseconds(static_cast<long long>(1000000.0 / target));
        }
        else
        {
            target_framerate = 0.0;
            period = std::chrono::microseconds(0);
        }
    }


    double get_target_framerate() const
    {
        return target_framerate;
    }


    /* Active waiting means that the thread will not ask the operating system to put it
     * to sleep, but that it waits in a while loop. The advantage of this is that timing
     * is much more accurate, the downside is that other threads don't get the chance to,
     * and the cpu core being used will always run at 100% usage.
     *//*
    void set_active_waiting(bool wait_active)
    {
        is_active_waiting = wait_active;
    }


    bool get_active_waiting() const
    {
        return is_active_waiting;
    }*/


    double get_framerate() const
    {
    	return measured_framerate;
    }


    void end_frame()
    {
    	auto now = clock.now();
        ++num_frames_counted;

        // Sleeping part.
        if (target_framerate > 0.0)
        {
            if (now < next_wake_up_time)
            {
                //if (is_active_waiting)
                //{
                    /* // not supported atm!
                    while(clock.now() < next_wake_up_time)
                    {
                        // do nothing
                        //asm (""); // might be solution if this loop gets optimized out
                    }*/
               //}
                //else
                //{
                    auto time_left = next_wake_up_time - now;
                    auto ms_left = time_left.count() / 1'000'000;
                    std::cout << ms_left << "\n";
                    std::this_thread::sleep_until(next_wake_up_time);
                //}
                next_wake_up_time += period;
            }
            else
            {
                // No need to sleep if we already missed the wake up time.
                if (now < next_wake_up_time + period)
                {
                    next_wake_up_time += period;
                }
                else
                {
                    next_wake_up_time = now + period;
                }
            }
        }
        
        // Measurement part.
        if (now > last_framecount_reset + framecount_reset_interval)
        {
            auto elapsed_micro_sec = (now - last_framecount_reset).count() / 1000;
            double elapsed_sec = elapsed_micro_sec / 1'000'000.0;
            double time_per_frame = elapsed_sec / static_cast<double>(num_frames_counted);
            measured_framerate = 1.0 / time_per_frame;

            last_framecount_reset = now;
            num_frames_counted = 0;
        }
    }

signals:

    void new_frame();


private:


    double target_framerate;
    double measured_framerate;
    unsigned long long num_frames_counted;

    std::chrono::microseconds period;
    std::chrono::milliseconds framecount_reset_interval{ 500 };

    std::chrono::steady_clock::time_point  next_wake_up_time;
    std::chrono::steady_clock::time_point  last_framecount_reset;

    std::chrono::steady_clock clock;

    //bool is_active_waiting;


};

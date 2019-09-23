#pragma once

#include <chrono>
#include <QObject>
#include <QTimer>


class Clock : public QObject
{
    Q_OBJECT

public:

    Clock(double target_frame_rate = 60.0);

    double get_target_framerate() const;
    double get_actual_framerate() const;
    uint64_t get_frame_count() const;

    double get_elapsed_seconds() const;
    double get_elapsed_minutes() const;
    double get_elapsed_hours() const;


public slots:

    void reset();

    void set_realtime(bool value);
    void set_target_framerate(double target);
    void set_framerate_uncontrolled(bool value);

signals:

    void begin_new_frame();

private slots:

    void on_wakeup();

private:

    uint64_t frame_count = 0;
    uint64_t current_frame_count = 0;
    double target_frame_rate;
    double target_frame_period;
    QTimer wakeup_timer;
    bool realtime = true;
    bool framerate_uncontrolled = false;

};

#pragma once

#include <chrono>
#include <QObject>



using namespace std::literals;


class FrameRateMonitor
{

public:

    FrameRateMonitor(std::chrono::milliseconds measurementInterval)
        : m_measurementInterval(measurementInterval)
    {
        m_lastMeasurement = m_clock.now();
    }


    void frame()
    {
        auto now = m_clock.now();
        ++m_currentFrameCount;
        ++m_frameCount;

        if (now > m_lastMeasurement + m_measurementInterval && m_currentFrameCount > 0)
        {
            quint64 microSecondsPassed = (now - m_lastMeasurement).count() / 1000;
            double secondsPassed = microSecondsPassed / 1'000'000.0;
            m_framerate = static_cast<double>(m_currentFrameCount) / secondsPassed;

            m_currentFrameCount = 0;
            m_lastMeasurement = now;
        }
    }


    void resetFrameCount()
    {
        m_frameCount = 0;
    }


    unsigned long long getFrameCount() const
    {
        return m_frameCount;
    }


    double getFrameRate() const
    {
        return m_framerate;
    }



private:

    double m_framerate = 0.0;
    quint64 m_currentFrameCount = 0;
    quint64 m_frameCount = 0;

    std::chrono::milliseconds m_measurementInterval;
    std::chrono::steady_clock::time_point m_lastMeasurement;

    std::chrono::steady_clock m_clock;

};

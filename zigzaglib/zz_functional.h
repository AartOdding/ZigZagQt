#pragma once

#include <functional>



namespace zz
{

    enum class Moment
    {
        ProgramStartup,
        ProgramShutdown,
        OpenGLStartup,
        OpenGLShutdown
    };

    struct CallAt
    {
        CallAt(Moment moment, std::function<void()> function);
    };

    void call_moment(Moment moment);

}

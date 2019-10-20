#include "zz_functional.h"

#include <vector>
#include <unordered_map>



using FunctionMap = std::unordered_map<zz::Moment, std::vector<std::function<void()>>>;

static FunctionMap& get_function_map()
{
    static FunctionMap functions;
    return functions;
}


namespace zz
{

    CallAt::CallAt(Moment moment, std::function<void()> function)
    {
        get_function_map()[moment].push_back(function);
    }


    void call_moment(Moment moment)
    {
        auto& vec = get_function_map()[moment];
        for (auto f : vec)
        {
            f();
        }
    }

}

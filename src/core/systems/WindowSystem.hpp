#pragma once

#include <model/BaseSystem.hpp>


class WindowSystem : public BaseSystem
{
public:

    WindowSystem();

    virtual bool canBeLoaded() override;

protected:

    virtual void loadSystem() override;

    virtual void unloadSystem() override;

private:


};


extern WindowSystem windowSystem;

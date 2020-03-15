#pragma once

#include <model/BaseSystem.hpp>


class NetworkSystem : public BaseSystem
{
public:

    NetworkSystem();

    virtual bool canBeLoaded() override;


protected:

    virtual void loadSystem() override;

    virtual void unloadSystem() override;

};


extern NetworkSystem networkSystem;

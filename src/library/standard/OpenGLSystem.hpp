#pragma once

#include <model/BaseSystem.hpp>


class OpenGLSystem : public BaseSystem
{
public:

    OpenGLSystem();

    virtual bool canBeLoaded() override;

protected:

    virtual void loadSystem() override;

    virtual void unloadSystem() override;

};


extern OpenGLSystem openGLSystem;

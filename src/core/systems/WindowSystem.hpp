#pragma once

#include <model/BaseSystem.hpp>

#include <memory>
#include <QQuickView>


class WindowSystem : public BaseSystem
{
public:

    WindowSystem();

    virtual bool canBeLoaded() override;

protected:

    virtual void loadSystem() override;

    virtual void unloadSystem() override;

private:

    std::unique_ptr<QQuickView> m_window;

};


extern WindowSystem windowSystem;

#pragma once

#include <QObject>
#include <QThread>
#include <QOffscreenSurface>

#include "renderer.h"
#include "programmodel.h"

// TODO: remove
#include <iostream>

class ProgramModel;

/*
 * This class is necessary because QT objects always live in one thread.
 * This class can be seen as the bridge between the main GUI thread and
 * the render thread.
 * This object lives in the main GUI thread, while the renderer object i
 * inside will live in their own thread (member variable render_thread)
 */

class RenderThread : public QObject
{
    Q_OBJECT

public:

    RenderThread()
    {
        render_surface.setFormat(QSurfaceFormat::defaultFormat());
        render_surface.create();
    }

    void start(ProgramModel& model_to_render)
    {
        renderer = new Renderer(model_to_render, render_surface);
        renderer->moveToThread(&render_thread);

        connect(&render_thread, &QThread::started, renderer, &Renderer::setup);

        render_thread.start();
    }


    void stop()
    {
        renderer->deleteLater();
        render_thread.quit();
    }


    ~RenderThread()
    {
        render_thread.wait();
        // delete surface
    }


public slots:


signals:

private:

    QThread render_thread;

    // Defined here because all surfaces must belong to the main GUI thread
    QOffscreenSurface render_surface;

    Renderer* renderer;


};

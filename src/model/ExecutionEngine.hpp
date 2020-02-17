#pragma once

#include <memory>

#include <QObject>
#include <QTimer>
#include <QGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "utility/FrameRateMonitor.hpp"


class Deserializer;
class Serializer;
class QSemaphore;
class OperatorNetwork;
class ExecutionEngineWindow;


class ExecutionEngine : public QObject,
                        public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:

    // Will take ownership of the OperatorNetwork.
    ExecutionEngine(OperatorNetwork* network, QOpenGLWidget* window);

    ~ExecutionEngine();

public slots:

    // Call indirectly!
    // Should be connected to the "started()" signal of QThread, to start scheduling
    // execution passes through the network.
    void startExecution();

    // Call indirectly!
    void pauseExecution();


    /*
     * Can be used to block the event loop. Only meant to be used from another thread.
     * Will acquire the semaphore, which will cause the event loop to be
     * blocked when the semaphore is released this function will return.
     * If this function is called in the same thread. The best way to call is using
     * a BlockingQueuedConnection.
     */
    //void blockEventLoop(QSemaphore* semaphore);

private slots:

    void executeFrame();

private:

    QTimer m_timer;
    OperatorNetwork* m_network;
    QOpenGLWidget* m_glWindow;
    FrameRateMonitor m_frameRateMonitor;

    QOpenGLShaderProgram shader;
    GLuint vao;
    GLuint vbo;

};

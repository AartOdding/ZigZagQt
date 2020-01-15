#pragma once

#include <QObject>
#include <QTimer>


class GLFWwindow;

class ExecutionEngine : public QObject
{
    Q_OBJECT

public:

    ExecutionEngine();

public slots:

    void startExecution();

    void pauseExecution();

private slots:

    void executeFrame();

private:

    QTimer m_timer;
    GLFWwindow* m_window = nullptr;

};

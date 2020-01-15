#include "ExecutionEngine.hpp"

#include <QThread>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


static void error_callback(int error, const char* description)
{
    std::cerr << "ERROR " << error << ":\n" << description << std::endl;

}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    std::cout << "key: " << key << std::endl;
}


ExecutionEngine::ExecutionEngine()
{
    connect(&m_timer, &QTimer::timeout, this, &ExecutionEngine::executeFrame);
    m_timer.start(0);
}

void ExecutionEngine::startExecution()
{
    std::cout << "START: " << thread() << std::endl;

    glfwSetErrorCallback(error_callback);

    if (glfwInit())
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        m_window = glfwCreateWindow(640, 480, "ZigZag says hello!", nullptr, nullptr);

        if (m_window)
        {
            glfwSetKeyCallback(m_window, key_callback);

            glfwMakeContextCurrent(m_window);
            gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
            glfwSwapInterval(1);
            glClearColor(0, 0, 0, 1);
        }
    }
}

void ExecutionEngine::pauseExecution()
{

}


void ExecutionEngine::executeFrame()
{
    if (m_window)
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_window);
    }

    std::cout << "EXEC: " << thread() << std::endl;
}

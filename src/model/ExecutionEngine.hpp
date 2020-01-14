#pragma once

#include <QObject>


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

};

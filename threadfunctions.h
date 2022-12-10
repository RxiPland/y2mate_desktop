#ifndef THREADFUNCTIONS_H
#define THREADFUNCTIONS_H

#include <QThread>
#include <windows.h>

class ThreadFunctions : public QThread
{
public:
    ThreadFunctions();
    void run();

    int operace = 0;  // 1=sleep; 2=shell;
    int sleep_time = 1;  // sleep time in seconds
    SHELLEXECUTEINFO ShExecInfo = {0};  // shell parameters
};

#endif // THREADFUNCTIONS_H

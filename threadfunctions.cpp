#include "threadfunctions.h"
#include <QDebug>

ThreadFunctions::ThreadFunctions()
{

}

void ThreadFunctions::run()
{
    if(operace == 1){
        // "sleep" in thread
        QThread::sleep(sleep_time);

    } else if (operace == 2){
        // "shell execute" in thread

        ShellExecuteEx(&ShExecInfo);
        WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

        CloseHandle(ShExecInfo.hProcess);
    }
}

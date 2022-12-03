#include "sleepthread.h"

long sleep_time = 1;

SleepThread::SleepThread()
{

}

void SleepThread::run(){

    QThread::sleep(sleep_time);
}

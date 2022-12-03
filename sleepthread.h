#ifndef SLEEPTHREAD_H
#define SLEEPTHREAD_H

#include <QThread>


class SleepThread : public QThread
{
public:
    SleepThread();
    void run();
    long sleep_time;
};

#endif // SLEEPTHREAD_H

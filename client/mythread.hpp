// mythread.h

#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QString>
#include "myudp.hpp"

class MyThread : public QThread
{
public:
    // constructor
    // set name using initializer
    explicit MyThread(MyUDP &client);

    // overriding the QThread's run() method
    void run();
private:
    MyUDP &client;
};

#endif // MYTHREAD_H


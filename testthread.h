#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>
class TestThread:public QThread
{
public:
    TestThread();
    bool keyTest(const int &deviceID);
    void ledTest(const int &deviceID);
    void beepTest(const int &deviceID);
    void motorTest(const int &deviceID);
    bool writeTest(const int &deviceID);
    void audioTest();
private:
    QString testInfo;
    void run();
};

#endif // TESTTHREAD_H

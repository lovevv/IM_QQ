#ifndef THREAD_H
#define THREAD_H
#include <QThread>
class Thread:public QThread
{
    Q_OBJECT
public:
    Thread();
    ~Thread();
    void run();
private:

};

#endif // THREAD_H

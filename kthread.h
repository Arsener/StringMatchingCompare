#ifndef KTHREAD_H
#define KTHREAD_H

#include <QThread>
#include <QString>
#include <chrono>

using namespace std;
using namespace chrono;

class KThread : public QThread
{
    Q_OBJECT

public:
    KThread();
    ~KThread();

    void setAttr(QString p, QString t);

signals:
    void returnPreTime(double);
    void returnMatchTime(double);
    void returnTotalTime(double);
    void returnProgress(int);
    void returnResults(QString);

protected:
    void run();

private:
    QString t, p;
    int pre[1000005];
    void computePrefixFunction(int m);
};

#endif // KTHREAD_H


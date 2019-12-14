#ifndef BFTHREAD_H
#define BFTHREAD_H

#include <QThread>
#include <QString>
#include <chrono>

using namespace std;
using namespace chrono;

class BFThread : public QThread
{
    Q_OBJECT

public:
    BFThread();
    ~BFThread();

    void setAttr(QString p, QString t);

signals:
    void returnPreTime(double);
    void returnMatchTime(double);
    void returnTotalTime(double);
    void returnResults(QString);

protected:
    void run();

private:
    QString t, p;
};

#endif // BFTHREAD_H

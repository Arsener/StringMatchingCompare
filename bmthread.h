#ifndef BMTHREAD_H
#define BMTHREAD_H

#include <QThread>
#include <QString>
#include <chrono>

using namespace std;
using namespace chrono;

class BMThread : public QThread
{
    Q_OBJECT

public:
    BMThread();
    ~BMThread();

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
    int bmBc[150];
    int Osuff[2000005];
    int bmGs[2000005];
    void computeBMBC(int m);
    void computeBMGS(int m);
    void computeOsuff(int m);
};

#endif // BMTHREAD_H

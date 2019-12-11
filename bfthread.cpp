#include "bfthread.h"

BFThread::BFThread()
{

}

BFThread::~BFThread()
{

}

void BFThread::setAttr(QString p, QString t)
{
    this->p = p;
    this->t = t;
}

void BFThread::run()
{
    int n = t.length();
    int m = p.length();
    double preTime = 0.0, matchTime = 0.0;

    emit returnPreTime(preTime);

    auto start = system_clock::now();
    QString result = "";
    for (int s = 0; s <= n - m; s++){
        emit returnProgress(s);
        bool flag = true;
        for (int i = 0; i < m; i++){
            if (p[i] != t[s + i]){
                flag = false;
                break;
            }
        }

        if (flag){
            if (result != "")
                result += ",";
            result += QString::number(s);
        }
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    matchTime = double(duration.count()) * microseconds::period::num / microseconds::period::den;
    emit returnMatchTime(matchTime);
    emit returnTotalTime(preTime + matchTime);
    emit returnResults(result);
}

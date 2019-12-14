#include "bmthread.h"

BMThread::BMThread()
{

}

BMThread::~BMThread()
{

}

void BMThread::setAttr(QString p, QString t)
{
    this->p = p;
    this->t = t;
}

void BMThread::computeBMBC(int m)
{
    for (int i = 0; i < 150; i++){
        bmBc[i] = m;
    }
    for (int i = 0; i < p.length() - 1; i++){
        bmBc[int(QChar(p[i]).toLatin1())] = m - i - 1;
    }
}

void BMThread::computeBMGS(int m)
{
    computeOsuff(m);
    for (int i = 0; i < m; i++){
        bmGs[i] = m;
    }

    int j = 0;
    for (int i = m - 2; i >= 0; i--){
        if (Osuff[i] == i + 1){
            while(j < m - Osuff[i]){
                if (bmGs[j] == m)
                    bmGs[j] = m - Osuff[i];
                j++;
            }
        }
    }

    for (int i = 0; i < m - 1; i++){
        bmGs[m - Osuff[i] - 1] = m - i - 1;
    }
}

void BMThread::computeOsuff(int m)
{
    Osuff[m - 1] = m;
    for (int i = m - 2; i >= 0; i--){
        if(p[i] == p[m - 1]){
            int k = 1;
            while(i - k >= 0 && p[i - k] == p[m - 1 - k]){
                k++;
            }
            Osuff[i] = k;
        }
        else{
            Osuff[i] = 0;
        }
    }
}

void BMThread::run()
{
    int n = t.length();
    int m = p.length();
    double preTime = 0.0, matchTime = 0.0;

    auto start = system_clock::now();
    computeBMBC(m);
    computeBMGS(m);
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    preTime = double(duration.count()) * microseconds::period::num / microseconds::period::den;
    emit returnPreTime(preTime);

    start = system_clock::now();
    QString result = "";

    int s = 0;
    while (s <= n - m){
        int i = m - 1;
        while(p[i] == t[s + i]){
            if (i == 0){
                if (result != "")
                    result += ",";
                result += QString::number(s);
                break;
            }
            else{
                i--;
            }
        }
        int move = bmBc[int(QChar(t[s + i]).toLatin1())] - m + i + 1;

        if (move < bmGs[i]){
            move = bmGs[i];
        }
        s += move;
    }

    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);

    matchTime = double(duration.count()) * microseconds::period::num / microseconds::period::den;
    emit returnMatchTime(matchTime);
    emit returnTotalTime(preTime + matchTime);
    emit returnResults(result);
}


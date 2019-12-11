#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "bfthread.h"
#include "kthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void startMatching();
    void setProgressBar(int);
    void setPreLabel(double);
    void setMatchLabel(double);
    void setTotalLabel(double);
    void setResults(QString);


private:
    Ui::MainWindow *ui;
    QString p, t;
    bool bfMatching = false, kmpMathcing = false, bmMathcing = false, matching = false;

    BFThread *bf;
    KThread *kmp;

    void resetProgressBar(int n, int m);
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);

    bf = new BFThread();
    kmp = new KThread();

    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(startMatching()));

    connect(bf, SIGNAL(returnPreTime(double)), this, SLOT(setPreLabel(double)));
    connect(bf, SIGNAL(returnMatchTime(double)), this, SLOT(setMatchLabel(double)));
    connect(bf, SIGNAL(returnTotalTime(double)), this, SLOT(setTotalLabel(double)));
    connect(bf, SIGNAL(returnResults(QString)), this, SLOT(setResults(QString)));
    connect(bf, SIGNAL(returnProgress(int)), this, SLOT(setProgressBar(int)));

    connect(kmp, SIGNAL(returnPreTime(double)), this, SLOT(setPreLabel(double)));
    connect(kmp, SIGNAL(returnMatchTime(double)), this, SLOT(setMatchLabel(double)));
    connect(kmp, SIGNAL(returnTotalTime(double)), this, SLOT(setTotalLabel(double)));
    connect(kmp, SIGNAL(returnResults(QString)), this, SLOT(setResults(QString)));
    connect(kmp, SIGNAL(returnProgress(int)), this, SLOT(setProgressBar(int)));
}

/*
ababababddababdababababddababababababddabababaddabadddbabaababbabaababababddababddababababbbabaababababddababababddababc
ababababdd
0 15 29 66 95 105 120
*/

MainWindow::~MainWindow()
{
    delete bf;
    delete kmp;
    delete ui;
}

void MainWindow::startMatching()
{
    if (matching){
        QMessageBox::warning(this, "Error!", "Matching!");
        return;
    }

    p = ui->pLineEdit->text();
    t = ui->tLineEdit->text();
    int n = t.length();
    int m = p.length();
    ui->tLengthLabel->setText(QString::number(n));
    ui->pLengthLabel->setText(QString::number(m));
    resetProgressBar(n, m);
    bfMatching = true;
    matching = true;
    ui->processLabel->setText("BF算法预处理");
    bf->setAttr(p, t);
    bf->start();
}

void MainWindow::setProgressBar(int p)
{
    ui->progressBar->setValue(p);
}

void MainWindow::resetProgressBar(int n, int m)
{

    ui->progressBar->setRange(0, n - m);
    ui->progressBar->setValue(0);
}

void MainWindow::setPreLabel(double time)
{
    if (bfMatching){
        ui->bfPreLabel->setText(QString::number(time) + "s");
        ui->processLabel->setText("BF算法匹配");
        resetProgressBar(t.length(), p.length());
    }
    else if(kmpMathcing){
        ui->kmpPreLabel->setText(QString::number(time) + "s");
        ui->processLabel->setText("KMP算法匹配");
        resetProgressBar(t.length(), 0);
    }
}

void MainWindow::setMatchLabel(double time)
{
    if (bfMatching){
        ui->bfMatchLabel->setText(QString::number(time) + "s");
    }
    else if(kmpMathcing){
        ui->kmpMatchLabel->setText(QString::number(time) + "s");
    }
}


void MainWindow::setTotalLabel(double time)
{
    if (bfMatching){
        ui->bfTotalLabel->setText(QString::number(time) + "s");
    }
    else if(kmpMathcing){
        ui->kmpTotalLabel->setText(QString::number(time) + "s");
    }
}

void MainWindow::setResults(QString result)
{
    if (bfMatching){
        ui->bfResultLabel->setText(result);
        bfMatching = false;
        kmpMathcing = true;
        resetProgressBar(p.length(), 0);
        ui->processLabel->setText(" KMP算法预处理");
        kmp->setAttr(p, t);
        kmp->start();
    }
    else if(kmpMathcing){
        ui->kmpResultLabel->setText(result);
        kmpMathcing = false;
        bmMathcing = true;
        matching = false;
//        resetProgressBar(p.length(), 0);
        ui->processLabel->setText("BM算法预处理");
//        kmp->setAttr(p, t);
//        kmp->start();
    }
//    else if(bmMathcing){

//    }
}



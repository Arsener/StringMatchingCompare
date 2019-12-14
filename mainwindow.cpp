#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bf = new BFThread();
    kmp = new KThread();
    bm = new BMThread();

    connect(ui->tSelectButton, SIGNAL(clicked(bool)), this, SLOT(selectTextFile()));
    connect(ui->pSelectButton, SIGNAL(clicked(bool)), this, SLOT(selectPatternFile()));
    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(startMatching()));

    connect(bf, SIGNAL(returnPreTime(double)), this, SLOT(setPreLabel(double)));
    connect(bf, SIGNAL(returnMatchTime(double)), this, SLOT(setMatchLabel(double)));
    connect(bf, SIGNAL(returnTotalTime(double)), this, SLOT(setTotalLabel(double)));
    connect(bf, SIGNAL(returnResults(QString)), this, SLOT(setResults(QString)));

    connect(kmp, SIGNAL(returnPreTime(double)), this, SLOT(setPreLabel(double)));
    connect(kmp, SIGNAL(returnMatchTime(double)), this, SLOT(setMatchLabel(double)));
    connect(kmp, SIGNAL(returnTotalTime(double)), this, SLOT(setTotalLabel(double)));
    connect(kmp, SIGNAL(returnResults(QString)), this, SLOT(setResults(QString)));

    connect(bm, SIGNAL(returnPreTime(double)), this, SLOT(setPreLabel(double)));
    connect(bm, SIGNAL(returnMatchTime(double)), this, SLOT(setMatchLabel(double)));
    connect(bm, SIGNAL(returnTotalTime(double)), this, SLOT(setTotalLabel(double)));
    connect(bm, SIGNAL(returnResults(QString)), this, SLOT(setResults(QString)));
}

MainWindow::~MainWindow()
{
    delete bf;
    delete kmp;
    delete bm;
    delete ui;
}

void MainWindow::selectTextFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Text File"), filePath, tr("Allfile(*.*);;txtfile(*.txt)"));
    if (fileName != "")
        ui->tLineEdit->setText(fileName);
    filePath = fileName.mid(0, fileName.lastIndexOf('/'));
}

void MainWindow::selectPatternFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Text File"), filePath, tr("Allfile(*.*);;txtfile(*.txt)"));
    if (fileName != "")
        ui->pLineEdit->setText(fileName);
    filePath = fileName.mid(0, fileName.lastIndexOf('/'));
}

void MainWindow::startMatching()
{
    t = "";
    p = "";
    if (matching){
        QMessageBox::warning(this, "Error!", "Matching!");
        return;
    }

    resetLabels();

    QFile ft(ui->tLineEdit->text());
    if (!ft.open(QIODevice::ReadOnly|QIODevice::Text))//打开指定文件
    {
        QMessageBox::warning(this, "Error!", "未找到指定文本T文件！");
        return;
    }

    QTextStream txtInputT(&ft);
    while (!txtInputT.atEnd())
        t += txtInputT.readLine();
    ft.close();

    QFile fp(ui->pLineEdit->text());
    if (!fp.open(QIODevice::ReadOnly|QIODevice::Text))//打开指定文件
    {
        QMessageBox::warning(this, "Error!", "未找到指定模式P文件！");
        return;
    }

    QTextStream txtInputP(&fp);
    while (!txtInputP.atEnd())
        p += txtInputP.readLine();
    fp.close();


    if (!fp.open(QIODevice::ReadOnly|QIODevice::Text))//打开指定文件
    {
        QMessageBox::warning(this, "Error!", "未找到指定模式P文件！");
        return;
    }

    int n = t.length();
    int m = p.length();

    ui->tLengthLabel->setText(QString::number(n));
    ui->pLengthLabel->setText(QString::number(m));

    if (n == 0){
        QMessageBox::warning(this, "Error!", "文本T不能为空字符串！");
        return;
    }

    if (m == 0){
        QMessageBox::warning(this, "Error!", "模式P不能为空字符串！");
        return;
    }

    if (n < m){
        QMessageBox::warning(this, "Error!", "文本T长度小于模式P长度！");
        return;
    }

    bfMatching = true;
    matching = true;
    bf->setAttr(p, t);
    bf->start();
}

void MainWindow::resetLabels(){
    ui->bfPreLabel->clear();
    ui->bfMatchLabel->clear();
    ui->bfTotalLabel->clear();
    ui->bfResultLabel->clear();

    ui->kmpPreLabel->clear();
    ui->kmpMatchLabel->clear();
    ui->kmpTotalLabel->clear();
    ui->kmpResultLabel->clear();

    ui->bmPreLabel->clear();
    ui->bmMatchLabel->clear();
    ui->bmTotalLabel->clear();
    ui->bmResultLabel->clear();
}

void MainWindow::setPreLabel(double time)
{
    if (bfMatching){
        ui->bfPreLabel->setText(QString::number(time) + "s");
    }
    else if(kmpMathcing){
        ui->kmpPreLabel->setText(QString::number(time) + "s");
    }
    else if(bmMathcing){
        ui->bmPreLabel->setText(QString::number(time) + "s");
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
    else if(bmMathcing){
        ui->bmMatchLabel->setText(QString::number(time) + "s");
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
    else if(bmMathcing){
        ui->bmTotalLabel->setText(QString::number(time) + "s");
    }
}

void MainWindow::setResults(QString result)
{
    if (result == ""){
        result = "在文本T中未找到模式串P";
    }

    if (bfMatching){
        ui->bfResultLabel->setText(result);
        bfMatching = false;
        kmpMathcing = true;
        kmp->setAttr(p, t);
        kmp->start();
    }
    else if(kmpMathcing){
        ui->kmpResultLabel->setText(result);
        kmpMathcing = false;
        bmMathcing = true;
        bm->setAttr(p, t);
        bm->start();
    }
    else if(bmMathcing){
        ui->bmResultLabel->setText(result);
        matching = false;
        bmMathcing = false;
    }
}



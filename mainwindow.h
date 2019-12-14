#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include "bfthread.h"
#include "kthread.h"
#include "bmthread.h"

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
    void setPreLabel(double);
    void setMatchLabel(double);
    void setTotalLabel(double);
    void setResults(QString);
    void selectTextFile();
    void selectPatternFile();


private:
    Ui::MainWindow *ui;
    QString p, t;
    QString filePath = "C:/";
    bool bfMatching = false, kmpMathcing = false, bmMathcing = false, matching = false;

    BFThread *bf;
    KThread *kmp;
    BMThread *bm;

    void resetLabels();
};
#endif // MAINWINDOW_H

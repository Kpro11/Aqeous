#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //uncoments these when we are ready for transparrency
    //setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    //setParent(0); // Create TopLevel-Widget
    //setAttribute(Qt::WA_NoSystemBackground, true);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setAttribute(Qt::WA_PaintOnScreen); // not needed in Qt 5.2 and up
    setWindowOpacity(0.95);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_showROVSIM_clicked()
{
    int retcode = system("C:/_work/FhSim/sfhdev/FhSimPlayPen_vs14-64/bin/FhRtVis.exe C:/_work/FhSim/rov/input/Argus_Mini/Simulate/MiniNetPosCtrl");
    qDebug() << retcode;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "stdlib.h"
using namespace std;

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

    mCamera = new QCamera();

    mCameraViewfinder = new QCameraViewfinder(this);

    mCameraImageCapture = new QCameraImageCapture(mCamera,this);

    mVBoxLayout = new QVBoxLayout();

    mCamera->setViewfinder(mCameraViewfinder);

    mVBoxLayout->addWidget(mCameraViewfinder);
    mVBoxLayout->setMargin(0);

    ui->camera_col->addLayout(mVBoxLayout);
    mCamera->start();




    valueI = ui->depth_slider->value();

    ui->depth_counter->display(valueI);

}

MainWindow::~MainWindow()
{
    delete ui;
}



double callback(double val){
    return 2*val;
}


void MainWindow::on_depth_slider_valueChanged(int value)
{

    ui->depth_counter->display(callback(value));
}

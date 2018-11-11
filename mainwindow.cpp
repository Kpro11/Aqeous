#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
<<<<<<< HEAD
#include "stdlib.h"
using namespace std;
=======
#include <QtAV>
#include <QtAVWidgets>
#include <QMessageBox>
#include <QUrl>
#include <QVBoxLayout>

using namespace QtAV;
>>>>>>> a449429658f92bf5340cb5d2c14adb52647999f3

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    valueI = ui->depth_slider->value();

    ui->depth_counter->display(valueI);

}

MainWindow::~MainWindow()
{
    delete ui;
}



<<<<<<< HEAD
double callback(double val){
    return 2*val;
}


=======
>>>>>>> a449429658f92bf5340cb5d2c14adb52647999f3
void MainWindow::on_depth_slider_valueChanged(int value)
{

    ui->depth_counter->display(callback(value));
}

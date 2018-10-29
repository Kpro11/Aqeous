#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include <QtAV>
#include <QtAVWidgets>
#include <QMessageBox>
#include <QUrl>
#include <QVBoxLayout>

using namespace QtAV;

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
    //setWindowOpacity(0.95);

    m_player = new AVPlayer(ui->verticalLayout_2);
    m_vo = new VideoOutput(ui->verticalLayout_2);
    if (!m_vo->widget()) {
       QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
       return;
    }
    m_player->setRenderer(m_vo);
    ui->verticalLayout_2->addWidget(m_vo->widget());
    m_player->play("udp://224.0.0.1:9999");


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



void MainWindow::on_depth_slider_valueChanged(int value)
{

    ui->depth_counter->display(value);
}

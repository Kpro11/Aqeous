#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include <QtAV>
#include <QtAVWidgets>
#include <QMessageBox>
#include <QUrl>
#include <QVBoxLayout>
#include <QDebug>
#include <Windows.h>
#include <tcprov.h>
using namespace QtAV;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setup the QtAV player
    m_player = new AVPlayer(ui->QtAVWindow);

    m_vo = new VideoOutput(ui->QtAVWindow);
    if (!m_vo->widget()) {
       QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
       return;
    }
    m_player->setRenderer(m_vo);
    ui->QtAVWindow->addWidget(m_vo->widget());
    // change the following url to whatever
    // QtAV support a ton of different formats, so use whatever floats your boat.
    m_player->play("udp://224.0.0.1:9999");

    // depth:
    valueI = ui->depth_slider->value();

    ui->depth_counter->display(valueI);

    connect(&GamepadServer::instance(), SIGNAL(stateUpdate(GamepadState, int)),
            this, SLOT(catchGamepadState(GamepadState, int)));

    this->setWindowTitle(tr("Gamepad Server v0.1"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::catchGamepadState(const GamepadState & gps, const int & playerId) {
    //ui->depth_counter->display(value);
    /*
    qDebug() << "Player " << playerId << ": ";

    qDebug() << "Left Trigger: " << gps.m_lTrigger <<
                "\tRight Trigger: " << gps.m_rTrigger;
    qDebug() << "Left Thumb :: X Axis: " << gps.m_lThumb.xAxis <<
                "\t Y Axis: " << gps.m_lThumb.yAxis;
    qDebug() << "Right Thumb :: Y Axis: " << gps.m_rThumb.xAxis <<
                "\t Y Axis: " << gps.m_rThumb.yAxis;
    */

    double north = (TcpRov::maxThrusterHorizontal*gps.m_lThumb.yAxis);
    double east = (TcpRov::maxThrusterHorizontal*gps.m_lThumb.xAxis);
    double down = (TcpRov::maxThrusterVertical*(gps.m_rTrigger - gps.m_lTrigger));
    double psi = (TcpRov::maxThrusterHeading*gps.m_rThumb.xAxis); //TODO: Find right normalisation value


    qDebug() << "Sending this data to tcp: " << north << east << down << psi;
    tcpRov->setValues(north, east, down, psi);


    static bool lastKeyStateA = 0;


    if (gps.m_pad_a) {
        if (!lastKeyStateA) {
            tcpRov->toggleAutoDepth();
         } lastKeyStateA = 1;
    } else {
        lastKeyStateA = 0;
}
/*
    if (gps.m_pad_b) {
        qDebug() << "B Pressed.";
    }
    if (gps.m_pad_x) {
        qDebug() << "X Pressed.";
    }
    if (gps.m_pad_y) {
        qDebug() << "Y Pressed.";
    }
    if (gps.m_pad_up) {
        qDebug() << "Up Pressed.";
    }
    if (gps.m_pad_down) {
        qDebug() << "Down Pressed.";
    }
    if (gps.m_pad_left) {
        qDebug() << "Left Pressed.";
    }
    if (gps.m_pad_right) {
        qDebug() << "Right Pressed.";
    }
    if (gps.m_lShoulder) {
        qDebug() << "Left Shoulder Pressed.";
    }
    if (gps.m_rShoulder) {
        qDebug() << "Right Shoulder Pressed.";
    }
    if (gps.m_lThumb.pressed) {
        qDebug() << "Left Thumb Pressed.";
    }
    if (gps.m_rThumb.pressed) {
        qDebug() << "Right Thumb Pressed.";
    }
    if (gps.m_pad_start) {
        qDebug() << "Start Pressed.";
    }
    if (gps.m_pad_back) {
        qDebug() << "Back Pressed.";
    }
    */

}

void MainWindow::on_depth_slider_valueChanged(int value)
{

    ui->depth_counter->display(value);
}

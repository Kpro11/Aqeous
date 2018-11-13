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

    static bool lastKeyStateA = 0;
    static bool lastKeyStateB = 0;

    if (gps.m_pad_a) {
        if (!lastKeyStateA) {
            if (tcpRov->autoDepth == 0) {
                tcpRov->autoDepth = 1;
                tcpRov->referenceDepth = tcpRov->readData.down;
            } else {
                tcpRov->autoDepth = 0;
            }
         } lastKeyStateA = 1;
    }

    if (gps.m_pad_b) {
        if (!lastKeyStateB) {
            if (tcpRov->autoHeading == 0) {
                tcpRov->autoHeading = 1;
                double pi = 3.14; // Should be defined somewhere in the project
                tcpRov->referenceHeading = tcpRov->readData.yaw*pi/180;
            } else {
                tcpRov->autoHeading = 0;
            }
         } lastKeyStateB = 1;
    } else {
        lastKeyStateB = 0;
    }


    double north = (TcpRov::maxThrusterHorizontal*gps.m_lThumb.yAxis);
    double east = (TcpRov::maxThrusterHorizontal*gps.m_lThumb.xAxis);

    double down = (gps.m_rTrigger - gps.m_lTrigger);
    if (tcpRov->autoDepth == 0) {
        down = (TcpRov::maxThrusterVertical*down);
    } else {
        double adjustment = (down > 0 ? 1 : 0); // 0 or 1
        down = tcpRov->referenceDepth + adjustment*tcpRov->depthAdjustment;
    }

    double psi = gps.m_rThumb.xAxis;
    if (tcpRov->autoHeading == 0) {
        psi = (TcpRov::maxThrusterHeading*psi); //TODO: Find right normalisation value
    } else {
        double adjustment = (psi > 0 ? 1 : 0); // 0 or 1
        psi = tcpRov->referenceHeading + adjustment*tcpRov->headingAdjustment;
    }

    tcpRov->setValues(north, east, down, 0, 0, psi, tcpRov->autoDepth, tcpRov->autoHeading);
    qDebug() << "Sending this data to tcp: " << north << east << down << psi << tcpRov->nextData.autoDepth << tcpRov->nextData.autoHeading;
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

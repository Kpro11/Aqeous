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
#include <QSlider>
#include <QLabel>
#include "headingwidget.h"
#include "depthwidget.h"
#include <tcprov.h>

using namespace QtAV;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    // setup the QtAV player
    m_player = new QtAV::AVPlayer( this );
    m_vo = new QtAV::VideoOutput( this );

    // check if we can create the video renderer
    if (!m_vo->widget()) {
       QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
       return;
    }

    m_player->setRenderer(m_vo);

    // assign the qtav player to a widget
    videoPlayer = m_vo->widget();

    // set the central widget to be the video player
    // old way: ui->QtAVWindow->addWidget(m_vo->widget());
    setCentralWidget(videoPlayer);

    // change the following url to whatever
    // QtAV support a ton of different formats, so use whatever floats your boat.
    m_player->play("udp://224.0.0.1:9999");

    connect(&GamepadServer::instance(), SIGNAL(stateUpdate(GamepadState, int)),
            this, SLOT(catchGamepadState(GamepadState, int)));

}

// function that sets up the rest of ui that relies on screen dimensions, this function should be run after screen dimensions has been set.
void MainWindow::setupUI() {

    // Fancy Heading Slider Widget
    headingWidget = new HeadingWidget ( this );
    headingWidget->setupUI(videoPlayer, & windowWidth, & windowHeight);

    // Fancy Depth Slider Widget
    depthWidget = new DepthWidget ( this );
    depthWidget->setupUI(videoPlayer, & windowWidth, & windowHeight);

}

MainWindow::~MainWindow()
{
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
    static bool lastKeyStateX = 0;

    if (gps.m_pad_a) {
        if (!lastKeyStateA) {
            if (tcpRov->autoDepth == 0) {
                tcpRov->autoDepth = 1;
                tcpRov->referenceDepth = tcpRov->readData.down;
                emit updateAutoDepth(1);
            } else {
                tcpRov->autoDepth = 0;
                emit updateAutoDepth(0);
            }
         } lastKeyStateA = 1;
    } else {
        lastKeyStateA = 0;
    }

    if (gps.m_pad_b) {
        if (!lastKeyStateB) {
            if (tcpRov->autoHeading == 0) {
                tcpRov->autoHeading = 1;
                double pi = 3.14; // Should be defined somewhere in the project
                tcpRov->referenceHeading = tcpRov->readData.yaw*pi/180;
                emit updateAutoHeading(1);
            } else {
                tcpRov->autoHeading = 0;
                emit updateAutoHeading(0);
            }
         } lastKeyStateB = 1;
    } else {
        lastKeyStateB = 0;
    }

    if (gps.m_pad_up) {
        tcpRov->biasSurge = std::min(tcpRov->biasSurge+1, TcpRov::maxThrusterHorizontal);
    }
    if (gps.m_pad_down) {
        tcpRov->biasSurge = std::max(tcpRov->biasSurge-1, -TcpRov::maxThrusterHorizontal);;
    }
    if (gps.m_pad_right) {
        tcpRov->biasSway = std::min(tcpRov->biasSway+1, TcpRov::maxThrusterHorizontal);;
    }
    if (gps.m_pad_left) {
        tcpRov->biasSway = std::max(tcpRov->biasSway-1, -TcpRov::maxThrusterHorizontal);;
    }
    if (gps.m_rShoulder) {
        tcpRov->biasHeave = std::min(tcpRov->biasHeave+1, TcpRov::maxThrusterVertical);;
    }
    if (gps.m_lShoulder) {
        tcpRov->biasHeave = std::max(tcpRov->biasHeave-1, -TcpRov::maxThrusterVertical);;
    }

    if (gps.m_pad_x) {
        if (!lastKeyStateX) {
           tcpRov->biasSurge=0;
           tcpRov->biasSway=0;
           tcpRov->biasHeave=0;
         } lastKeyStateX = 1;
    } else {
        lastKeyStateX = 0;
    }


    double north = tcpRov->biasSurge + (TcpRov::maxThrusterHorizontal*gps.m_lThumb.yAxis);
    double east = tcpRov->biasSway + (TcpRov::maxThrusterHorizontal*gps.m_lThumb.xAxis);

    double down = (gps.m_rTrigger - gps.m_lTrigger);
    if (tcpRov->autoDepth) {
        double adjustment = (down > 0 ? 1 : 0); // 0 or 1
        down = tcpRov->referenceDepth + adjustment*tcpRov->depthAdjustment;
        emit updateDepthReference(down);
    } else {
        down = tcpRov->biasHeave + (TcpRov::maxThrusterVertical*down);

    }

    double psi = gps.m_rThumb.xAxis;

    if (tcpRov->autoHeading) {
        double adjustment = (psi > 0 ? 1 : 0); // 0 or 1
        psi = tcpRov->referenceHeading + adjustment*tcpRov->headingAdjustment;
        emit updateYawReference(psi);
    } else {
        psi = (TcpRov::maxThrusterHeading*psi); //TODO: Find right normalisation value
    }

    tcpRov->setValues(north, east, down, 0, 0, psi, tcpRov->autoDepth, tcpRov->autoHeading);


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

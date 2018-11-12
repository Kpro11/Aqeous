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

    double north = (TcpRov::maxThrusterHorizontal*gps.m_lThumb.yAxis);
    double east = (TcpRov::maxThrusterHorizontal*gps.m_lThumb.xAxis);
    double down = (TcpRov::maxThrusterVertical*(gps.m_rTrigger - gps.m_lTrigger));
    double psi = (TcpRov::maxThrusterHeading*gps.m_rThumb.xAxis); //TODO: Find right normalisation value






    static bool lastKeyStateA = 0;
    static bool lastKeyStateB = 0;

    double toggleAutoDepth = 0;
    double toggleAutoHeading = 0;


    if (gps.m_pad_a) {
        if (!lastKeyStateA) {    
            toggleAutoDepth = 1;
         } lastKeyStateA = 1;
    } else {
        lastKeyStateA = 0;
    }

    if (gps.m_pad_b) {
        if (!lastKeyStateB) {
            toggleAutoHeading = 1;
         } lastKeyStateB = 1;
    } else {
        lastKeyStateB = 0;
    }

    tcpRov->setValues(north, east, down, 0, 0, psi, toggleAutoDepth, toggleAutoHeading);
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

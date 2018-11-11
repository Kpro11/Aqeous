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

    // header widget
    headingWidget = new HeadingWidget ( videoPlayer, & windowWidth, & windowHeight);

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

    double north = gps.m_lThumb.yAxis;
    double east = gps.m_lThumb.xAxis;
    double down = gps.m_rThumb.yAxis;
    double psi = gps.m_rThumb.xAxis;

    if (north != 0 || east != 0 || down != 0 || psi != 0) {
        qDebug() << "Sending this data to tcp: " << north << east << down << psi;
        tcpRov->setValues(north, east, down, psi);
    }

    /*
    if (gps.m_pad_a) {
        qDebug() << "A Pressed.";
    }
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

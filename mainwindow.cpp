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

void MainWindow::checkAndHandleFlag(bool button, bool& lastKeyState, double& flag, double& reference, double referenceValue) {
    if (button) {
        if (!lastKeyState) {
            if (flag == 0) {
                flag = 1;
                reference = referenceValue;
            } else {
                flag = 0;
            }
         } lastKeyState = 1;
    } else {
        lastKeyState = 0;
    }
}

void MainWindow::handleBiasUp(bool button, bool& lastKeyState, double& bias, double maxValue) {

    if (button) {
        if (bias == 0) {
            if(lastKeyState) {
                bias = 0;
                lastKeyState = 1;
            } else {
                bias = std::min(bias+1, maxValue);
                lastKeyState = 1;
            }
        } else {
            bias = std::min(bias+1, maxValue);
            lastKeyState = 1;
        }
    } else {
        lastKeyState = 0;
    }
}

void MainWindow::handleBiasDown(bool button, bool& lastKeyState, double& bias, double minValue) {

    if (button) {
        if (bias == 0) {
            if(lastKeyState) {
                bias = 0;
                lastKeyState = 1;
            } else {
                bias = std::max(bias-1, minValue);
                lastKeyState = 1;
            }
        } else {
            bias = std::max(bias-1, minValue);
            lastKeyState = 1;
        }
    } else {
        lastKeyState = 0;
    }
}

void MainWindow::autoHandling(double autoFlagOn, double reference, double autoAdjustment, double& force, double maxValue) {
    if (autoFlagOn) {
        double adjustment = 0;
        if (force > 0) {
            adjustment = 1;
        }
        else if (force < 0) {
            adjustment = -1;
        }
        force = reference + adjustment*autoAdjustment;
        tcpRov->referenceHeading += adjustment * tcpRov->headingAdjustment;
    } else {
        force = (maxValue*force); //TODO: Find right normalisation value
    }
}


void MainWindow::catchGamepadState(const GamepadState & gps, const int & playerId) {

    //0 if button was up (unpressed), 1 if button was down (pressed)
    static bool lastKeyStateA = 0;
    static bool lastKeyStateB = 0;
    static bool lastKeyStateDown = 0;
    static bool lastKeyStateUp = 0;
    static bool lastKeyStateLeft = 0;
    static bool lastKeyStateRight = 0;
    static bool lastKeyStateTriggerL = 0;
    static bool lastKeyStateTriggerR = 0;

    checkAndHandleFlag(gps.m_pad_a, lastKeyStateA, tcpRov->autoDepth, tcpRov->referenceDepth, tcpRov->readData.down);
    checkAndHandleFlag(gps.m_pad_b, lastKeyStateB, tcpRov->autoHeading, tcpRov->referenceHeading, tcpRov->readData.yaw*3.14159265/180);

    handleBiasUp(gps.m_pad_up, lastKeyStateUp, tcpRov->biasSurge, TcpRov::maxThrusterHorizontal);
    handleBiasDown(gps.m_pad_down, lastKeyStateDown, tcpRov->biasSurge, -TcpRov::maxThrusterHorizontal);

    handleBiasUp(gps.m_pad_right, lastKeyStateRight, tcpRov->biasSway, TcpRov::maxThrusterHorizontal);
    handleBiasDown(gps.m_pad_left, lastKeyStateLeft, tcpRov->biasSway, -TcpRov::maxThrusterHorizontal);

    handleBiasUp(gps.m_rShoulder, lastKeyStateTriggerR, tcpRov->biasHeave, TcpRov::maxThrusterVertical);
    handleBiasDown(gps.m_lShoulder, lastKeyStateTriggerL, tcpRov->biasHeave, -TcpRov::maxThrusterVertical);

    if (gps.m_pad_x) {
        if (gps.m_lShoulder || gps.m_rShoulder) {
            tcpRov->biasHeave=0;
        } else if (gps.m_pad_up || gps.m_pad_down) {
            tcpRov->biasSurge=0;
        } else if (gps.m_pad_left || gps.m_pad_right) {
            tcpRov->biasSway=0;
        }
    }

    if (gps.m_pad_y) {
           tcpRov->biasSurge=0;
           tcpRov->biasSway=0;
           tcpRov->biasHeave=0;
    }

    double north = tcpRov->biasSurge + (TcpRov::maxThrusterHorizontal*gps.m_lThumb.yAxis);
    double east = tcpRov->biasSway + (TcpRov::maxThrusterHorizontal*gps.m_lThumb.xAxis);

    double down = (gps.m_rTrigger - gps.m_lTrigger);
    autoHandling(tcpRov->autoDepth, tcpRov->referenceDepth, tcpRov->depthAdjustment, down, TcpRov::maxThrusterVertical);

    double psi = gps.m_rThumb.xAxis;
    autoHandling(tcpRov->autoHeading, tcpRov->referenceHeading, tcpRov->headingAdjustment, psi, TcpRov::maxThrusterHeading);

    tcpRov->setValues(north, east, down, 0, 0, psi, tcpRov->autoDepth, tcpRov->autoHeading);
}

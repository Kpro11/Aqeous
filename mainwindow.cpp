#include "mainwindow.h"
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
#include <tcprov.h>
#include <constantvalues.h>
#include <cmath>

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

    // Fancy bias arrow / cordinate system shower;
    // Create a surrounding QFrame that QPainter can live in
    QFrame * biasContainer = new QFrame( videoPlayer );
    biasContainer->setGeometry(windowWidth - 400, windowHeight - 400 , 300, 300);
    //biasContainer->setStyleSheet("QFrame { border: 1px solid yellow}");
    biasWidget = new BiasWidget( biasContainer, 300, 300);
}

MainWindow::~MainWindow()
{
}

/**
 * @brief MainWindow::checkAndHandleFlag    Toggles flag if button is pressed (not held)
 * @param button            Bool to signal if a button is pressed
 * @param lastKeyState      Used to detect when a button is pressed (as opposed to held)
 * @param flag              Flag to be toggled when button pressed
 * @param reference         Reference which will be used when flag is set
 * @param referenceValue    Value reference will be set to (last known value from ROV)
 */
void MainWindow::checkAndHandleFlag(bool button, bool& lastKeyState, double& flag, double& reference, double referenceValue) {
    if (button) {
        if (!lastKeyState) {
            if (flag == 0) {
                flag = 1;
                reference = referenceValue;
            } else {
                flag = 0;
            }
            tcpRov->autoHeadingWasUpdated();
            tcpRov->autoDepthWasUpdated();

         } lastKeyState = 1;
    } else {
        lastKeyState = 0;
    }
}

/**
 * @brief MainWindow::handleBiasUp  Handles changes of bias in a positive direction
 * @param button        Bool to signal if a button is pressed
 * @param lastKeyState  Used to detect when a button is pressed (as opposed to held)
 * @param bias          Current value for bias, which will be updated
 * @param maxValue      Maximum legal value for bias, generally the maximum value for the thruster
 */
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

/**
 * @brief MainWindow::handleBiasDown    Handles changes of bias in a negative direction
 * @param button        Bool to signal if a button is pressed
 * @param lastKeyState  Used to detect when a button is pressed (as opposed to held)
 * @param bias          Current value for bias, which will be updated
 * @param minValue      Minimum legal value for bias, generally the minimum value for the thruster
 */
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

/**
 * @brief MainWindow::autoHandling  Handles auto and manual mode for a force or moment
 * @param autoFlagOn        Flag to signify if manual or auto mode
 * @param reference         Reference value for auto mode
 * @param autoAdjustment    Amount the reference will be adjusted by for each tick
 * @param force             Value of the force/moment, starts out as a number between -1 and 1, ends up as either a force or reference
 * @param bias              Current bias of the force/moment
 * @param maxValue          Maximum value for the thruster
 */
void MainWindow::autoHandling(double autoFlagOn, double& reference, double autoAdjustment, double& force, double bias, double maxValue) {
    if (autoFlagOn) {
        double adjustment = 0;
        if (force > 0) {
            adjustment = 1;
        }
        else if (force < 0) {
            adjustment = -1;
        }
        force = reference + adjustment*autoAdjustment;
        reference += adjustment * autoAdjustment;
    } else {
        force = bias + (maxValue*force); //TODO: Find right normalisation value
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

    constexpr double pi = 3.14159265;

    checkAndHandleFlag(gps.m_pad_a, lastKeyStateA, tcpRov->autoDepth, tcpRov->referenceDepth, tcpRov->readData.down);
    checkAndHandleFlag(gps.m_pad_b, lastKeyStateB, tcpRov->autoHeading, tcpRov->referenceHeading, std::fmod(tcpRov->readData.yaw*pi/180, 2*pi));

    handleBiasUp(gps.m_pad_up, lastKeyStateUp, tcpRov->biasSurge, constantValues::maxThrusterHorizontal);
    handleBiasDown(gps.m_pad_down, lastKeyStateDown, tcpRov->biasSurge, -constantValues::maxThrusterHorizontal);

    handleBiasUp(gps.m_pad_right, lastKeyStateRight, tcpRov->biasSway, constantValues::maxThrusterHorizontal);
    handleBiasDown(gps.m_pad_left, lastKeyStateLeft, tcpRov->biasSway, -constantValues::maxThrusterHorizontal);

    handleBiasUp(gps.m_rShoulder, lastKeyStateTriggerR, tcpRov->biasHeave, constantValues::maxThrusterVertical);
    handleBiasDown(gps.m_lShoulder, lastKeyStateTriggerL, tcpRov->biasHeave, -constantValues::maxThrusterVertical);

    // Reset various biases
    if (gps.m_pad_x) {
        if (gps.m_lShoulder || gps.m_rShoulder) {
            tcpRov->biasHeave=0;
        } else if (gps.m_pad_up || gps.m_pad_down) {
            tcpRov->biasSurge=0;
        } else if (gps.m_pad_left || gps.m_pad_right) {
            tcpRov->biasSway=0;
        }
    }

    // Reset all biases
    if (gps.m_pad_y) {
           tcpRov->biasSurge=0;
           tcpRov->biasSway=0;
           tcpRov->biasHeave=0;
    }

    double north = tcpRov->biasSurge + (constantValues::maxThrusterHorizontal*gps.m_lThumb.yAxis);
    double east = tcpRov->biasSway + (constantValues::maxThrusterHorizontal*gps.m_lThumb.xAxis);
    double down = (gps.m_rTrigger - gps.m_lTrigger);
    autoHandling(tcpRov->autoDepth, tcpRov->referenceDepth, constantValues::depthAdjustment, down, tcpRov->biasHeave, constantValues::maxThrusterVertical);

    double psi = gps.m_rThumb.xAxis;
    // Bias set to 0 because yaw bias is not implemented
    autoHandling(tcpRov->autoHeading, tcpRov->referenceHeading, constantValues::headingAdjustment, psi, 0, constantValues::maxThrusterHeading);

    tcpRov->setValues(north, east, down, 0, 0, psi, tcpRov->autoDepth, tcpRov->autoHeading);
}

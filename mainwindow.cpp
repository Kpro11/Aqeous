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

    // Fancy bias arrow / cordinate system shower;
    // Create a surrounding QFrame that QPainter can live in
    QFrame * biasContainer = new QFrame( videoPlayer );
    biasContainer->setGeometry(1200,500,500,500);
    biasContainer->setStyleSheet("QFrame { border: 1px solid yellow}");
    biasWidget = new BiasWidget( biasContainer, 500, 500);
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

    //0 if button was up (unpressed), 1 if button was down (pressed)
    static bool lastKeyStateA = 0;
    static bool lastKeyStateB = 0;
    static bool lastKeyStateDown = 0;
    static bool lastKeyStateUp = 0;
    static bool lastKeyStateLeft = 0;
    static bool lastKeyStateRight = 0;
    static bool lastKeyStateTriggerL = 0;
    static bool lastKeyStateTriggerR = 0;

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
        if (tcpRov->biasSurge == 0) {
            if(lastKeyStateUp) {
                tcpRov->biasSurge = 0;
                lastKeyStateUp = 1;
            } else {
                tcpRov->biasSurge = std::min(tcpRov->biasSurge+1, TcpRov::maxThrusterHorizontal);
                lastKeyStateUp = 1;
            }
        } else {
            tcpRov->biasSurge = std::min(tcpRov->biasSurge+1, TcpRov::maxThrusterHorizontal);
            lastKeyStateUp = 1;
        }
    } else {
        lastKeyStateUp = 0;
    }

    if (gps.m_pad_down) {
        if (tcpRov->biasSurge == 0) {
            if(lastKeyStateDown) {
                tcpRov->biasSurge = 0;
                lastKeyStateDown = 1;
            } else {
                tcpRov->biasSurge = std::max(tcpRov->biasSurge-1, -TcpRov::maxThrusterHorizontal);
                lastKeyStateDown = 1;
            }
        } else {
            tcpRov->biasSurge = std::max(tcpRov->biasSurge-1, -TcpRov::maxThrusterHorizontal);
            lastKeyStateDown = 1;
        }
    } else {
        lastKeyStateDown = 0;
    }

    if (gps.m_pad_right) {
        if (tcpRov->biasSway == 0) {
            if(lastKeyStateRight) {
                tcpRov->biasSway = 0;
                lastKeyStateRight = 1;
            } else {
               tcpRov->biasSway = std::min(tcpRov->biasSway+1, TcpRov::maxThrusterHorizontal);
                lastKeyStateRight = 1;
            }
        } else {
            tcpRov->biasSway = std::min(tcpRov->biasSway+1, TcpRov::maxThrusterHorizontal);
            lastKeyStateRight = 1;
        }
    } else {
        lastKeyStateRight = 0;
    }

    if (gps.m_pad_left) {
        if (tcpRov->biasSway == 0) {
            if(lastKeyStateLeft) {
                tcpRov->biasSway = 0;
                lastKeyStateLeft = 1;
            } else {
               tcpRov->biasSway = std::max(tcpRov->biasSway-1, -TcpRov::maxThrusterHorizontal);
                lastKeyStateLeft = 1;
            }
        } else {
            tcpRov->biasSway = std::max(tcpRov->biasSway-1, -TcpRov::maxThrusterHorizontal);
            lastKeyStateLeft = 1;
        }
    } else {
        lastKeyStateLeft = 0;
    }


    if (gps.m_rShoulder) {
        if (tcpRov->biasHeave == 0) {
            if(lastKeyStateTriggerR) {
                tcpRov->biasHeave = 0;
                lastKeyStateTriggerR = 1;
            } else {
               tcpRov->biasHeave = std::min(tcpRov->biasHeave+1, TcpRov::maxThrusterVertical);
                lastKeyStateTriggerR = 1;
            }
        } else {
            tcpRov->biasHeave = std::min(tcpRov->biasHeave+1, TcpRov::maxThrusterVertical);
            lastKeyStateTriggerR = 1;
        }
    } else {
        lastKeyStateTriggerR = 0;
    }

    if (gps.m_lShoulder) {
        if (tcpRov->biasHeave == 0) {
            if(lastKeyStateTriggerL) {
                tcpRov->biasHeave = 0;
                lastKeyStateTriggerL = 1;
            } else {
               tcpRov->biasHeave = std::max(tcpRov->biasHeave-1, -TcpRov::maxThrusterVertical);
                lastKeyStateTriggerL = 1;
            }
        } else {
            tcpRov->biasHeave = std::max(tcpRov->biasHeave-1, -TcpRov::maxThrusterVertical);
            lastKeyStateTriggerL = 1;
        }
    } else {
        lastKeyStateTriggerL = 0;
    }

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

    if (tcpRov->autoDepth) {
        double adjustment = 0;
        if (down > 0) {
            adjustment = 1;
        }
        else if (down < 0) {
            adjustment = -1;
        }
        down = tcpRov->referenceDepth + adjustment*tcpRov->depthAdjustment;
        emit updateDepthReference(down);
        tcpRov->referenceDepth += adjustment * tcpRov->depthAdjustment;
    } else {
        down = tcpRov->biasHeave + (TcpRov::maxThrusterVertical*down);

    }

    double psi = gps.m_rThumb.xAxis;


    if (tcpRov->autoHeading) {
        double adjustment = 0;
        if (psi > 0) {
            adjustment = 1;
        }
        else if (psi < 0) {
            adjustment = -1;
        }
        psi = tcpRov->referenceHeading + adjustment*tcpRov->headingAdjustment;
        emit updateYawReference(psi);
        tcpRov->referenceHeading += adjustment * tcpRov->headingAdjustment;
    } else {
        psi = (TcpRov::maxThrusterHeading*psi); //TODO: Find right normalisation value
    }

    tcpRov->setValues(north, east, down, 0, 0, psi, tcpRov->autoDepth, tcpRov->autoHeading);
}

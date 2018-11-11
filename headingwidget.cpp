#include "headingwidget.h"
#include <QDebug>
#include "QHBoxLayout"
#include <QLabel>

HeadingWidget::HeadingWidget(QWidget *parent) : QWidget(parent)
{

}

void HeadingWidget::setupUI(QWidget * _videoPlayer, int * _windowWidth, int * _windowHeight) {
    videoPlayer = _videoPlayer;
    windowWidth = _windowWidth;
    windowHeight = _windowHeight;

    // create frame that acts as a container for this heading widget;
    frame = new QFrame( videoPlayer );
    frame->setObjectName("headingWidget");

    // set the position and dimensions (start x, start y, width, heigth)
    frame->setGeometry(200,80, *windowWidth - 400, 40);
    // add a border to the bottom
    frame->setStyleSheet( "QFrame#headingWidget { border: 3px solid white; border-top: 0; border-left: 0; border-right: 0; }" );

}



void HeadingWidget::updateYaw(double _yaw) {
    // this must be converted to degrees:
    yaw = _yaw;
    currentYaw->setText(QString::number(_yaw));

    // todo add conversion from rad to degrees here
}



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

    int frameStartX = 200;
    int frameStartY = 80;
    frameWidth = *windowWidth - frameStartX * 2;
    frameHeight = 40;

    // create frame that acts as a container for this heading widget;
    frame = new QFrame( videoPlayer );
    frame->setObjectName("headingWidget");

    // set the position and dimensions (start x, start y, width, heigth
    frame->setGeometry(frameStartX, frameStartY, frameWidth, frameHeight);
    // add a border to the bottom
    frame->setStyleSheet( "QFrame#headingWidget { border: 3px solid white; border-top: 0; border-left: 0; border-right: 0; }" );

    // Add a label to show current heading / yaw
    currentYaw = new QLabel( QString::number(yaw) , videoPlayer );
    currentYaw->setAlignment(Qt::AlignCenter);

    int currentYawWidth = 200;
    int currentYawHeight = frameHeight * 1.5;
    int currentYawX = frameStartX + (frameWidth / 2) - currentYawWidth / 2; //position to horizontally center the widget
    int currentYawY = frameStartY + frameHeight + frameHeight / 2;  // position to vertically center the widget
    currentYaw->setGeometry(currentYawX, currentYawY, currentYawWidth, currentYawHeight);

    QString currentYawStyleSheet = "QLabel { ";
    currentYawStyleSheet += "color: black; ";
    currentYawStyleSheet += "font-size: 30px; ";
    currentYawStyleSheet += "background-color: white; ";
    currentYawStyleSheet += "}";

    currentYaw->setStyleSheet(currentYawStyleSheet);

    // Create all the labels we need with appropiate styling
    for (int i = 0; i < 360; i += 15) {
        QString stylesheet = "";
        QString charStyle = " QLabel { color: white; text-size: 35px; } ";
        QString numStyle = " QLabel { color: grey; text-size: 20px; } ";

        HeadingLabel *newLabel = new HeadingLabel();
        newLabel->value = i;
        switch (i) {
            case 0:
                newLabel->letter = 'N';
                stylesheet = charStyle;
                break;
            case 90:
                newLabel->letter = 'E';
                stylesheet = charStyle;
                break;
            case 180:
                newLabel->letter = 'S';
                stylesheet = charStyle;
                break;
            case 270:
                newLabel->letter = 'W';
                stylesheet = charStyle;
                break;
            default:
                newLabel->letter = ' ';
                stylesheet = numStyle;
        }

        if (newLabel->letter != ' ') {
            newLabel->label = new QLabel(newLabel->letter, frame);
        } else {
            newLabel->label = new QLabel(QString::number(newLabel->value), frame);
}

        newLabel->label->setStyleSheet(stylesheet);

        // Hide the label for now
        newLabel->label->setGeometry(0,0,0,0);

        // add label to list of all labels
        labels << newLabel;
    }

}


void HeadingWidget::updateYaw(double _yaw) {
    // this must be converted to degrees:
    yaw = _yaw;
    currentYaw->setText(QString::number(_yaw));

    // todo add conversion from rad to degrees here
}



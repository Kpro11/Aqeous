#include "headingwidget.h"
#include <QDebug>
#include "QHBoxLayout"
#include <QLabel>
#include <math.h>

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
    currentYawStyleSheet += "color: white; ";
    currentYawStyleSheet += "font-size: 30px; ";
    currentYawStyleSheet += "}";

    currentYaw->setStyleSheet(currentYawStyleSheet);

    // Create all the labels we need with appropiate styling
    for (int i = 0; i < 360; i += 15) {
        QString stylesheet = "";


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

    updateLabels();

    //testTimer = new QTimer(this);
    //connect(testTimer, SIGNAL(timeout()), this, SLOT(testUpdate()));
    //testTimer->start(30);
}

//This function will update the current heading / yaw view by setting new positions on all labels
void HeadingWidget::updateLabels() {
    // asumes that yaw is in degrees

    // find out how many pixels there are available per label
    int pixelsPerSlot = frameWidth / 12;

    // iterate trough every label
    for (int i = 0; i < labels.size(); i++) {

        int point = labels[i]->value;

        // finds the distance in this 360 degree circle
        double distance = distanceFromPointToYaw(point, yaw);

        // label should only show if it is in range
        if (abs(distance) <= 90) {

            // normalize
            double positionInRow = (distance + 90) / 15;

            // set position
            labels[i]->label->setGeometry(positionInRow * pixelsPerSlot, 0, 30, 30);




        } else {
            // hide the label
            labels[i]->label->setGeometry(0,0,0,0);
        }
    }
}

// calculates true distance between two points in a 360 degrees circle
double distanceFromPointToYaw(double point, double yaw) {

    // To find the distance between two points in a "circle" you have to do more than just
    // calculate the difference. You also have to take into account that the values 0 and 360 are neighbors.
    // We therefor calculate three values here: Normal distance, distance counter-clockwise and
    // distance clockwise. The lowest of these variables are the true distance.

    // in this code we calculate (counter-)clockwise withouth checking if yaw was reached,
    // this is to keep the math simple

    // For example: A yaw at 330 and a point at 20 are only 50 degrees away from eachother
    // normal distance = 310
    // counter-clockwise distance = 360+320 = 680
    // clockwise distance = 50

    // the normal distance between yaw and point
    double distanceBetweenYawAndPoint = abs(yaw - point);

    // calculate variables to help traverse (counter-)clockwise
    double yawDistanceToZero = yaw;
    double yawDistanceToMax = 360 - yaw;

    double pointDistanceToZero = point;
    double pointDistanceToMax = 360 - point;

    // distance from point to max (360) + from min (0) to yaw point
    double distanceAbove = pointDistanceToMax + yawDistanceToZero;
    // distance from point to min(0) + from max(360) to yaw point.
    double distanceBelow = pointDistanceToZero + yawDistanceToMax;

    // we now know what the true distance is.

    // find the lowest value and return
    if(distanceAbove < distanceBelow && distanceAbove < distanceBetweenYawAndPoint) {
        // since the value was above we return negative
        return -1 * distanceAbove;
    } else if (distanceBelow < distanceAbove && distanceBelow < distanceBetweenYawAndPoint) {
        return distanceBelow;
    } else { // distanceBetweenYawAndPoint was lowest
        // we calculate it again because it will produce the rigth "fortegn"
        return point - yaw;
    }

    // The code belov returns the true distance
    // Choose the value that was lowest. This is the correct value
    // return std::min(std::min(distanceAbove, distanceBelow), distanceBetweenYawAndPoint);
}

void HeadingWidget::testUpdate() {
    /*
    yaw = abs(360 * sin(testTime * 3.141 / ( 360 * 4)) + 1);
    testTime += 1;
    updateLabels();
    */
}


void HeadingWidget::updateYaw(double _yaw) {
    // yaw must be converted to degrees first

    // uncomment when yaw is fixed in the simulator
    //yaw = _yaw;

    currentYaw->setText(QString::number(yaw));

    // todo add conversion from rad to degrees here
}

// we ignore _autoDepth
void HeadingWidget::updateAutoHeading(double _autoDepth, double _autoHeading) {
    QString currentYawStyleSheet = "QLabel { ";
    currentYawStyleSheet += "color: black; ";
    currentYawStyleSheet += "font-size: 30px; ";

    if (_autoHeading >= 1) {
        currentYawStyleSheet += "color: yellow; ";
    } else {
         currentYawStyleSheet += "color: white; ";
    }
    currentYawStyleSheet += "}";
    currentYaw->setStyleSheet(currentYawStyleSheet);
}


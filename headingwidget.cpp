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

    pixelsPerSlot = frameWidth / 12;

    // create frame that acts as a container for this heading widget;
    frame = new QFrame( videoPlayer );
    frame->setObjectName("headingWidget");

    // set the position and dimensions (start x, start y, width, heigth
    frame->setGeometry(frameStartX, frameStartY, frameWidth, frameHeight);
    // add a border to the bottom
    frame->setStyleSheet( "QFrame#headingWidget { border: 3px solid white; border-top: 0; border-left: 0; border-right: 0; }" );

    // Add a label to show current heading / yaw
    currentYaw = new QLabel( QString::number(yaw) , videoPlayer );
    currentYaw->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    currentYaw->setStyleSheet(yawStyleSheet);
    currentYawPos = new Position();

    currentYawPos->width = 200;
    currentYawPos->height = frameHeight * 1.5;
    currentYawPos->x = frameStartX + (frameWidth / 2) - currentYawPos->width / 2; //position to horizontally center the widget
    currentYawPos->y = frameStartY + frameHeight + frameHeight / 2;  // position to vertically center the widget
    setGeometry(currentYaw, currentYawPos);

    yawReference = new QLabel( "0", videoPlayer );
    yawReference->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    yawReference->setStyleSheet(yawStyleSheet);
    yawReferencePos = new Position();

    yawReferencePos->width = currentYawPos->width;
    yawReferencePos->height = currentYawPos->height;
    yawReferencePos->x = currentYawPos->x;
    yawReferencePos->y = currentYawPos->y + currentYawPos->height;
    setGeometry(yawReference, yawReferencePos);

    yawReferenceLock = new QLabel("0", videoPlayer );
    yawReferenceLock->setStyleSheet(yawStyleSheet);
    yawReferenceLock->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    yawReferenceLockPos = new Position();

    yawReferenceLockPos->x= yawReferencePos->x - yawReferencePos->width / 1.5;
    yawReferenceLockPos->y = yawReferencePos->y;
    yawReferenceLockPos->width = yawReferencePos->width;
    yawReferenceLockPos->height = yawReferencePos->height;
    setGeometry(yawReferenceLock, yawReferenceLockPos);

    QPixmap pixmapTarget = QPixmap(":/images/lock-icon.png");
    pixmapTarget = pixmapTarget.scaled(yawReferencePos->height / 2.2, yawReferencePos->height / 2.2);
    yawReferenceLock->setPixmap(pixmapTarget);

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

void HeadingWidget::updateLockPosition() {
    QString yRef = QString::number(yawRef);
}

void HeadingWidget::setGeometry(QLabel * _lbl, Position * _lblPos) {
    _lbl->setGeometry(_lblPos->x, _lblPos->y, _lblPos->width, _lblPos->height);
}

//This function will update the current heading / yaw view by setting new positions on all labels
void HeadingWidget::updateLabels() {
    // asumes that yaw is in degrees
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
double distanceFromPointToYaw(double point, double _yaw) {

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
    int yaw = static_cast<int>(abs(_yaw)) % 360;

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

    yaw = abs(_yaw);


    currentYaw->setText(formatYaw(yaw));
    updateLabels();

    // todo add conversion from rad to degrees here
}

// This function will output a string with exactly one decimal
QString HeadingWidget::formatYaw(double _yaw) {
    QString output = "";
    // round of decimal to 1 place
    double rounded = ceil(_yaw * 10) / 10;

    output = QString::number(rounded);

    // add decimal if not there
    if (floor(rounded) == rounded) {
        output += ".0";
    }

    return output;
}

void HeadingWidget::updateYawReference(double _yaw) {
    yawReference->setText(formatYaw(_yaw));
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


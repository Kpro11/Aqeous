#include "depthwidget.h"

DepthWidget::DepthWidget(QWidget *parent) : QWidget(parent)
{

}

void DepthWidget::setupUI(QWidget * _videoPlayer, int * _windowWidth, int * _windowHeight) {
    videoPlayer = _videoPlayer;
    windowWidth = _windowWidth;
    windowHeight = _windowHeight;

    int frameStartX = 80;
    int frameStartY = 300;
    frameWidth = 40;
    frameHeight = *windowHeight - frameStartY * 1.5;

    // create frame that acts as a container for this heading widget;
    frame = new QFrame( videoPlayer );
    frame->setObjectName("depthWidget");

    // set the position and dimensions (start x, start y, width, heigth
    frame->setGeometry(frameStartX, frameStartY, frameWidth, frameHeight);
    // add a border to the bottom
    frame->setStyleSheet( "QFrame#depthWidget { border: 3px solid white; border-top: 0; border-left: 0; border-bottom: 0; }" );


    // Add a label to show current depth
    currentDepth = new QLabel( QString::number(depth) , videoPlayer );
    currentDepth->setAlignment(Qt::AlignCenter);

    int currentDepthWidth = 200;
    int currentDepthHeight = 60;
    int currentDepthX = frameStartX + frameWidth + currentDepthWidth / 8; //position to horizontally center the widget
    int currentDepthY = frameStartY + frameHeight / 2 - currentDepthHeight / 2;  // position to vertically center the widget
    currentDepth->setGeometry(currentDepthX, currentDepthY, currentDepthWidth, currentDepthHeight);

    QString currentDepthStyleSheet = "QLabel { ";
    currentDepthStyleSheet += "color: black; ";
    currentDepthStyleSheet += "font-size: 30px; ";
    currentDepthStyleSheet += "background-color: white; ";
    currentDepthStyleSheet += "}";

    currentDepth->setStyleSheet(currentDepthStyleSheet);

    // Create all the labels we need with appropiate styling
    // 200 labels because tether on ROV is max 200m
    for (int i = 0; i < 200; i++) {
        QString bigNumStyle = " QLabel { color: white; text-size: 35px; } ";
        QString numStyle = " QLabel { color: grey; text-size: 20px; } ";

        DepthLabel *newLabel = new DepthLabel();
        newLabel->value = i;

        newLabel->label = new QLabel(QString::number(newLabel->value) + "m", frame);

        // Make every 5m stand out
        if (i % 5 == 0) {
            newLabel->label->setStyleSheet(bigNumStyle);
        } else {
            newLabel->label->setStyleSheet(numStyle);
        }

        // Hide the label for now
        newLabel->label->setGeometry(0,0,0,0);

        // add label to list of all labels
        labels << newLabel;
    }
}

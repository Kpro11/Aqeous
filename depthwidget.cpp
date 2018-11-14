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
    frameWidth = 60;
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
    int currentDepthX = frameStartX + frameWidth + currentDepthWidth / 16; //position to horizontally center the widget
    int currentDepthY = frameStartY + frameHeight / 2 - currentDepthHeight / 2;  // position to vertically center the widget
    currentDepth->setGeometry(currentDepthX, currentDepthY, currentDepthWidth, currentDepthHeight);

    QString currentDepthStyleSheet = "QLabel { ";
    currentDepthStyleSheet += "color: white; ";
    currentDepthStyleSheet += "font-size: 30px; ";
    currentDepthStyleSheet += "}";

    currentDepth->setStyleSheet(currentDepthStyleSheet);

    // Create all the labels we need with appropiate styling
    // 200 labels because tether on ROV is max 200m
    for (int i = 0; i < 200; i++) {
        QString bigNumStyle = " QLabel { color: white; font-size: 23px; } ";
        QString numStyle = " QLabel { color: grey; font-size: 17px; } ";

        DepthLabel *newLabel = new DepthLabel();
        newLabel->value = i;

        newLabel->label = new QLabel(QString::number(newLabel->value), frame);

        newLabel->label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

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
    updateLabels();
}

// update the current depth by setting new position on all labels
void DepthWidget::updateLabels() {
    //iterate trough all the labels
    for (int i = 0; i < labels.size(); i++) {
        int baseStep = 40 * 1.2;
        int middle = frameHeight / 2 - 20;
        int y = i * baseStep + middle - depth * baseStep;
        labels[i]->label->setGeometry(0, y, 40, 40);
    }
}

void DepthWidget::updateDepth(double _depth) {
    depth = _depth;
    currentDepth->setText(QString::number(_depth));
    updateLabels();
}

void DepthWidget::updateFlags(double _autoDepth, double _autoHeading) {
    QString currentDepthStyleSheet = "QLabel { ";
    currentDepthStyleSheet += "color: black; ";
    currentDepthStyleSheet += "font-size: 30px; ";

    if (_autoDepth >= 1) {
        currentDepthStyleSheet += "color: yellow; ";
    } else {
         currentDepthStyleSheet += "color: white; ";
    }
    currentDepthStyleSheet += "}";
    currentDepth->setStyleSheet(currentDepthStyleSheet);
}

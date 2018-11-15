#include "depthwidget.h"
#include <QDebug>
#include "fontsize.h"

DepthWidget::DepthWidget(QWidget *parent) : QWidget(parent)
{

}

/// @notice setups all required stylesheets and sets font-size relative to the dimensions of the window
void DepthWidget::setupStyleSheets() {

    double bigFont = FontSize::getBigFont(windowWidth);
    double smallFont = FontSize::getSmallFont(windowWidth);

    borderStyleSheet = "QFrame#depthWidget { border: ";
    borderStyleSheet += QString::number(FontSize::getBorder(windowWidth));
    borderStyleSheet += "px solid white; border-top: 0; border-left: 0; border-bottom: 0; }";

    // stylesheet for white text
    whiteText = " QLabel { color: white;  } ";
    // Stylesheet for text that should be slightly larger
    bigNumStyle = " QLabel { color: white; font-size: " + QString::number(bigFont) + "px; } ";
    // text that is slighy smaller
    numStyle = " QLabel { color: white; font-size: " + QString::number(smallFont) + "px; } ";
    // for the currentDepth and referenceDepth labels
    depthStyleSheet = "QLabel { color: white; font-size: " + QString::number(bigFont) + "px; }";
}


void DepthWidget::setupUI(QWidget * _videoPlayer, int * _windowWidth, int * _windowHeight) {
    videoPlayer = _videoPlayer;
    windowWidth = _windowWidth;
    windowHeight = _windowHeight;

    setupStyleSheets();

    int frameStartOffset = *windowHeight / 42;
    int frameStartX = *windowWidth / 100;
    int frameStartY = *windowHeight / 4 + frameStartOffset;
    frameWidth = 60;
    frameHeight = *windowHeight - (frameStartY - frameStartOffset) * 1.5;

    // create frame that acts as a container for this heading widget;
    frame = new QFrame( videoPlayer );
    frame->setObjectName("depthWidget");

    // set the position and dimensions (start x, start y, width, heigth
    frame->setGeometry(frameStartX, frameStartY, frameWidth, frameHeight);
    // add a border to the bottom
    frame->setStyleSheet( borderStyleSheet );

    // Add a label to show current depth
    currentDepth = new QLabel( QString::number(depth) , videoPlayer );
    currentDepth->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    currentDepthPos = new Position();

    currentDepthPos->width = 200;
    currentDepthPos->height = 60;
    currentDepthPos->x = frameStartX + frameWidth + currentDepthPos->width / 6 ; //position to horizontally center the widget
    currentDepthPos->y = frameStartY + frameHeight / 2 - currentDepthPos->height / 2;  // position to vertically center the widget
    setPosition(currentDepth, currentDepthPos);

    currentDepth->setStyleSheet(depthStyleSheet);

    depthReference = new QLabel( "0.0", videoPlayer );
    depthReference->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    depthReference->setStyleSheet(depthStyleSheet);
    depthReferencePos = new Position();

    depthReferencePos->width = currentDepthPos->width;
    depthReferencePos->height = currentDepthPos->height;
    depthReferencePos->x = currentDepthPos->x + 10;
    depthReferencePos->y = currentDepthPos->y;
    setPosition(depthReference, depthReferencePos);

    depthReferenceLock = new QLabel("0.0", videoPlayer );
    depthReferenceLock->setStyleSheet(depthStyleSheet);
    depthReferenceLock->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    depthReferenceLockPos = new Position();

    depthReferenceLockPos->x= depthReferencePos->x - depthReferencePos->width / 2.3;
    depthReferenceLockPos->y = depthReferencePos->y - depthReferencePos->height / 1.4;
    depthReferenceLockPos->width = depthReferencePos->width;
    depthReferenceLockPos->height = depthReferencePos->height;
    setPosition(depthReferenceLock, depthReferenceLockPos);

    QPixmap pixmapTarget = QPixmap(":/images/lock-icon.png");
    pixmapTarget = pixmapTarget.scaled(depthReferencePos->height / 2.2, depthReferencePos->height / 2.2);
    depthReferenceLock->setPixmap(pixmapTarget);

    // hide reference depth and lock icon
    depthReference->hide();
    depthReferenceLock->hide();

    // Create all the labels we need with appropiate styling
    // 200 labels because tether on ROV is max 200m
    for (int i = 0; i < 200; i++) {

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

void DepthWidget::setPosition(QLabel * _lbl, Position * _lblPos) {
    _lbl->setGeometry(_lblPos->x, _lblPos->y, _lblPos->width, _lblPos->height);
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
    currentDepth->setText(formatDepth(depth));
    updateLabels();
}

// This function will output a string with exactly one decimal
QString DepthWidget::formatDepth(double _depth) {
    QString output = "";
    // round of decimal to 1 place
    double rounded = ceil(_depth * 10) / 10;

    output = QString::number(rounded);

    // add decimal if not there
    if (floor(rounded) == rounded) {
        output += ".0";
    }

    return output;
}

void DepthWidget::updateDepthReference(double _depthRef) {
    depthRef = _depthRef;
    depthReference->setText(formatDepth(depthRef));
}

void DepthWidget::updateAutoDepth(double _autoDepth) {
    if (_autoDepth <= 0) {
        depthReference->hide();
        depthReferenceLock->hide();
    } else {
        depthReference->show();
        depthReferenceLock->show();
    }
}

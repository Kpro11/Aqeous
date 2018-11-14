#ifndef HEADINGWIDGET_H
#define HEADINGWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QList>
#include <QTimer>

#include "position.h"

class HeadingLabel {
public:
    QLabel *label;
    int value;
    QChar letter;
};

class HeadingWidget : public QWidget
{
    Q_OBJECT
public:
    HeadingWidget(QWidget *parent = nullptr);
    double yaw = 0.0;
    double yawRef = 0.0;
    int testTime = 0;

    void setupUI(QWidget * _videoPlayer, int * _windowWidth, int * _windowHeight);

public slots:
    void updateYaw(double);
    void updateLabels();
    void testUpdate();
    void updateAutoHeading(double _autoHeading);
    void updateLockPosition();
    void setPosition(QLabel * _lbl, Position * _lblPos);
    QString formatYaw(double _yaw);
    void updateYawReference(double _yaw);

private:
    QTimer * testTimer;

    QWidget * videoPlayer;

    int * windowWidth;
    int * windowHeight;

    int frameWidth;
    int frameHeight;

    QString yawStyleSheet = "QLabel { color: white; font-size: 30px; }";

    QLabel *currentYaw;
    Position *currentYawPos;

    QLabel *yawReference;
    Position *yawReferencePos;

    QLabel *yawReferenceLock;
    Position *yawReferenceLockPos;


    QFrame * frame; // main frame that contains entire widget

    QList<HeadingLabel *> labels;

    // how many pixels there are available per label
    int pixelsPerSlot;

    QString whiteText = " QLabel { color: white;  } ";   // stylesheet for white text

    QString charStyle = " QLabel { color: white; font-size: 23px; } ";
    QString numStyle = " QLabel { color: white; font-size: 17px; } ";

    QString greenText = " QLabel { color: green;  } ";   // stylesheet for green text
    QString greenCharStyle = " QLabel { color: green ; text-size: 35px; } ";
    QString greenNumStyle = " QLabel { color: dark-green; text-size: 20px; } ";

};

double distanceFromPointToYaw(double, double);

#endif // HEADINGWIDGET_H

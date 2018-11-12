#ifndef HEADINGWIDGET_H
#define HEADINGWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QList>
#include <QTimer>

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
    int testTime = 0;

    void setupUI(QWidget * _videoPlayer, int * _windowWidth, int * _windowHeight);

public slots:
    void updateYaw(double);
    void updateLabels();
    void testUpdate();
    void updateAutoHeading(double _autoDepth, double _autoHeading);

private:
    QTimer * testTimer;

    QWidget * videoPlayer;

    int * windowWidth;
    int * windowHeight;

    int frameWidth;
    int frameHeight;

    QLabel *currentYaw;

    QFrame * frame; // main frame that contains entire widget

    QList<HeadingLabel *> labels;

    QString whiteText = " QLabel { color: white;  } ";   // stylesheet for white text

    QString charStyle = " QLabel { color: white; text-size: 35px; } ";
    QString numStyle = " QLabel { color: grey; text-size: 20px; } ";

    QString greenText = " QLabel { color: green;  } ";   // stylesheet for white text
    QString greenCharStyle = " QLabel { color: green ; text-size: 35px; } ";
    QString greenNumStyle = " QLabel { color: dark-green; text-size: 20px; } ";

};

double distanceFromPointToYaw(double, double);

#endif // HEADINGWIDGET_H

#ifndef HEADINGWIDGET_H
#define HEADINGWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QList>

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

    void setupUI(QWidget * _videoPlayer, int * _windowWidth, int * _windowHeight);

public slots:
    void updateYaw(double);
private:
    QWidget * videoPlayer;

    int * windowWidth;
    int * windowHeight;

    int frameWidth;
    int frameHeight;

    QLabel *currentYaw;

    QFrame * frame; // main frame that contains entire widget

    QList<HeadingLabel *> labels;

    QString whiteText = " QLabel { color: white;  } ";   // stylesheet for white text
};

int distanceFromPointToYaw(int, int);

#endif // HEADINGWIDGET_H

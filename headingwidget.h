#ifndef HEADINGWIDGET_H
#define HEADINGWIDGET_H

#include <QWidget>
#include <QFrame>

class HeadingWidget
{
public:
    HeadingWidget(QWidget *, int *, int *);
    double yaw = 0.0;

private:
    QWidget * videoPlayer;

    int * windowWidth;
    int * windowHeight;

    QFrame * frame; // main frame that contains entire widget
    QString whiteText = " QLabel { color: white; } ";   // stylesheet for white text
};

#endif // HEADINGWIDGET_H

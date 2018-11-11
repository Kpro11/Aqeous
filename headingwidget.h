#ifndef HEADINGWIDGET_H
#define HEADINGWIDGET_H

#include <QWidget>
#include <QSlider>

class HeadingWidget
{
public:
    HeadingWidget(QWidget *, int *, int *);

private:
    QWidget * videoPlayer;

    int * windowWidth;
    int * windowHeight;

    QSlider * slider;
};

#endif // HEADINGWIDGET_H

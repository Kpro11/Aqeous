#ifndef HEADINGWIDGET_H
#define HEADINGWIDGET_H

#include <QWidget>
#include <QFrame>

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

    QFrame * frame; // main frame that contains entire widget
    QString whiteText = " QLabel { color: white; } ";   // stylesheet for white text
};

#endif // HEADINGWIDGET_H

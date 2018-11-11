#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtAV>
#include <QDebug>
#include "gamepadserver.h"
#include "tcprov.h"
#include <QObject>
#include "headingwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    TcpRov *tcpRov;
    QWidget * videoPlayer;
    HeadingWidget * headingWidget;

    int windowWidth;
    int windowHeight;

    void setupUI();


private slots:
    //void on_depth_slider_valueChanged(int value);

    void catchGamepadState(const GamepadState & gps, const int & playerId);

private:
    QtAV::VideoOutput *m_vo;
    QtAV::AVPlayer *m_player;
};

#endif // MAINWINDOW_H

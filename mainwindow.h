#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtAV>
#include <QDebug>
#include "gamepadserver.h"
#include "tcprov.h"
#include <QObject>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    TcpRov *tcpRov;
    int windowHeight;
    int windowWidth;

private slots:
    //void on_depth_slider_valueChanged(int value);
    void catchGamepadState(const GamepadState & gps, const int & playerId);

private:
    QWidget * videoPlayer;

    QtAV::VideoOutput *m_vo;
    QtAV::AVPlayer *m_player;
};

#endif // MAINWINDOW_H

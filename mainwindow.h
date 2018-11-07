#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtAV>
#include <QDebug>
#include "gamepadserver.h"
#include "tcprov.h"
#include <QObject>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    double valueI;

private slots:
    //void on_depth_slider_valueChanged(int value);
    void catchGamepadState(const GamepadState & gps, const int & playerId);

private:
    Ui::MainWindow *ui;
    QtAV::VideoOutput *m_vo;
    QtAV::AVPlayer *m_player;
    TcpRov tcprov;

};

#endif // MAINWINDOW_H

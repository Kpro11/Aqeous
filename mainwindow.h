#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtAV>
#include <QDebug>
#include "gamepadserver.h"
#include "tcprov.h"
#include <QObject>
#include "headingwidget.h"
#include "depthwidget.h"
#include "biaswidget.h"
#include "constantvalues.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    TcpRov *tcpRov;
    QWidget * videoPlayer;
    HeadingWidget * headingWidget;
    DepthWidget * depthWidget;
    BiasWidget * biasWidget;


    int windowWidth;
    int windowHeight;

    void setupUI();

signals:
    void updateDepthReference(double _depth);
    void updateYawReference(double _yaw);
    void updateAutoHeading(double _autoHeading);
    void updateAutoDepth(double _autoDepth);

private slots:
    //void on_depth_slider_valueChanged(int value);

    void catchGamepadState(const GamepadState & gps, const int & playerId);

private:
    QtAV::VideoOutput *m_vo;
    QtAV::AVPlayer *m_player;

    void checkAndHandleFlag(bool button, bool& lastKeyState, double& flag, double& reference, double referenceValue);
    void handleBiasUp(bool button, bool& lastKeyState, double& bias, double maxValue);
    void handleBiasDown(bool button, bool& lastKeyState, double& bias, double minValue);
    void autoHandling(double autoFlagOn, double& reference, double autoAdjustment, double& force, double bias, double maxValue);
};

#endif // MAINWINDOW_H

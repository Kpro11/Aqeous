#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "iwindows_xinput_wrapper.h"
#include "gamepadserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    IWindows_XInput_Wrapper * xWrapper;

protected slots:
    void catchGamepadState(const GamepadState & gps, const int & playerId);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

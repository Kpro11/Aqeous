#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "iwindows_xinput_wrapper.h"

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

public slots:

    void GetButtons(short uID, QList<XboxOneButtons> PressedButtons);
    void GetLeftTrigger(short uID, byte Value);
    void GetRightTrigger(short uID, byte Value);

    void GetLeftThumbstick(short, double x, double y);
    void GetRightThumbstick(short uID, double, double y);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

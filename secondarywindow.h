#ifndef SECONDARYWINDOW_H
#define SECONDARYWINDOW_H

#include <QMainWindow>
#include "thrustergroup.h"

namespace Ui {
class SecondaryWindow;
}

class SecondaryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondaryWindow(QWidget *parent = nullptr);
    ~SecondaryWindow();

private:
    Ui::SecondaryWindow *ui;

     ThrusterGroup *thruster_col;
};

#endif // SECONDARYWINDOW_H

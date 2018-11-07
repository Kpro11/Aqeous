#ifndef SECONDARYWINDOW_H
#define SECONDARYWINDOW_H

#include <QMainWindow>
#include "thrustergroup.h"
#include "powerstatus.h"
#include "controltester.h"

namespace Ui {
class SecondaryWindow;
}

class SecondaryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondaryWindow(QWidget *parent = nullptr);
    ~SecondaryWindow();

    /*Power status value initialization*/
    bool fkv;
    bool skv;


    /*Initializing Thruster power ouput values*/
    int t1;
    int t2;
    int t3;
    int t4;
    int t5;
    int t6;

signals:
    void connectToROV();

private slots:
    void on_openSimulator_clicked();

    void on_connectROV_clicked();

    //void on_openSim_clicked();

private:
    Ui::SecondaryWindow *ui;

     ThrusterGroup *thruster_col;

     PowerStatus *pstatus_col;

     controltester *control_tester;
};

#endif // SECONDARYWINDOW_H

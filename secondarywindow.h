#ifndef SECONDARYWINDOW_H
#define SECONDARYWINDOW_H

#include <QMainWindow>
#include "thrustergroup.h"
#include "powerstatus.h"
#include "controltester.h"
#include "stdlib.h"
#include <QLabel>
using namespace std;

namespace Ui {
class SecondaryWindow;
}

class SecondaryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondaryWindow(QWidget *parent = nullptr);
    ~SecondaryWindow();
    int PowerOutput;
    bool fPower;
    bool sPower;
    QPixmap red;
    QString textVal;




private slots:
    void changeStatusRed();
    void changeStatusYellow();
    void changeStatusGreen();
    void on_ed1_textEdited(const QString &arg1);
    QPixmap changeOnStatus();
    QPixmap changeOffStatus();


    void on_fPowStatus_toggled(bool checked);

    void on_sPowStatus_toggled(bool checked);

private:
    Ui::SecondaryWindow *ui;

     ThrusterGroup *thruster_col;

     PowerStatus *pstatus_col;

     controltester *control_tester;
};

#endif // SECONDARYWINDOW_H

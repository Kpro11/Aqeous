#include "secondarywindow.h"
#include "ui_secondarywindow.h"


SecondaryWindow::SecondaryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondaryWindow)
{
    ui->setupUi(this);
    fPower = false;
    sPower = false;


}

SecondaryWindow::~SecondaryWindow()
{
    delete ui;
}


void SecondaryWindow::on_ed1_textEdited(const QString &arg1)
{
    textVal = arg1;
    PowerOutput = textVal.toInt();

    if(PowerOutput >= 0 && PowerOutput < 50){

        changeStatusYellow();
    }
    else if(PowerOutput > 50 && PowerOutput <= 100){
        changeStatusGreen();
    }
    else{

        changeStatusRed();
    }
}


void SecondaryWindow::changeStatusGreen(){
    QPixmap green(":/images/GREEN.png");
    ui->T1->setPixmap(green);
}

void SecondaryWindow::changeStatusRed(){
    QPixmap red(":/images/RED.png");
    ui->T1->setPixmap(red);
}

void SecondaryWindow::changeStatusYellow(){
    QPixmap yellow(":/images/YELLOW.png");
    ui->T1->setPixmap(yellow);
}

QPixmap SecondaryWindow::changeOffStatus(){
    QPixmap red(":/images/RED.png");
    return red;

}
QPixmap SecondaryWindow::changeOnStatus(){
    QPixmap green(":/images/GREEN.png");
    return green;
}


void SecondaryWindow::on_fPowStatus_toggled(bool checked)
{

    if (checked){
        ui->fPower->setPixmap(changeOnStatus());
    }
    else {
        ui->fPower->setPixmap(changeOffStatus());
    }
}

void SecondaryWindow::on_sPowStatus_toggled(bool checked)
{

    if (checked){
        ui->sPower->setPixmap(changeOnStatus());
    }
    else {
        ui->sPower->setPixmap(changeOffStatus());
    }
}

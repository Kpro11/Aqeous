#include "secondarywindow.h"
#include "ui_secondarywindow.h"


SecondaryWindow::SecondaryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondaryWindow)
{
    ui->setupUi(this);

    thruster_col = new ThrusterGroup();
    pstatus_col = new PowerStatus();
    control_tester = new controltester();

    ui->thruster_status->addWidget(thruster_col);
    ui->powerstat_col->addWidget(pstatus_col);
    ui->ctester_col->addWidget(control_tester);


}

SecondaryWindow::~SecondaryWindow()
{
    delete ui;
}

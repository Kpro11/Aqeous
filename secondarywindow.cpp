#include "secondarywindow.h"
#include "ui_secondarywindow.h"
#include <QDebug>


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

void SecondaryWindow::on_openSim_clicked()
{



    qDebug("Starting the simulator");
    system("start C:/_work/FhSim/sfhdev/FhSimPlayPen_vs14_amd64/bin/tcp/runvisROV.bat && exit");
    system("start python C:/_work/FhSim/sfhdev/FhSimPlayPen_vs14_amd64/bin/tcp/tcp_rov_forces.py && exit");

    //start obs
    qDebug("Starting obs (Remember to setup obs as explained in the readme)");
    system("cd \"C:\\Program Files\\obs-studio\\bin\\64bit\" && start obs64 --profile RovSimProfile --scene RovSimScene --startrecording && exit");

    //qDebug() << returnCode;
    //qDebug() << returnCode2;
}

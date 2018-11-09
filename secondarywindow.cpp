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

void SecondaryWindow::on_openSimulator_clicked()
{
    qDebug("Starting the simulator");

    // the commands are prepended by a "start" because "start" will spawn a new process so this program doesnt halt.
    // Runs the simulator:
    system("start C:/_work/FhSim/sfhdev/FhSimPlayPen_vs14_amd64/bin/tcp/runvisRtVisROV.bat && exit");
    // Runs the python program that sends commands to the simulator. Program replaces a physical controller. This is required when not using a physical controller
    //system("start python C:/_work/FhSim/sfhdev/FhSimPlayPen_vs14_amd64/bin/tcp/tcp_rov_forces.py && exit");

    // emits signal so that we can connect to the ROV using tcp
    emit connectToROV();

    // Starts Open Brodcasting Software with the correct settings and starts recording (which is streaming in our case)
    qDebug("Starting obs (Remember to setup obs as explained in the readme)");
    system("cd \"C:\\Program Files\\obs-studio\\bin\\64bit\" && start obs64 --profile RovSimProfile --scene RovSimScene --startrecording && exit");
}

void SecondaryWindow::on_connectROV_clicked()
{
    // emits signal so that we can connect to the ROV using tcp
    emit connectToROV();
}

void SecondaryWindow::updateROVValues(double n, double e, double d, double psi) {
    qDebug() << "setting new values: " << n << e << d << psi;
    ui->north->display(n);
    ui->east->display(e);
    ui->down->display(d);
    ui->psi->display(psi);
}

#include "secondarywindow.h"
#include "ui_secondarywindow.h"
#include <QDebug>

SecondaryWindow::SecondaryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondaryWindow)
{
    ui->setupUi(this);

}

SecondaryWindow::~SecondaryWindow()
{
    delete ui;
}

void SecondaryWindow::on_openSim_clicked()
{
    int returnCode = system("start C:/_work/FhSim/sfhdev/FhSimPlayPen_vs14_amd64/bin/tcp/runvisROV.bat");
    int returnCode2 = system("start python C:/_work/FhSim/sfhdev/FhSimPlayPen_vs14_amd64/bin/tcp/tcp_rov_forces.py");

    qDebug() << returnCode;
    qDebug() << returnCode2;
}

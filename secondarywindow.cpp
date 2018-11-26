#include "secondarywindow.h"
#include "ui_secondarywindow.h"
#include <QDebug>
#include "converter.h"

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

    QPixmap pixmapTarget = QPixmap(":/images/hitramap.png");
    int w = ui->map->width() * 2.2;
    int h = ui->map->height() * 1.5;
    pixmapTarget = pixmapTarget.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->map->setPixmap(pixmapTarget);

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

    // this is the latest version which do not include the fishfarm.
    //system("start C:/_work/FhSim/sfhdev/FhSimPlayPen_vs14_amd64/bin/tcp/runrtvisROV6DOF_autoDH_thrA.bat && exit");

    // This is the latest version with fishfarm, warning this sim is pretty resource intensive
    system("start C:/_work/FhSim/sfhdev/FhSimPlayPen_vs14_amd64/bin/tcp/runrtvisROV6DOF_autoDH_thrA_fish.bat && exit");

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

void SecondaryWindow::updateROVValues(double _north, double _east, double _down, double _roll, double _pitch, double _yaw) {
    ui->north->display(_north);
    ui->east->display(_east);
    ui->down->display(_down);
    ui->roll->display(_roll);
    ui->pitch->display(_pitch);
    ui->yaw->display(_yaw);
}

/// @brief when check button "autoHeadingCheck" in ui is toggled this function is called
/// @param checked is true if checkbox was checked
void SecondaryWindow::on_autoHeadingCheck_toggled(bool checked)
{
    if (checked)
        emit updateAutoHeading(1);
    else
        emit updateAutoHeading(0);
}

/// @brief when check button "autoDepthCheck" in ui is toggled this function is called
/// @param checked is true if checkbox was checked
void SecondaryWindow::on_autoDepthCheck_toggled(bool checked)
{
    if (checked)
        emit updateAutoDepth(1);
    else
        emit updateAutoDepth(0);
}

/// @brief when user has finnished entering a value (by clicking away or pressing enter) in "autoHeadingValue" this function is called.
void SecondaryWindow::on_autoHeadingValue_editingFinished()
{
    double rad = Converter::degToRad(ui->autoHeadingValue->value());
    emit updateReferenceHeading(rad);
}

/// @brief when user has finnished entering a value (by clicking away or pressing enter) in "autoDepthValue" this function is called.
void SecondaryWindow::on_autoDepthValue_editingFinished()
{
    double rad = Converter::degToRad(ui->autoDepthValue->value());
    emit updateReferenceDepth(rad);
}

/// @brief connects to the real ROV trough serial port / sintef's backend
void SecondaryWindow::on_rovSerial_clicked()
{
    // connect to serial port
    system("start C:/_work/FhSim/sfhdev/FhSimPlayPen_vs14_amd64/bin/tcp/runrtvisrunROV_ver1.bat && exit");
}


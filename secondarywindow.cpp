#include "secondarywindow.h"
#include "ui_secondarywindow.h"

SecondaryWindow::SecondaryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondaryWindow)
{
    ui->setupUi(this);

    thruster_col = new ThrusterGroup();

    ui->thruster_status->addWidget(thruster_col);


}

SecondaryWindow::~SecondaryWindow()
{
    delete ui;
}

#include "thrustergroup.h"
#include "ui_thrustergroup.h"

ThrusterGroup::ThrusterGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThrusterGroup)
{
    ui->setupUi(this);
}

ThrusterGroup::~ThrusterGroup()
{
    delete ui;
}



#include "powerstatus.h"
#include "ui_powerstatus.h"

PowerStatus::PowerStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PowerStatus)
{
    ui->setupUi(this);
}

PowerStatus::~PowerStatus()
{
    delete ui;
}

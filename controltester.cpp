#include "controltester.h"
#include "ui_controltester.h"
#include "secondarywindow.h"

controltester::controltester(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::controltester)
{
    ui->setupUi(this);
}

controltester::~controltester()
{
    delete ui;
}



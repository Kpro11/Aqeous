#include "secondarywindow.h"
#include "ui_secondarywindow.h"

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

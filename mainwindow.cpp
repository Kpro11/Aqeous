#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include <QMessageBox>
#include <QUrl>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    xWrapper = new IWindows_XInput_Wrapper;
    xWrapper->Setup();

    connect(xWrapper, SIGNAL(ButtonPressed(short,  QList<XboxOneButtons> )), this, SLOT(GetButtons(short,  QList<XboxOneButtons> )));
    connect(xWrapper, SIGNAL(LeftThumbStick(short, double, double)), this, SLOT(GetLeftThumbstick(short, double, double)));
    connect(xWrapper, SIGNAL(RightThumbStick(short, double, double)), this, SLOT(GetRightThumbstick(short, double, double)));
    connect(xWrapper, SIGNAL(LeftTrigger(short, byte)), this, SLOT(GetLeftTrigger(short, byte)));
    connect(xWrapper, SIGNAL(RightTrigger(short, byte)), this, SLOT(GetRightTrigger(short, byte)));

    xWrapper->Start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GetButtons(short uID, QList<XboxOneButtons> PressedButtons)
{
    if (!PressedButtons.isEmpty())
        qDebug() << "userID - " << uID << "; Buttons pressed:" << PressedButtons;
}

void MainWindow::GetLeftTrigger(short uID, byte Value)
{
    if (Value > 1)
        qDebug() << "userID - " << uID << "; Left Trigger Value: " << Value;
}

void MainWindow::GetRightTrigger(short uID, byte Value)
{
    if (Value > 1)
        qDebug() << "userID - " << uID << "; Right Trigger Value: " << Value;
}

void MainWindow::GetLeftThumbstick(short uID, double x, double y)
{
    if (true)
        qDebug() << "userID - " << uID << "; Left Thumb X: " << x << ", Left Thumb Y: " << y;
}

void MainWindow::GetRightThumbstick(short uID, double x, double y)
{
    if (x != 0 || y != 0)
        qDebug() << "userID - " << uID << "; Right Thumb X: " << x << ", Right Thumb Y: " << y;
}

void MainWindow::on_pushButton_clicked()
{
    xWrapper->VibrateController(1, 30000, 0);
}

void MainWindow::on_pushButton_2_clicked()
{
    xWrapper->VibrateController(1, 0, 30000);
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include <QtAV>
#include <QtAVWidgets>
#include <QMessageBox>
#include <QUrl>
#include <QVBoxLayout>

using namespace QtAV;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_player = new AVPlayer(ui->QtAVWindow);

    m_vo = new VideoOutput(ui->QtAVWindow);
    if (!m_vo->widget()) {
       QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
       return;
    }
    m_player->setRenderer(m_vo);
    ui->QtAVWindow->addWidget(m_vo->widget());
    m_player->play("udp://224.0.0.1:9999");

    valueI = ui->depth_slider->value();

    ui->depth_counter->display(valueI);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_depth_slider_valueChanged(int value)
{

    ui->depth_counter->display(value);
}

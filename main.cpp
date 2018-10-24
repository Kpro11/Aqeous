#include "mainwindow.h"
#include "secondarywindow.h"
#include <QApplication>
#include "qdebug.h"
#include "QScreen"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    
    // 2 windows code taken from https://stackoverflow.com/questions/34551046/create-two-windows
    MainWindow w1;
    SecondaryWindow w2;

    // The following section will place and rezise the windows according to the screen setup on the host computer
    // If run on only one screen it will automaticly be placed and resized as two "small" windows with the same aspect ratio
    // - as the host's screen.
    // If run on two or more screens it will chose the two first, place the windows accordingly and make them borderless fullscreen.
    QList<QScreen *> qList = QApplication::screens();

    //Debug: lists all screens with info
    for (int i = 0; i < qList.length(); i++) {
        qDebug() << "Screen " << i << " " << qList[i]->geometry();
    }

    if (qList.length() >= 2) {
        //Both windows are made fullscreen && w1 => primarydisplay && w2 => secondary display
        w1.setWindowFlags(Qt::FramelessWindowHint);
        w1.showFullScreen();
        w2.move(qList[1]->geometry().x(), 0);
        // If we want the window to always stay on top we can use Qt::WindowStaysOnTopHint
        w2.setWindowFlags(Qt::FramelessWindowHint);
        w2.showFullScreen();
    } else {
        //There is only one screen - put the windows side by side on the same screen
        QRect  screenGeometry = qList[0]->geometry();
        int height = screenGeometry.height();
        int width = screenGeometry.width();

        w1.resize(width/2,height/2);
        w2.resize(width/2,height/2);

        //Moves the windows so they are centered and positioned correctly
        w1.move(0,0);
        w2.move(width/2,0);
    }

    w1.show();
    w2.show();

    // qDebug() << qList.length();
    // qDebug() << "Width: " << width;


    return a.exec();
}

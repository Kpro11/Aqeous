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

    //The following section will place the two windows side by side on the same window.
    //TODO Check if there is a second monitor and place the two windows on those two instead of on one screen
    //Gets the screen geometry
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    w1.resize(width/2,height/2);
    w2.resize(width/2,height/2);
    //Moves the windows so they are centered and positioned correctly
    w1.move(0,height/4);
    w2.move(width/2,height/4);

    w1.show();
    w2.show();

    // qDebug() << "Height: " << height;
    // qDebug() << "Width: " << width;


    return a.exec();
}

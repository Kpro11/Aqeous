#include "mainwindow.h"
#include "secondarywindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 2 windows code taken from https://stackoverflow.com/questions/34551046/create-two-windows
    MainWindow w1;
    SecondaryWindow w2;

    w1.show();
    w2.show();

    return a.exec();
}

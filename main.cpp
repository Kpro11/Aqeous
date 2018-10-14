#include "mainwindow.h"
#include "secondarywindow.h"
#include <QApplication>
#include "qdebug.h"
#include "QScreen"
#include "client.h"
#include <QTcpSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client client;
    QTcpSocket socket;

    socket.connectToHost("127.0.0.1", 5005);

    QObject::connect(&socket, &QTcpSocket::readyRead, [&]
        {
            //this is called when readyRead() is emitted
            qDebug() << "New data available: " << socket.bytesAvailable();
            QByteArray datas = socket.readAll();
            QString DataAsString = QTextCodec::codecForMib(106)->toUnicode(datas);
            qDebug() << DataAsString;
        });

    return a.exec();
}

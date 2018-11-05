#include "tcprov.h"
#include <QtCore>
#include <QDebug>
#include <QTcpSocket>

TcpRov::TcpRov()
{

}

void TcpRov::startTcpLoop() {
    qDebug() << "in startTcpLoop()";
    QTcpSocket socket;

    socket.connectToHost("127.0.0.1", 5005);

    QObject::connect(&socket, &QTcpSocket::readyRead, [&] {
        //this is called when readyRead() is emitted
        qDebug() << "New data available: " << socket.bytesAvailable();
        QByteArray datas = socket.readAll();
        QString DataAsString = QTextCodec::codecForMib(106)->toUnicode(datas);
        qDebug() << DataAsString;
    });

}

#include "tcprov.h"
#include <stdlib.h>
#include <thread>
#include "secondarywindow.h"
#include <QTextCodec>

TcpRov::TcpRov(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket( this );

    connect( socket, SIGNAL(readyRead()), SLOT(readTcpData()) );

    socket->connectToHost("127.0.0.1", 5000);
    if (socket->waitForConnected()) {
        qDebug("succesfully connected!");
    }
}

void TcpRov::readTcpData() {
    qDebug() << "reading data";
    qDebug() << "New data available: " << socket->bytesAvailable();
    QByteArray datas = socket->readAll();
    QString DataAsString = QTextCodec::codecForMib(106)->toUnicode(datas);
    qDebug() << DataAsString;
}

void TcpRov::tcpConnect() {
    qDebug("Trying to connect");
    socket->connectToHost("127.0.0.1", 5000);
    if (socket->waitForConnected()) {
        qDebug("succesfully connected!");
    }
}


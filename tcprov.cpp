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
    // after we recive data then send the next data.
    // this happens currently approximatly once every 0.1 seconds
    tcpSend();
}

void TcpRov::tcpConnect() {
    qDebug("Trying to connect");
    socket->connectToHost("127.0.0.1", 5000);
    if (socket->waitForConnected()) {
        qDebug("succesfully connected!");
    }
}

void TcpRov::tcpSend() {
    qDebug("Writing data");
    if(socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_11);

        out << nextN;
        out << nextE;
        out << nextD;
        out << nextPSY;

        // TOTO reset those variables here

        //qDebug() << "block" << block;
        //out.device()->seek(0);
        //qDebug() << "block" << block;
        //out << quint64(block.size() - sizeof(quint64));
        //qDebug() << "block" << block;
        QString s = QString::number(nextN);
        s = s + ":";
        socket->write(s.toUtf8());
        qDebug() << "Wrote block " << block;
    } else {
        qDebug() << "Error: not connected to tcp";
    }
}

void TcpRov::setValues(quint64 north, quint64 east, quint64 down, quint64 psi) {
    nextN = north;
    nextE = east;
    nextD = down;
    nextPSY = psi;
    tcpSend();
}

<<<<<<< HEAD
#include "tcprov.h"
#include <stdlib.h>
#include "secondarywindow.h"
#include <QTextCodec>

TcpRov::TcpRov(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket( this );

    in.setDevice(socket);
    in.setVersion(QDataStream::Qt_5_11);

    connect( socket, SIGNAL(readyRead()), SLOT(readTcpData()) );

    //socket->connectToHost("127.0.0.1", 5000);
    if (socket->waitForConnected()) {
        qDebug("succesfully connected!");
    }
}

void TcpRov::readTcpData() {
    /*
    // do this stuff here http://doc.qt.io/qt-5/qtnetwork-fortuneclient-example.html
    in.startTransaction();

    double a;
    double b;
    double c;
    double d;

    in >> a;
    in >> b;
    in >> c;
    in >> d;

    if (!in.commitTransaction()) {
        qDebug() << "Error in reading";
    }

    qDebug() << "data: " << a << b << c << d;
    */



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
    qDebug("writing data");
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

        socket->write(block);
        qDebug() << "Writed block " << block;
    } else {
        qDebug() << "Error: not connected to tcp";
    }
}
=======
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
>>>>>>> 6c7d860d3878ab0a111bebd2402ff9ef4cfb6661

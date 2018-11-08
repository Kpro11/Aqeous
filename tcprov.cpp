#include "tcprov.h"
#include <stdlib.h>
#include "secondarywindow.h"
#include <QTextCodec>

#include <QDebug>
#include <windows.h>
#include <winsock2.h>

#include <ws2tcpip.h>


TcpRov::TcpRov(QObject *parent) : QObject(parent)
{
    // TCP connection (no need to change anything here) ===================================================
    // Initialize Winsock
    WSADATA wsaData;
    int wsaError = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (wsaError != 0) {
        qDebug() << "WSAStartup failed: " << wsaError;
    }

}

void TcpRov::readTcpData() {
    //TODO implement

    // after we recive data then send the next data.
    // this happens currently approximatly once every 0.1 seconds
    tcpSend();
}

void TcpRov::tcpConnect() {
    // TODO implement
}

void TcpRov::tcpSend() {
    // todo implement further

    qDebug("writing data");
    std::string msg_buf;
    msg_buf.reserve(sizeof (nextN) + sizeof (nextE) + sizeof (nextD) + sizeof (nextPSY));

    msg_buf.append((const char*)&nextN, sizeof(nextN));
    msg_buf.append((const char*)&nextE, sizeof(nextE));
    msg_buf.append((const char*)&nextD, sizeof(nextD));
    msg_buf.append((const char*)&nextPSY, sizeof(nextPSY));
}

void TcpRov::setValues(quint64 north, quint64 east, quint64 down, quint64 psi) {
    /*
    nextN = north;
    nextE = east;
    nextD = down;
    nextPSY = psi;
    */
    tcpSend();
}

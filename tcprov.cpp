#include "tcprov.h"
#include <stdlib.h>
#include "secondarywindow.h"
#include <QTextCodec>

#include <QDebug>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

TcpRov::TcpRov(QObject *parent) : QObject(parent)
{

}

void TcpRov::readTcpData() {
    qDebug() << "Reading data";

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = 8 * recNum;

    int iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

    if (iResult > 0)
        qDebug() << "Bytes received: " << iResult;
    else if (iResult == 0)
        qDebug() << "Connection closed";
    else
        qDebug() << "recv failed with error: " << WSAGetLastError();

    memcpy(&readData.PosN, &recvbuf[0], 8);
    memcpy(&readData.PosE, &recvbuf[0 + 8 * 1], 8);
    memcpy(&readData.PosD, &recvbuf[0 + 8 * 2], 8);
    memcpy(&readData.PosPsi, &recvbuf[0 + 8 * 3], 8);

    qDebug() << "readData.PosN: " << readData.PosN << " m";
    qDebug() << "readData.PosE: " << readData.PosE << " m";
    qDebug() << "readData.PosD: " << readData.PosD << " m";
    qDebug() << "readData.PosPsi: " << readData.PosPsi << " rad";

    qDebug() << "Finnished reading data";

    // after we recive data then send the next data.
    // this happens currently approximatly once every 0.1 seconds
    tcpSend();
}

void TcpRov::tcpConnect() {
    qDebug() << "Conecting...";

    // The following code was mostly supplied by sintef, but modified sligthly on our part.

    // Initialize Winsock
    int iResult; //variable to check for errors
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        qDebug() << "WSAStartup failed: " << iResult;
    }

    struct addrinfo *result = NULL,
            *ptr = NULL,
            hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(IPString.c_str(), PortString.c_str(), &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
    }

    // Attempt to connect to the first address returned by the call to getaddrinfo
    ptr = result;

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
    }

    // call to function outside of qt scope
    winsockConnect(&ConnectSocket, ptr);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
    }

    // Should really try the next address returned by getaddrinfo if the connect call failed
    // But for this simple example we just free the resources returned by getaddrinfo and print an error message
    freeaddrinfo(result);

    qDebug() << "finnished connecting";

    // start the reading and sending loop
    readTcpData();
}

void TcpRov::tcpSend() {

    qDebug("writing data");

    runTime = (iRead + 1) * timeStep;
    qDebug () << "Sending time: " << runTime;


    // temp values
    nextN = -30.0 + 0.5 * sin(runTime*3.14159265/6.0);
    nextE = 0;
    nextD = 0.2 * runTime;
    nextPSY = 0.1 * sin(runTime*3.14159265/6.0);


    std::string msg_buf;

    // Need to reserve space
    msg_buf.reserve(sizeof(nextData));

    msg_buf.append((const char*)&nextData.ForceSurge, sizeof(nextData.ForceSurge));
    msg_buf.append((const char*)&nextData.ForceSway, sizeof(nextData.ForceSway));
    msg_buf.append((const char*)&nextData.ForceHeave, sizeof(nextData.ForceHeave));
    msg_buf.append((const char*)&nextData.ForceYaw, sizeof(nextData.ForceYaw));

    int iResult = send(ConnectSocket, &msg_buf[0], msg_buf.size(), 0);
    if (iResult == SOCKET_ERROR)
    {
        qDebug() << "Send failed with WSA error: " << WSAGetLastError();
        return;
    }
    qDebug() << "Bytes sent: " << iResult;

    iRead++;
    // Continue the loop
    readTcpData();
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

// this function is an extension of TcpRov::tcpConnect and was made because "connect" is a reserved word for QT. But this function does not inherit from QT.
void winsockConnect(SOCKET *_ConnectSocket, addrinfo *ptr) {
    // Connect to server.
    int iResult = connect(*_ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(*_ConnectSocket);
        *_ConnectSocket = INVALID_SOCKET;
    }
}

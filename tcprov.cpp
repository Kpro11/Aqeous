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
    //TODO implement

    // after we recive data then send the next data.
    // this happens currently approximatly once every 0.1 seconds
    tcpSend();
}

void TcpRov::tcpConnect() {

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

    winsockConnect(&ConnectSocket, ptr);

    // Should really try the next address returned by getaddrinfo if the connect call failed
    // But for this simple example we just free the resources returned by getaddrinfo and print an error message
    freeaddrinfo(result);
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

// this function is an extension of TcpRov::tcpConnect and was made because "connect" is a reserved word for QT. But this function does not inherit from QT.
void winsockConnect(SOCKET *_ConnectSocket, addrinfo *ptr) {
    // Connect to server.
    int iResult = connect(*_ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(*_ConnectSocket);
        *_ConnectSocket = INVALID_SOCKET;
    }

    if (*_ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
    }
}

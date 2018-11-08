#ifndef TCPROV_H
#define TCPROV_H


#include <QObject>
#include <winsock2.h>

class TcpRov : public QObject
{
    Q_OBJECT
public:
    explicit TcpRov(QObject *parent = nullptr);

    double nextN = 500;
    double nextE = 0;
    double nextD = 0;
    double nextPSY = 0;

    double tStp = 0.1;						// Communication interval
    double recNum = 4;						// Number of messages (8-byte double precision numbers) to receive
    double senNum = 4;						// Number of messages (8-byte double precision numbers) to send

    WSADATA wsaData;                        // initalize Winsock

    std::string IPString = "127.0.0.1";		// IP address of FhSim TCP server
    std::string PortString = "5000";		// Port number of FhSim TCP server

    SOCKET ConnectSocket = INVALID_SOCKET;


signals:

public slots:
    void tcpConnect();
    void readTcpData();
    void tcpSend();
    void setValues(quint64, quint64, quint64, quint64);
};

void winsockConnect(SOCKET *, addrinfo *);

#endif // TCPROV_H

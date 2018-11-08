#ifndef TCPROV_H
#define TCPROV_H


#include <QObject>
#include <winsock2.h>

#define DEFAULT_BUFLEN 1024



class TcpRov : public QObject
{
    Q_OBJECT
public:
    explicit TcpRov(QObject *parent = nullptr);

    double timeStep = 0.1;						// Communication interval
    double recNum = 4;						// Number of messages (8-byte double precision numbers) to receive
    double senNum = 4;						// Number of messages (8-byte double precision numbers) to send

    WSADATA wsaData;                        // initalize Winsock

    std::string IPString = "127.0.0.1";		// IP address of FhSim TCP server
    std::string PortString = "5000";		// Port number of FhSim TCP server

    SOCKET ConnectSocket = INVALID_SOCKET;

    int iRead = 0;                          // how many times have we read data?
    double runTime;                         // how long has the tcp connection lasted

    std::string msg_buf;

    // Data structure to receive from FhSim
    class TCPVessel {
        public:
            double PosN = 0.0;
            double PosE = 0.0;
            double PosD = 0.0;
            double PosPsi = 0.0;
    };

    // Data structure to send to FhSim
    class TCPThruster {
        public:
            double ForceSurge = 500.0;
            double ForceSway = 0.0;
            double ForceHeave = 0.0;
            double ForceYaw = 0.0;
    };

    TCPVessel readData;					// Data to receive from FhSim
    TCPThruster nextData;               // Data to send to FhSim

signals:

public slots:
    void tcpConnect();
    void tcpRead();
    void tcpSend();
    void setValues(quint64, quint64, quint64, quint64);
    void resetValues();
};

void winsockConnect(SOCKET *, addrinfo *);



#endif // TCPROV_H

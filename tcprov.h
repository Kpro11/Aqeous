#ifndef TCPROV_H
#define TCPROV_H

#include <QObject>
#include <winsock2.h>
#include <QTimer>

#define DEFAULT_BUFLEN 1024
#define PI 3.14159265359

class TcpRov : public QObject
{
    Q_OBJECT
public:
    explicit TcpRov(QObject *parent = nullptr);

    QTimer *tcpReadTimer;
    //QTimer *tcpConnectTimer;

    double timeStep = 0.1;					// Communication interval
    double recNum = 4;						// Number of messages (8-byte double precision numbers) to receive
    double senNum = 4;						// Number of messages (8-byte double precision numbers) to send

    double autoDepth = 0;
    double autoHeading = 0;
    double referenceDepth = 0;
    double referenceHeading = 0;

    double biasSurge = 0;
    double biasSway = 0;
    double biasHeave = 0;


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
            double north = 0.0;
            double east = 0.0;
            double down = 0.0;
            double roll = 0.0;
            double pitch = 0.0;
            double yaw = 0.0;
    };

    // Data structure to send to FhSim
    class TCPThruster {
        public:
            double surge= 500.0;
            double sway = 0.0;
            double heave = 0.0; // reference depth when AutoDepth == 1
            double roll = 0.0;  // not implemented in simulator at the moment
            double pitch = 0.0; // not implemented in simulator at the moment
            double yaw = 0.0;   // reference heading when AutoHeading = 1
            // uncomment when new simulator supports it
            double autoDepth = 0.0;     // boolean dooble :) 0 for off or 1 for on
            double autoHeading = 0.0;   // 0 for off, 1 for on
    };

    TCPVessel readData;					// Data to receive from FhSim
    TCPThruster nextData;               // Data to send to FhSim

signals:
    void updateROVValues(double, double, double, double, double, double);
    void updateYaw(double);
    void updateDepth(double);
    void updateFlags(double, double);
    void updateBias(double, double, double);

public slots:
    void tcpConnect();
    void tcpRead();
    void tcpSend();
    void setValues(double, double, double, double);
    void setValues(double, double, double, double, double, double);
    void setValues(double, double, double, double, double, double, double, double);
    void resetAllValues();
    void resetValuesButNotFlagValues();
    void startTcpReadTimer();
    void stopTcpReadTimer();
    void toggleAutoDepth();
    void toggleAutoHeading();

};




void winsockConnect(SOCKET *, addrinfo *);



#endif // TCPROV_H

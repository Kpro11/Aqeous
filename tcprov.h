#ifndef TCPROV_H
#define TCPROV_H


//#include <winsock2.h>

#include <QObject>


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
//    WSADATA wsaData;                        // initalize Winsock

signals:

public slots:
    void tcpConnect();
    void readTcpData();
    void tcpSend();
    void setValues(quint64, quint64, quint64, quint64);
};

#endif // TCPROV_H

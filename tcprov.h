#ifndef TCPROV_H
#define TCPROV_H

#include <QObject>
#include <QTcpSocket>

class TcpRov : public QObject
{
    Q_OBJECT
public:
    explicit TcpRov(QObject *parent = nullptr);
    QTcpSocket *socket;



signals:

public slots:
    void tcpConnect();
    void readTcpData();
};

#endif // TCPROV_H

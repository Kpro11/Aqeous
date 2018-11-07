#ifndef TCPROV_H
#define TCPROV_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

class TcpRov : public QObject
{
    Q_OBJECT
public:
    explicit TcpRov(QObject *parent = nullptr);
    QTcpSocket *socket;

    quint64 nextN = 500;
    quint64 nextE = 0;
    quint64 nextD = 0;
    quint64 nextPSY = 0;

    QDataStream in;


signals:

public slots:
    void tcpConnect();
    void readTcpData();
    void tcpSend();

};

#endif // TCPROV_H

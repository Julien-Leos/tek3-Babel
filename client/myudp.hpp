// myudp.h

#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>
#include <opus.h>
#include "portaudio.h"
#include <iostream>
#include <string>


class MyUDP : public QObject
{
    Q_OBJECT
public:
    explicit MyUDP(QString ip, qint16 port, QString targetIp, qint16 targetPort, QObject *parent = 0);
    void HelloUDP(const char *buffer, int size);
    void setStream(PaStream *stream){_stream = stream;}
signals:
    
public slots:
    void readyRead();

private:
    QUdpSocket *socket;
    QHostAddress _address;
    qint16 _port;
    PaStream *_stream;
};

#endif // MYUDP_H
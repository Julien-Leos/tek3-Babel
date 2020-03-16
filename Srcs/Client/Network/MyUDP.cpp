/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** MyUDP
*/

#include "MyUDP.hpp"

#include "../Audio/Audio.hpp"

namespace babel {
    MyUDP::MyUDP(std::shared_ptr<Audio> audio, QString ip, qint16 port, QString targetIp, qint16 targetPort, QObject *parent) :
        QObject(parent)
    {
        QHostAddress local(ip);

        _audio = audio;
        _socket = new QUdpSocket(this);
        _address = QHostAddress(targetIp);
        _port = targetPort;
        _buffer = (char*)malloc(4 + MAX_PACKET_SIZE);

        _socket->bind(local, port);
        connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    }

    void    MyUDP::HelloUDP(const char *buffer, int size)
    {
        _socket->writeDatagram(buffer, size, _address, _port);
    }

    void    MyUDP::readyRead()
    {
        QHostAddress sender;
        quint16 senderPort;
        
        memset(_buffer, 0, 4 + MAX_PACKET_SIZE);
        _socket->readDatagram(_buffer, 4 + MAX_PACKET_SIZE, &sender, &senderPort);
        
        _audio->write(_buffer);
    }

    char *  MyUDP::getBuffer(void) const
    {
        return (_buffer);
    }
}

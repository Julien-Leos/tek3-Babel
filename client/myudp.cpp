// myudp.cpp

#include "myudp.hpp"
 #include <iostream>
 
#include <chrono>
#include <thread>

#define CHANNELS 2
#define MAX_FRAME_SIZE 6*960
#define MAX_PACKET_SIZE (3*1276)
#define FRAMES_PER_BUFFER   (960)
#define SAMPLE_RATE       (48000)


MyUDP::MyUDP(QString ip, qint16 port, QString targetIp, qint16 targetPort, QObject *parent) :
    QObject(parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);
    
    // The most common way to use QUdpSocket class is 
    // to bind to an address and port using bind()
    // bool QAbstractSocket::bind(const QHostAddress & address, 
    //     quint16 port = 0, BindMode mode = DefaultForPlatform)
    QHostAddress local(ip);
    _address = QHostAddress(targetIp);
    _port = targetPort;
    socket->bind(local, port);
    
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MyUDP::HelloUDP(const char *buffer, int size)
{
    // Sends the datagram datagram 
    // to the host address and at port.
    // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram, 
    //                      const QHostAddress & host, quint16 port)
    socket->writeDatagram(buffer, size, _address, _port);
}

void MyUDP::readyRead()
{
    // when data comes in
    // QByteArray buffer;
    // buffer.resize(socket->pendingDatagramSize());
    
    QHostAddress sender;
    quint16 senderPort;
    
    char *buffer = (char*)malloc(4 + MAX_PACKET_SIZE);
    memset(buffer, 0, 4 + MAX_PACKET_SIZE);
    socket->readDatagram(buffer, 4 + MAX_PACKET_SIZE,
                         &sender, &senderPort);
    PaError err;
    OpusDecoder *decoder;
    decoder = opus_decoder_create(SAMPLE_RATE, CHANNELS, &err);
    int frame_size;
    int *nbBytes = (int*)buffer;
    unsigned char *cbits = (unsigned char*)(buffer + 4);
    opus_int16 out[MAX_FRAME_SIZE*CHANNELS] = {0};
    static int i = 0;
    frame_size = opus_decode(decoder, cbits, *nbBytes, out, MAX_FRAME_SIZE, 0);
    std::cout << *nbBytes << "  write " << ++i << std::endl;
    err = Pa_WriteStream( _stream, (char*)out, FRAMES_PER_BUFFER);
    
}
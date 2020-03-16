#include <QtWidgets>
#include "myudp.hpp"
#include <QNetworkInterface>
#include "mythread.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (argc < 4)
        std::cout << "Need your port and target ip and port" << std::endl;


    QString ip;    
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    for(int nIter=0; nIter<list.count(); nIter++) {
        if(!list[nIter].isLoopback()) {
            if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol)
                ip = QString(list[nIter].toString());
        }
    }
    qint16 port = atoi(argv[1]);
    QString targetIp(argv[2]);
    qint16 targetPort = atoi(argv[3]);
    MyUDP client(ip, port, targetIp, targetPort);
    MyThread thread1(client);
    thread1.start();
    return app.exec();

}

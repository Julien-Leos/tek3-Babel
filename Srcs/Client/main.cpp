/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** main
*/

#include "Includes.hpp"

#include "Audio/Audio.hpp"
#include "Network/MyThread.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto audio = std::make_shared<babel::Audio>();

    if (argc < 4) {
        std::cout << "Need your port and target ip and port" << std::endl;
        exit(84);
    }

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

    auto client = std::make_shared<babel::MyUDP>(audio, ip, port, targetIp, targetPort);
    babel::MyThread thread(audio, client);
    thread.start();
    return app.exec();
}
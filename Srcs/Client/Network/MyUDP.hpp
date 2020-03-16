/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** MyUDP
*/

#ifndef MYUDP_HPP_
#define MYUDP_HPP_

#include "../Includes.hpp"

namespace babel {
    class Audio;

    class MyUDP : public QObject {
            Q_OBJECT
        public:
            explicit MyUDP(std::shared_ptr<Audio> audio, QString ip, qint16 port, QString targetIp, qint16 targetPort, QObject *parent = 0);
            
            void    HelloUDP(const char *buffer, int size);

            char *  getBuffer(void) const;
        signals:
            
        public slots:
            void    readyRead();

        private:
            std::shared_ptr<Audio>  _audio;

            char *          _buffer;
            QUdpSocket *    _socket;
            QHostAddress    _address;
            qint16          _port;
    };
}

#endif /* !MYUDP_HPP_ */

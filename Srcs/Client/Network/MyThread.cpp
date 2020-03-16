/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** MyThread
*/

#include "MyThread.hpp"

namespace babel {
    MyThread::MyThread(std::shared_ptr<Audio> audio, std::shared_ptr<MyUDP> client)
    {
        _audio = audio;
        _client = client;
    }

    void    MyThread::run()
    {
        _audio->init();
        _audio->read(_client->getBuffer(), _client);
        _audio->close();
    }
}

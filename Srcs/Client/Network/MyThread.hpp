/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** MyThread
*/

#ifndef MYTHREAD_HPP_
#define MYTHREAD_HPP_

#include "../Includes.hpp"

#include "../Audio/Audio.hpp"
#include "MyUDP.hpp"

namespace babel {
    // class Audio;

    class MyThread : public QThread {
        public:
            explicit MyThread(std::shared_ptr<Audio> audio, std::shared_ptr<MyUDP> client);

            void run();

        private:
            std::shared_ptr<Audio>  _audio;
            std::shared_ptr<MyUDP> _client;
    };
}

#endif /* !MYTHREAD_HPP_ */

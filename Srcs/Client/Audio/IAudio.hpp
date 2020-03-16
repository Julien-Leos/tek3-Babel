/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** IAudio
*/

#ifndef IAUDIO_HPP_
#define IAUDIO_HPP_

#include "../Includes.hpp"

namespace babel {
    class MyUDP;

    class IAudio {
        public:
            virtual ~IAudio() = default;

            virtual void    init(void) = 0;
            virtual void    close(void) = 0;

            virtual void    read(char * buffer, std::shared_ptr<MyUDP> client) = 0;
            virtual void    write(char * buffer) = 0;
    };
}

#endif /* !IAUDIO_HPP_ */

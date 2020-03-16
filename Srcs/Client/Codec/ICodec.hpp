/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** ICodec
*/

#ifndef ICODEC_HPP_
#define ICODEC_HPP_

#include "../Includes.hpp"

namespace babel {
    class ICodec {
        public:
            virtual ~ICodec() = default;

            virtual int     encode(unsigned char * cbits, char * dataInput) = 0;
            virtual int     decode(unsigned char * cbits, char * dataOutput, int nbBytes) = 0;
    };
}

#endif /* !ICODEC_HPP_ */

/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include "IAudio.hpp"

#include "../Codec/Codec.hpp"
#include "../Network/MyUDP.hpp"

namespace babel {
    #define FRAME_SIZE          960
    #define NUM_CHANNELS        2
    #define MAX_FRAME_SIZE      (6 * 960)

    #define FRAMES_PER_BUFFER   960
    #define SAMPLE_RATE         48000

    #define PA_SAMPLE_TYPE      paInt16

    struct Stream //VERIFIER SI L'ABSTRACTION EST TOUJOURS VALIDE
    {
        PaStream *stream;
        const PaDeviceInfo *info;
        PaStreamParameters params;
    };

    class Audio : public IAudio {
        public:
            Audio();
            ~Audio();

            void    init(void);
            void    close(void);

            void    read(char * buffer, std::shared_ptr<MyUDP> client);
            void    write(char * buffer);

        private:
            Stream *    _input;
            Stream *    _output;
            
            Codec       _codec;
            PaError     _error;
    };
}


#endif /* !AUDIO_HPP_ */

#include "mythread.hpp"
#include <QDebug>
#include "myudp.hpp"
 #include <stdio.h>
 #include <cstdlib>
 #include <string>
 #include <fstream>
 #include "portaudio.h"
  
#include <chrono>
#include <thread>
 #include <opus.h>
 
 /* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define FRAME_SIZE 960
#define CHANNELS 2
#define MAX_FRAME_SIZE 6*960
#define APPLICATION OPUS_APPLICATION_VOIP
#define BITRATE 64000
#define MAX_PACKET_SIZE (3*1276)

 
 #define SAMPLE_RATE       (48000)
 #define FRAMES_PER_BUFFER   (960)
 #define NUM_SECONDS          (10)
 /* #define DITHER_FLAG     (paDitherOff)  */
 #define DITHER_FLAG           (0)
 
 /* Select sample format. */
 #if 0
 #define PA_SAMPLE_TYPE  paFloat32
 #define SAMPLE_SIZE (4)
 #define SAMPLE_SILENCE  (0.0f)
 #define PRINTF_S_FORMAT "%.8f"
 #elif 1
 #define PA_SAMPLE_TYPE  paInt16
 #define SAMPLE_SIZE (2)
 #define SAMPLE_SILENCE  (0)
 #define PRINTF_S_FORMAT "%d"
 #elif 0
 #endif

MyThread::MyThread(MyUDP &client) : client(client)
{
}

// We overrides the QThread's run() method here
// run() will be called when a thread starts
// the code will be shared by all threads

void MyThread::run()
{
    PaStreamParameters inputParameters, outputParameters;
     PaStream *streamin = NULL;
     PaStream *streamout = NULL;
     PaError err;
     const PaDeviceInfo* inputInfo;
     const PaDeviceInfo* outputInfo;
     char *sampleBlock = NULL;
     int i;
     int numBytes;
     int numChannels;

     printf("patest_read_write_wire.c\n"); fflush(stdout);
     printf("sizeof(int) = %lu\n", sizeof(int)); fflush(stdout);
     printf("sizeof(long) = %lu\n", sizeof(long)); fflush(stdout);
 
     err = Pa_Initialize();
     if( err != paNoError ) 
            return;
 
     inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
     printf( "Input device # %d.\n", inputParameters.device );
     inputInfo = Pa_GetDeviceInfo( inputParameters.device );
     printf( "    Name: %s\n", inputInfo->name );
     printf( "      LL: %g s\n", inputInfo->defaultLowInputLatency );
     printf( "      HL: %g s\n", inputInfo->defaultHighInputLatency );
 
     outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
     printf( "Output device # %d.\n", outputParameters.device );
     outputInfo = Pa_GetDeviceInfo( outputParameters.device );
     printf( "   Name: %s\n", outputInfo->name );
     printf( "     LL: %g s\n", outputInfo->defaultLowOutputLatency );
     printf( "     HL: %g s\n", outputInfo->defaultHighOutputLatency );
 
     numChannels = inputInfo->maxInputChannels < outputInfo->maxOutputChannels
             ? inputInfo->maxInputChannels : outputInfo->maxOutputChannels;

      numChannels = 2; ///////////////////////////////////////////////////////////////////////


     printf( "Num channels = %d.\n", numChannels );
 
     inputParameters.channelCount = numChannels;
     inputParameters.sampleFormat = PA_SAMPLE_TYPE;
     inputParameters.suggestedLatency = inputInfo->defaultHighInputLatency ;
     inputParameters.hostApiSpecificStreamInfo = NULL;
 
     outputParameters.channelCount = numChannels;
     outputParameters.sampleFormat = PA_SAMPLE_TYPE;
     outputParameters.suggestedLatency = outputInfo->defaultHighOutputLatency;
     outputParameters.hostApiSpecificStreamInfo = NULL;
 
     /* -- setup -- */
 
     err = Pa_OpenStream(
               &streamin,
               &inputParameters,
               nullptr,
               SAMPLE_RATE,
               FRAMES_PER_BUFFER,
               paClipOff,      /* we won't output out of range samples so don't bother clipping them */
               NULL, /* no callback, use blocking API */
               NULL ); /* no callback, so no callback userData */
     if( err != paNoError ) 
            return;

        err = Pa_OpenStream(
               &streamout,
               nullptr,
               &outputParameters,
               SAMPLE_RATE,
               FRAMES_PER_BUFFER,
               paClipOff,      /* we won't output out of range samples so don't bother clipping them */
               NULL, /* no callback, use blocking API */
               NULL ); /* no callback, so no callback userData */
     if( err != paNoError ) 
            return;
 
     numBytes = FRAMES_PER_BUFFER * numChannels * SAMPLE_SIZE ;
     sampleBlock = (char *) malloc( numBytes );
     if( sampleBlock == NULL )
     {
         printf("Could not allocate record array.\n");
                return;
     }
     memset( sampleBlock, SAMPLE_SILENCE, numBytes );
 
     err = Pa_StartStream( streamin);
     err = Pa_StartStream( streamout);
     if( err != paNoError ) 
            return;
     printf("Wire on. Will run %d seconds.\n", NUM_SECONDS); fflush(stdout);
    
    
    client.setStream(streamout);

   opus_int16 in[FRAME_SIZE*CHANNELS];
    opus_int16 out[MAX_FRAME_SIZE*CHANNELS] = {0};

   char *buffer = (char*)malloc(4 + MAX_PACKET_SIZE);
    memset(buffer, 0, 4 + MAX_PACKET_SIZE);
    OpusDecoder *decoder;
    decoder = opus_decoder_create(SAMPLE_RATE, CHANNELS, &err);
    int frame_size;

   unsigned char *cbits = (unsigned char*)(buffer + 4);
   int *nbBytes = (int*)buffer;
   int error;
   int j = 0;
   
   OpusEncoder *encoder;
   encoder = opus_encoder_create(SAMPLE_RATE, CHANNELS, APPLICATION, &err);
   error = opus_encoder_ctl(encoder, OPUS_SET_BITRATE(BITRATE));

   for(int i=0; i == 0; i += 0) {
       std::cout << "read" << std::endl;
      err = Pa_ReadStream( streamin, (char*)in, FRAMES_PER_BUFFER);
      *nbBytes = opus_encode(encoder, in, FRAME_SIZE, cbits, MAX_PACKET_SIZE);
      std::cout << *nbBytes << " " << ++j << std::endl;
    //   frame_size = opus_decode(decoder, cbits, *nbBytes, out, MAX_FRAME_SIZE, 0);
    client.HelloUDP(buffer, *nbBytes + 4);
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // std::cout << frame_size << std::endl;
    // err = Pa_WriteStream( streamout, (char*)out, FRAMES_PER_BUFFER);
   }

     printf("Wire off.\n"); fflush(stdout);
 
     err = Pa_StopStream( streamin );
     err = Pa_StopStream( streamout );
     if( err != paNoError ) 
            return;
 
     free( sampleBlock );
 
     Pa_Terminate();
     return;
 
 xrun:
     printf("err = %d\n", err); fflush(stdout);
     if( streamin ) {
        Pa_AbortStream( streamin );
        Pa_CloseStream( streamin );
     }
    if( out ) {
        Pa_AbortStream( out );
        Pa_CloseStream( out );
     }
     free( sampleBlock );
     Pa_Terminate();
     if( err & paInputOverflow )
        fprintf( stderr, "Input Overflow.\n" );
     if( err & paOutputUnderflow )
        fprintf( stderr, "Output Underflow.\n" );
     return;
 error1:
     free( sampleBlock );
 error2:
     if( streamin ) {
        Pa_AbortStream( streamin );
        Pa_CloseStream( streamin );
     }
     Pa_Terminate();
     fprintf( stderr, "An error occured while using the portaudio stream\n" );
     fprintf( stderr, "Error number: %d\n", err );
     fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
     return;
    // client.HelloUDP(message);
}
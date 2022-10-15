#include <stdio.h>
#include <portaudio.h>
#include "../structure.h"


typedef struct {
    float *leftChanel;
    float *rightChanel;
    soundFormat format; //audio format
    unsigned int frame; //current playhead position
    unsigned int sample;
} paCallbackData;


PaStream *stream;
paCallbackData paData;
PaTime startTime;


int pacallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
    paCallbackData *inData = (paCallbackData*)userData;
    float *out = (float*)outputBuffer;

    for(int i = 0; i < framesPerBuffer; i++) {
        inData->sample++;
        *out++ = inData->leftChanel[inData->sample];
        *out++ = inData->rightChanel[inData->sample];
    }
    return 0;
}


int initPa(soundFormat format) {
    PaError err;
    //intitiate portaudio
    err = Pa_Initialize();
    if(err != paNoError) {goto error;}
    printf("portaudio initiated\n");
    paData.format = format;
    int chanels = 1;
    if(format.stereo == 1) chanels = 2;

    //open main audio stream
    err = Pa_OpenDefaultStream(&stream, 0, chanels, paFloat32, format.sampleRate, format.frameSize, pacallback, &paData);
    if(err != paNoError) {goto error;}
    printf("stream opened\n");

    return 1;

error:
    printf("initialization error ocured!\n portaudio error: %s\n", Pa_GetErrorText(err));
    return 0;
}


int terminatePa() {
    PaError err;
    //close the stream
    err = Pa_CloseStream(stream);
    if(err != paNoError) {goto error;}
    printf("stream closed \n");

    //terminate portaudio
    err = Pa_Terminate();
    if(err != paNoError) {goto error;}
    printf("terminated\n");

    return 1;

 error:
    printf("termination error ocured!\n portaudio error: %s\n", Pa_GetErrorText(err));
    return 0;
}


int getCurrentSample() {
    return paData.sample;
}


int getCurrentPlaybackTime() {
    return Pa_GetStreamTime(stream) - startTime;
}


int startPlayBack(unsigned int sample) {
    PaError err;
    paData.sample = sample;
    err = Pa_StartStream(stream);
    if(err != paNoError) {goto error;}
    startTime = Pa_GetStreamTime(stream);

    return 1;

 error:
    printf("play back start error ocured!\n portaudio error: %s\n", Pa_GetErrorText(err));
    return 0;
}


int stopPlayBack() {
    PaError err;
    err = Pa_StopStream(stream);
    if(err != paNoError) {goto error;}

    return 1;

 error:
    printf("play back stop error ocured!\n portaudio error: %s\n", Pa_GetErrorText(err));
    return 0;
}


int setTracks(float *leftChanel, float *rightChanel) {
    paData.leftChanel = leftChanel;
    paData.rightChanel = rightChanel;
    return 1;
}

#include <stdio.h>
#include <portaudio.h>
#include <math.h>
#include "./math/audioMath.h"
#include "./math/computer.h"

#define SAMPLE_RATE (44100)
#define PI (3.14159256)
#define BUFFER_SIZE (512)


typedef struct {
    struct trackData *data; //audio tracks
    soundFormat format; //audio format
    unsigned int frame; //current playhead position
    unsigned int sample;
    int tracks; //the amount of tracks the mixer has to combine
} paCallbackData;


int pacallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
    paCallbackData *inData = (paCallbackData*)userData;
    float *out = (float*)outputBuffer;

    for(int i = 0; i < framesPerBuffer; i++) {
        inData->sample++;
        float leftChanel = 0.0;
        float rightChanel = 0.0;
        for(int track = 0; track < inData->tracks; track++) { //combine all tracks
            leftChanel += 
                inData->data[track].audio[inData->sample] * 
                inData->data[track].level;
            rightChanel += inData->data[track].audio[inData->sample] * inData->data[track].level;
        }
        //normalize output to not make speekers go kaboom
        *out++ = leftChanel / inData->tracks;
        *out++ = rightChanel / inData->tracks;
   }
   return 0;
}


int main() {
    //intitiate portaudio
    PaError err;
    err = Pa_Initialize();
    if(err != paNoError) {goto error;}


    soundFormat format;
    format.frameSize = SAMPLE_RATE;
    format.sampleRate = SAMPLE_RATE;
    format.stereo = 1;

    float temp = 400.0;
    instruction inst[4];
    inst[0].type = 0; inst[0].ID=4;
    inst[1].type = 1; inst[1].data.f=&temp;
    inst[2].type = 0; inst[2].ID=3;
    inst[3].type = 0; inst[3].ID=2;
    inst[4].type = 0; inst[4].ID=5;

    float *test = computeSoundData(inst, 4, format, 0, 5);

    //temporary testing code
    struct trackData tracks[1];
    struct trackData track0 = {0, 0.05, test};
    tracks[0] = track0;

    paCallbackData paData;
    paData.data = tracks;
    paData.tracks = 1;

    //intitiate portaudio stream
    PaStream *stream;
    err = Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, SAMPLE_RATE, BUFFER_SIZE, pacallback, &paData);
    if(err != paNoError) {goto error;}

    //start playing the stream
    err = Pa_StartStream(stream);
    if(err != paNoError) {goto error;}
    printf("playing sound!\n");
    PaTime starttime = Pa_GetStreamTime(stream);

    while (1) {
    PaTime time = Pa_GetStreamTime(stream);
    if(time-starttime >= 5) {break;}
    }

    //stop the stream
    err = Pa_StopStream(stream);
    if(err != paNoError) {goto error;}
    printf("stoping\n");

    //close the stream
    err = Pa_CloseStream(stream);
    if(err != paNoError) {goto error;}
    printf("stream closed \n");

    //terminate portaudio
    err = Pa_Terminate();
    if(err != paNoError) {goto error;}
    printf("terminated\n");

    return 0;

error:
    printf("somethn fucked up...\n");
    printf("PortAudio error: %s\n", Pa_GetErrorText(err));
    return 0;
}

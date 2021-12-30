#include <stdio.h>
#include <portaudio.h>
#include <math.h>

#define SAMPLE_RATE (44100)
#define PI (3.14159256)


double samples = 0;

typedef struct {
    float left_phase;
    float right_phase;
} paTestData;


static paTestData data;


int pacallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData){
    paTestData *data = (paTestData*)userData;  
    float *out = (float*)outputBuffer;
    (void) inputBuffer; //Prevent unused variable warning.
    unsigned int i;
    
    for(i=0; i<framesPerBuffer; i++) {
    samples++;
    data->left_phase = sin((samples/44100)*50*sin(samples/441)*PI*2);
    data->right_phase = sin((samples/44100)*50*sin(samples/441)*PI*2);
    *out++ = data->left_phase;
    *out++ = data->right_phase;
   }

    return 0;
}


int main () {
    PaError err;
    //intitiates portaudio
    printf("starting\n");
    err = Pa_Initialize();
    if(err != paNoError) goto error;
    printf("initiated!\n");
    
    PaStream *stream;
    //intitiates portaudio stream
    err = Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, SAMPLE_RATE, 256, pacallback, &data);
    if(err != paNoError) goto error;
    printf("stream initiated!\n");

    //starts playing the stream
    err = Pa_StartStream(stream);
    if(err != paNoError) goto error;
    printf("playing sound!\n");

    Pa_Sleep(5000);

    //stops the stream
    err = Pa_StopStream(stream);
    if(err != paNoError) goto error;
    printf("stoping\n");

    //closes the stream
    err = Pa_CloseStream(stream);
    if(err != paNoError) goto error;
    printf("stream closed \n");

    //terminates portaudio
    err = Pa_Terminate();
    if(err != paNoError) goto error;
    printf("terminated\n");

    return 0;

error:
    printf("somethn fucked up...\n");
    printf("PortAudio error: %s\n", Pa_GetErrorText(err));

}

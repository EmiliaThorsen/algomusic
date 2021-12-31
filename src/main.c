#include <stdio.h>
#include <portaudio.h>
#include <math.h>


#define SAMPLE_RATE (44100)
#define PI (3.14159256)
#define BUFFER_SIZE (512)


typedef struct {
    int trackID;
    float trackLevel;
    float *data;
} TrackSoundData;


typedef struct {
    TrackSoundData *tracks;
    unsigned long int frame;
} paCallbackData;


int pacallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData){
    paCallbackData *data = (paCallbackData*)userData;  
    float *out = (float*)outputBuffer;
    unsigned int i;
    
    for(i=0; i<framesPerBuffer; i++) {
    data->frame++;
    *out++ = data->tracks->data[data->frame];
    *out++ = data->tracks->data[data->frame];
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
    
    float frame = 0.0;
    float track0data[220500];
    for (int i=0; i<220500; i++) {
        frame++;
        track0data[i] = sin((frame/44100)*800);
    }
       
    TrackSoundData track = {1, 1.0, track0data};
    paCallbackData data; 
    data.tracks = &track;

    PaStream *stream;
    //intitiates portaudio stream
    err = Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, SAMPLE_RATE, BUFFER_SIZE, pacallback, &data);
    if(err != paNoError) goto error;
    printf("stream initiated!\n");

    //starts playing the stream
    err = Pa_StartStream(stream);
    if(err != paNoError) goto error;
    printf("playing sound!\n");
    PaTime starttime = Pa_GetStreamTime(stream);

    while (1) {
    PaTime time = Pa_GetStreamTime(stream);
    if(time-starttime >= 5) break;
    }

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

#include <stdio.h>
#include <portaudio.h>
#include <math.h>


#define SAMPLE_RATE (44100)
#define PI (3.14159256)
#define BUFFER_SIZE (512)


//the data structure for the calculated audio track data
typedef struct {
    int trackID; //id of the track
    float trackLevel; //the mixer level of the track
    float *data; //audio data of the track
} TrackSoundData;


//the data passed into pacallback
typedef struct {
    TrackSoundData *data; //array of audio data tracks
    unsigned long int frame; //the frame in the audio tracks the player is in
    int tracks; //the amount of tracks the mixer has to combine
} paCallbackData;


int pacallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData){
    paCallbackData *data = (paCallbackData*)userData;  
    float *out = (float*)outputBuffer;
    
    for(int i=0; i<framesPerBuffer; i++) {
        data->frame++;

        float leftChanel = 0.0;
        float rightChanel = 0.0;
        for(int track=0; track<data->tracks; track++){
            leftChanel += data->data[track].data[data->frame]*data->data[track].trackLevel;
            rightChanel += data->data[track].data[data->frame]*data->data[track].trackLevel;
        }

        *out++ = leftChanel/data->tracks;
        *out++ = rightChanel/data->tracks;
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
    float track1data[220500];
    for (int i=0; i<220500; i++) {
        frame++;
        track0data[i] = sin((frame/44100)*1600);
        track1data[i] = sin((frame/44100)*3200);
    }

    TrackSoundData track0 = {0, 1.0, track0data};
    TrackSoundData track1 = {1, 1.0, track1data};

    TrackSoundData tracks[2];
    tracks[0] = track0;
    tracks[1] = track1;

    paCallbackData data; 
    data.data = tracks;
    data.tracks = 2;

    //intitiates portaudio stream
    PaStream *stream;
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

#include "stdlib.h"
#include "../structure.h"
#include "./playBack.h"
#include <stdio.h>

struct track {
    int id;
    float *dataL;
    float *dataR;
    float level;
    int samples;
};


struct track **trackData;
int tracks;
int trackBufferSize;
int usedIds;

float *mainTrackLeft;
float *mainTrackRight;
int outSamples;


void initMixer() {
    tracks = 0;
    usedIds = 0;
    trackBufferSize = 1;
    trackData = malloc(sizeof(struct track *));
    mainTrackLeft = malloc(sizeof(float));
    mainTrackRight = malloc(sizeof(float));
}


void setOutTrackSize(int samples) {
    outSamples = samples;
    mainTrackLeft = realloc(mainTrackLeft, sizeof(float) * samples);
    mainTrackRight = realloc(mainTrackRight, sizeof(float) * samples);
}


void _combineTracks() {
    printf("%i", tracks);
    for(int track = 0; track < tracks; track++) {
        float level = trackData[track]->level / tracks;
        for (int sample = 0; sample < outSamples; sample++) {
            mainTrackLeft[sample] += trackData[track]->dataL[sample] * level;
            mainTrackRight[sample] += trackData[track]->dataR[sample] * level;
        }
    }
    setTracks(mainTrackLeft, mainTrackRight);
}


int addNewTrack() {
    if(tracks == trackBufferSize) {
        trackData = realloc(trackData, sizeof(struct track *) * trackBufferSize * 2);
        trackBufferSize *= 2;
    }
    usedIds++;
    struct track track;
    trackData[tracks] = &track;
    trackData[tracks]->level = 1.0;
    trackData[tracks]->dataL = (float *)malloc(sizeof(float));
    trackData[tracks]->dataR = (float *)malloc(sizeof(float));
    trackData[tracks]->samples = 1;
    trackData[tracks]->id = usedIds;
    tracks++;
    return usedIds;
}


void removeTrack(int id) {
    int found = 0;
    for(int track = 0; track < tracks; track++) {
        if(trackData[track]->id == id) {
            free(trackData[track]);
            found = 1;
        }
        if(found) trackData[track] = trackData[track + 1];
    }
    if(found) {
        tracks--;
        if(tracks < trackBufferSize / 4) {
            trackData = realloc(trackData, sizeof(struct track *) * trackBufferSize / 2);
            trackBufferSize /= 2;
        }
    }
    _combineTracks();
}


void updateTrack(int id, float *dataL, float *dataR, int samples) {
    for(int track = 0; track < tracks; track++) {
        if(trackData[track]->id == id) {
            if(trackData[track]->samples != samples) {
                trackData[track]->dataR = realloc(trackData[track]->dataR, sizeof(float) * samples);
                trackData[track]->dataL = realloc(trackData[track]->dataL, sizeof(float) * samples);
            }
            for(int sample = 0; sample < outSamples; sample++) { //this will eventualy hold efects stuff too
                trackData[track]->dataL[sample] = dataL[sample];
                trackData[track]->dataR[sample] = dataR[sample];
            }
            break;
        }
    }
    _combineTracks();
}

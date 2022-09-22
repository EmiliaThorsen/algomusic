#include "stdlib.h"
#include "../structure.h"
#include "./playBack.h"

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
    for(int track = 0; track < tracks; track++) {
        for (int sample = 0; sample < outSamples; sample++) {
            mainTrackLeft[sample] += trackData[track]->dataL[sample];
            mainTrackRight[sample] += trackData[track]->dataR[sample];
        }
    }
    for (int sample = 0; sample < outSamples; sample++) {
        mainTrackLeft[sample] /= tracks;
        mainTrackRight[sample] /= tracks;
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
    trackData[tracks]->level = 1;
    trackData[tracks]->dataL = (float *)malloc(sizeof(float) * 100);
    trackData[tracks]->dataR = (float *)malloc(sizeof(float) * 100);
    trackData[tracks]->samples = 100;
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
            for(int sample = 0; sample < outSamples; sample++) {
                trackData[track]->dataL[sample] = dataL[sample] * trackData[track]->level;
                trackData[track]->dataR[sample] = dataR[sample] * trackData[track]->level;
            }
            break;
        }
    }
    _combineTracks();
}

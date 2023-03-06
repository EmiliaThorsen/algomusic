#include "./sharedSecuancerTypes.h"
#include <stdlib.h>
#include "../controll.h"
#include "./secuanceStorage.h"


int sequencerSongLength = 0;

int sections = 0;
int sectionBufferSize;
struct sequencerSection **sectionArray;

//sequance related code
void _updateSongLength() {
    setGlobalVariable(songLength, sequencerSongLength);
}


void initSequencer(){
    sectionArray = malloc(sizeof(struct sequencerSection *));
    sectionBufferSize = 1;
    _updateSongLength();
}


void addSection(int length) {
    struct sequencerSection *sequance = malloc(sizeof(struct sequencerSection));
    sequance->lengh = length;
    sequance->tracks = 0;
    sequance->trackBufferSize = 1;
    sequance->track = malloc(sizeof(struct sequencerTrack));
    if(sections == sectionBufferSize) {
        sectionArray = realloc(sectionArray, sizeof(struct sequencerSection *) * sectionBufferSize * 2);
        sectionBufferSize *= 2;
    }
    sectionArray[sections] = sequance;
    sections++;
    sequencerSongLength += length;
    _updateSongLength();
}


void removeSection(int section) {
    sequencerSongLength -= sectionArray[section]->lengh;
    free(sectionArray[section]);
    for(int i = section; i < sections; i++) {
        sectionArray[i] = sectionArray[i + 1];
    }
    sections--;
    if(sections < sectionBufferSize / 4) {
        sectionArray = realloc(sectionArray, sizeof(struct sequencerSection *) * sectionBufferSize / 2);
        sectionBufferSize /= 2;
    }
    _updateSongLength();
}


struct sequencerSection *getSection(int section) {
    return sectionArray[section];
}


int getSectionCount() {
    return sections;
}


//track related code
void addSequanceTrack(struct sequencerSection *section) {
    struct sequencerTrack *track = malloc(sizeof(struct sequencerTrack));
    if(section->tracks == section->trackBufferSize) {
        section->track = realloc(section->track, sizeof(struct sequencerTrack *) * section->trackBufferSize * 2);
        section->trackBufferSize *= 2;
    }
    section->track[section->tracks] = track;
    section->tracks++;
}


void removeSequanceTrack(struct sequencerSection *section, int track) {
    free(section->track[track]);
    for(int i = track; i < section->tracks; i++) {
        section->track[i] = section->track[i + 1];
    }
    section->tracks--;
    if(section->tracks < section->trackBufferSize / 4) {
        section->track = realloc(section->track, sizeof(struct sequencerTrack *) * section->trackBufferSize / 2);
        section->trackBufferSize /= 2;
    }
}


int getSequanceTrackCount(struct sequencerSection *section) {
    return section->tracks;
}

#include "./sharedSecuancerTypes.h"
#include <stdlib.h>
#include "../controll.h"


int sequencerSongLength = 0;

int sections = 0;
int sectionBufferSize;
struct sequencerSection **sectionArray;


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
    sequance->track = malloc(0);
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

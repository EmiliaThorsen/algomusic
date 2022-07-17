#include <stdio.h>
#include <portaudio.h>
#include <math.h>
#include "./math/computer.h"
#include "./playBack/playBack.h"
#include "./ui/ui.h"
#include <unistd.h>
#include "./controll.h"

#define SAMPLE_RATE (44100)


int main() {
    soundFormat format;
    format.frameSize = SAMPLE_RATE;
    format.sampleRate = SAMPLE_RATE;
    format.stereo = 1;

    startTUI();
    setControllVariable(running, 1);
    while (getControllVariable(running)) {
        updateTUI();
        usleep(50000);
    }
    quitTUI();


    //temporary teting code
    float temp = 600.0;
    float temp2 = 1000.0;
    instruction inst[11];
    inst[0].type = 0; inst[0].ID=4;
    inst[1].type = 1; inst[1].data.f=&temp;
    inst[2].type = 0; inst[2].ID=3;
    inst[3].type = 0; inst[3].ID=2;
    inst[4].type = 0; inst[4].ID=5;
    inst[5].type = 0; inst[5].ID=4;
    inst[6].type = 1; inst[6].data.f=&temp2;
    inst[7].type = 0; inst[7].ID=3;
    inst[8].type = 0; inst[8].ID=2;
    inst[9].type = 0; inst[9].ID=5;
    inst[10].type = 0; inst[10].ID=0;
    float *test = computeSoundData(inst, 11, format, 0, 6);
    struct trackData tracks[1];
    struct trackData track0 = {0, 0.5, test};
    tracks[0] = track0;

    initPa(format);
    setTracks(tracks, 1);
    startPlayBack(0);
    while (getCurrentPlaybackTime() < 5) {}
    stopPlayBack();
    terminatePa();
    return 0;
}

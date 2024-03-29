#include <stdio.h>
#include <portaudio.h>
#include <math.h>
#include "./math/computer.h"
#include "./playBack/playBack.h"
#include "./playBack/mixer.h"
#include "./ui/ui.h"
#include <stdlib.h>
#include <unistd.h>
#include "./controll.h"
#include "./sequencer/secuanceStorage.h"

#define SAMPLE_RATE (44100)


enum {
    addsound,
    subsound,
    scalesound,
    insertarray,
    insertrange,
    sinewave,
    trianglewave,
    sqarewave,
    sawwave
};


int main() {
    soundFormat format;
    format.frameSize = SAMPLE_RATE;
    format.sampleRate = SAMPLE_RATE;
    format.stereo = 1;

    initControllSystem();
    setGlobalVariable(running, 1);
    setGlobalVariable(sampleRate, SAMPLE_RATE);
    initMixer();
    initSequencer();

    //main program loop
    startTUI();
    while (getGlobalVariable(running)) {
        updateTUI();
        handleEvents();
        usleep(50000);
    }
    quitTUI();

    //temporary teting code
  //float *temp = malloc(sizeof(float));
  //float *temp2 = malloc(sizeof(float));
  //float *scaler = malloc(sizeof(float));
  //*temp = 400.0;
  //*temp2 = 600.0;
  //*scaler = 0.5;
  //instruction inst[14];
  //inst[0].type = 0; inst[0].ID=insertrange;
  //inst[1].type = 1; inst[1].data.f=temp;
  //inst[2].type = 0; inst[2].ID=insertarray;
  //inst[3].type = 0; inst[3].ID=scalesound;
  //inst[4].type = 0; inst[4].ID=sinewave;
  //inst[5].type = 0; inst[5].ID=insertrange;
  //inst[6].type = 1; inst[6].data.f=temp2;
  //inst[7].type = 0; inst[7].ID=insertarray;
  //inst[8].type = 0; inst[8].ID=scalesound;
  //inst[9].type = 0; inst[9].ID=sinewave;
  //inst[10].type = 0; inst[10].ID=addsound;
  //inst[11].type = 1; inst[11].data.f=scaler;
  //inst[12].type = 0; inst[12].ID=insertarray;
  //inst[13].type = 0; inst[13].ID=scalesound;

  //float *test = computeSoundData(inst, 14, format, 0, 6);
  //setOutTrackSize(format.sampleRate * 6);
  //int id = addNewTrack();
  //updateTrack(id, test, test);

  //initPa(format);
  //startPlayBack(0);
  //while (getCurrentPlaybackTime() < 5) {}
  //stopPlayBack();
  //terminatePa();
  //free(test);

    freeGlobalVariables();
    return 0;
}

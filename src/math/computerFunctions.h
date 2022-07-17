#include <complex.h>
#include "sharedTypes.h"
#include "../structure.h"


int addSound(mixBuff *, mixBuff *, int, soundFormat, int, int);
int subSound(mixBuff *, mixBuff *, int, soundFormat, int, int);
int scaleSound(mixBuff *, mixBuff *, int, soundFormat, int, int);

int insertArray(mixBuff *, mixBuff *, int, soundFormat, int, int);
int insertRange(mixBuff *, mixBuff *, int, soundFormat, int, int);

int sineWave(mixBuff *, mixBuff *, int, soundFormat, int, int);
int triangleWave(mixBuff *, mixBuff *, int, soundFormat, int, int);
int sqareWave(mixBuff *, mixBuff *, int, soundFormat, int, int);
int sawWave(mixBuff *, mixBuff *, int, soundFormat, int, int);


static int (*operators[]) (mixBuff *, mixBuff *, int, soundFormat, int, int) = {
    addSound,
    subSound,
    scaleSound,
    insertArray,
    insertRange,
    sineWave,
    triangleWave,
    sqareWave,
    sawWave
};

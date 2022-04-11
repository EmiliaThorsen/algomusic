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
    [0] = addSound,
    [1] = subSound,
    [2] = scaleSound,
    [3] = insertArray,
    [4] = insertRange,
    [5] = sineWave,
    [6] = triangleWave,
    [7] = sqareWave,
    [8] = sawWave
};

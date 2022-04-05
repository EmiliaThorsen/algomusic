#include <complex.h>
#include "../structure.h"

typedef struct {
    int type;
    union {
        float *f;
        float _Complex *cf;
    };
} mixBuff;


typedef struct {
    int type;
    union {
    int ID;
    mixBuff data;
    };
} instruction;


float *computeSoundData(instruction *instructions, int size, soundFormat format, int startFrame, int frames);

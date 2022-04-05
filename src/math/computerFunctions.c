#include "computerFunctions.h"
#include "audioMath.h"


int addSound(mixBuff *stack, mixBuff *data, int stackPos, soundFormat format, int startFrame, int frames) {
    for (int i = 0; i<format.frameSize*frames; i++) {
        stack[stackPos-2].f[i] += stack[stackPos-1].f[i];
    }
    return stackPos-1;
}


int subSound(mixBuff *stack, mixBuff *data, int stackPos, soundFormat format, int startFrame, int frames) {
    for (int i = 0; i<format.frameSize*frames; i++) {
        stack[stackPos-2].f[i] -= stack[stackPos-1].f[i];
    }
    return stackPos-1;
}


int scaleSound(mixBuff *stack, mixBuff *data, int stackPos, soundFormat format, int startFrame, int frames) {
    for (int i = 0; i<format.frameSize*frames; i++) {
        stack[stackPos-2].f[i] *= *stack[stackPos-1].f;
    }
    return stackPos-1;
}


int insertArray(mixBuff *stack, mixBuff *data, int stackPos, soundFormat format, int startFrame, int frames) {
    stack[stackPos].f = data->f;
    return stackPos+1;
}


int insertRange(mixBuff *stack, mixBuff *data, int stackPos, soundFormat format, int startFrame, int frames) {
    int frameSize = format.frameSize;
    float range[frameSize*frames];
    for (int i = 0; i < frameSize * frames; i++) {
        range[i] = (float)(i + startFrame * frameSize) / (float)format.sampleRate;
    }
    stack[stackPos].f = range;
    return stackPos+1;
}


int sineWave(mixBuff *stack, mixBuff *data, int stackPos, soundFormat format, int startFrame, int frames) {
    for (int i = 0; i < format.frameSize * frames; i++) {
        stack[stackPos-1].f[i] = sinwave(stack[stackPos-1].f[i]);
    }
    return stackPos;
}


int triangleWave(mixBuff *stack, mixBuff *data, int stackPos, soundFormat format, int startFrame, int frames) {
    for (int i = 0; i < format.frameSize * frames; i++) {
        stack[stackPos-1].f[i] = triwave(stack[stackPos-1].f[i]);
    }
    return stackPos;
}


int sqareWave(mixBuff *stack, mixBuff *data, int stackPos, soundFormat format, int startFrame, int frames) {
    for (int i = 0; i < format.frameSize * frames; i++) {
        stack[stackPos-1].f[i] = sqrwave(stack[stackPos-1].f[i]);
    }
    return stackPos;
}


int sawWave(mixBuff *stack, mixBuff *data, int stackPos, soundFormat format, int startFrame, int frames) {
    for (int i = 0; i < format.frameSize * frames; i++) {
        stack[stackPos-1].f[i] = sawwave(stack[stackPos-1].f[i]);
    }
    return stackPos;
}

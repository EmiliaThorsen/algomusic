#include "computerFunctions.h"
#include <complex.h>

float *computeSoundData(instruction *instructions, int size, soundFormat format, int startFrame, int frames){
    mixBuff stack[size];
    int stackPos = 0;
    mixBuff *data;

    for (int instruction=0; instruction<size; instruction++) {
        if (instructions[instruction].type == 1) {
            data = &instructions[instruction].data;
            continue;
        }
        stackPos = operators[instructions[instruction].ID](stack, data, stackPos, format, startFrame, frames);
    }

    return stack[0].f;   
}

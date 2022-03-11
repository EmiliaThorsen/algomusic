#include "audioMath.h"


typedef struct arrayRange {
    int start;
    int end;
} arrayRange;


typedef struct expresion {
    int type;
    union {
        float number;
        float _Complex compNum;
        float *variable;
        float _Complex *complexVar;
        arrayRange arrayRange;
        int operation;
    };
} expresion;


typedef struct mixedTypeBuffer {
    int type;
    union {
        float number;
        float *array;
        float _Complex compNum;
        float _Complex *compNumArray;
        arrayRange range;
    };
} mixedTypeBuffer;


int add(mixedTypeBuffer *stack, int stackPos, int size) {
    for(int i=0; i < size; i++) {stack[stackPos-2].array[i] += stack[stackPos - 1].array[i];}
    return 1;
}


int sub(mixedTypeBuffer *stack, int stackPos, int size) {
    for(int i=0; i < size; i++) {stack[stackPos-2].array[i] -= stack[stackPos - 1].array[i];}
    return 1;
}


int sinus(mixedTypeBuffer *stack, int stackPos, int size) {
    for(int i=0; i < size; i++) {stack[stackPos - 1].array[i] = sinwave(stack[stackPos - 1].array[i]);}
    return 0;
}


int sqr(mixedTypeBuffer *stack, int stackPos, int size) {
    for(int i=0; i < size; i++) {stack[stackPos - 1].array[i] = sqrwave(stack[stackPos - 1].array[i]);}
    return 0;
}


int saw(mixedTypeBuffer *stack, int stackPos, int size) {
    for(int i=0; i < size; i++) {stack[stackPos - 1].array[i] = sawwave(stack[stackPos - 1].array[i]);}
    return 0;
}


int tri(mixedTypeBuffer *stack, int stackPos, int size) {
    for(int i=0; i < size; i++) {stack[stackPos - 1].array[i] = triwave(stack[stackPos - 1].array[i]);}
    return 0;
}


static int (*operators[]) (mixedTypeBuffer *, int, int) = {
    [0] = add,
    [1] = sub,
    [2] = sinus,
    [3] = sqr,
    [4] = saw,
    [5] = tri
};


//function for calculating a rpn function into an array of floats
float *calculateRPN(expresion *function, int funcSize, int start, int end) {
    int size = end - start;
    int vars = 0;
    for(int ex = 0; ex < funcSize; ex++) {if(function[ex].type<5) {vars++;}}
    mixedTypeBuffer stack[vars];
    int stackPos = 0;

    for (int expr = 0; expr < funcSize; expr++) {
        expresion currentExpresion = function[expr];
        switch (currentExpresion.type) {
            case 0:
                stack[stackPos].type = 0;
                stack[stackPos].number = currentExpresion.number;
                stackPos++;
                break;
            case 1:
                stack[stackPos].type = 2;
                stack[stackPos].compNum = currentExpresion.compNum;
                stackPos++;
                break;
            case 2:
                stack[stackPos].type = 0;
                stack[stackPos].number = *currentExpresion.variable;
                stackPos++;
                break;
            case 3:
                stack[stackPos].type = 2;
                stack[stackPos].compNum = *currentExpresion.complexVar;
                stackPos++;
                break;
            case 4:
                stack[stackPos].type = 4;
                stack[stackPos].range.start = start;
                stack[stackPos].range.start = end;
                stackPos++;
            case 5:
                stackPos -= operators[currentExpresion.operation](stack, stackPos, size);
                break;
        }
    }
    return stack[0].array;
}

#include "./controll.h"
#include <stdlib.h>


int *globalVariables;


void initGlobalVariables() {
    globalVariables = malloc(sizeof(int) * flagCount);
}


void setGlobalVariable(enum flags flag, int data) {
    globalVariables[flag] = data;
}


int getGlobalVariable(enum flags flag) {
    return globalVariables[flag];
}


void freeGlobalVariables() {
    free(globalVariables);
}




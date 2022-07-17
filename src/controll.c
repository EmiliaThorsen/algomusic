#include "./controll.h"


int globalVariables[flagCount];


void setControllVariable(enum flags flag, int data) {
    globalVariables[flag] = data;
}


int getControllVariable(enum flags flag) {
    return globalVariables[flag];
}

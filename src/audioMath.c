#include <math.h>
#include "audioMath.h"

//function for calculating a rpn function into an array of floats
float *calculateFunction(void *func, int start, int end){
    float awo =69.0;
    return &awo;
}

//the difrent types of waves
float sinwave(float ang){
   return(sin(ang*6.283185307));
}
float sqrwave(float ang){
    return(2*(fmod(ang+0.5, 1)>=0.5)-1);
}
float sawwave(float ang){
    return(fmod(ang*2+1, 2)-1);
}
float triwave(float ang){
    return(fabs(fmod(ang*4, 4)-2)-1);
}

//usefull helper functions
float cut(float value, float max, float min);
    

#include <complex.h>

//function for calculating a rpn function into an array of floats
float *calculateFunction(void *func, int start, int end);

//the difrent types of waves
float sinwave(float ang);
float sqrwave(float ang);
float sawwave(float ang);
float triwave(float ang);

//usefull helper functions
float clamp(float value, float max, float min);
void FFT(float _Complex buffer[], int size);
void IFFT(float _Complex buffer[], int size);

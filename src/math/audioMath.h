#include <complex.h>


//the difrent types of waves
float sinwave(float ang);
float sqrwave(float ang);
float sawwave(float ang);
float triwave(float ang);


//usefull helper functions
float clamp(float value, float max, float min);
float frequency(float sample, int samplerate, float frequency);
float note(float sample, int samplerate, float note);


//signal procesing functions
void FFT(float _Complex buffer[], int size);
void IFFT(float _Complex buffer[], int size);
void multcompbuffers(float _Complex buffer[], float _Complex multiplier[], int size);
void biquadfilter(float buffer[], int size, float b0, float b1, float b2, float a0, float a1, float a2);

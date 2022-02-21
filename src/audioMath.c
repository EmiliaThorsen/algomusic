#include <math.h>
#include "audioMath.h"
#include <complex.h>

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

float clamp(float value, float max, float min) {
    const float t = value < min ? min : value;
    return t > max ? max : t;
}

typedef float complex compf;

void _fft(compf buffer[], compf out[], int n, int step, compf precomp) {
    if (step < n) {
		_fft(out, buffer, n, step * 2, precomp);
		_fft(out + step, buffer + step, n, step * 2, precomp);
		for (int i = 0; i < n; i += 2 * step) {
            compf w = cpowf(precomp, i) * out[i+step]; 
			buffer[i / 2]     = out[i] + w;
			buffer[(i + n)/2] = out[i] - w;
		}
	}
}

void FFT(compf buffer[], int size) {
    compf out[size];
	for (int i = 0; i < size; i++) out[i] = buffer[i];
    compf precomp = cexpf(-I * 3.14159265 / size);
	_fft(buffer, out, size, 1, precomp);
}

void IFFT(compf buffer[], int size) {
    compf out[size];
	for (int i = 0; i < size; i++) out[i] = buffer[i];
    compf precomp = 1.0/size * cexpf(I * 3.14159265 / size);
	_fft(buffer, out, size, 1, precomp);
}

void multcompbuffers(compf buffer[], compf multiplier[], int size){
    for (int i=0; i < size; i++) {
        buffer[i] *= multiplier[i];
    } 
}

void biquadfilter(float buffer[], int size, float b0, float b1, float b2, float a1, float a2){
    float in[size];
    for (int i=0; i < size; i++) {
        in[i] = buffer[i];
    }
    buffer[0] = b0*in[0];
    buffer[1] = b0*in[1]+b1*in[0]-a1*buffer[0];
    for (int i=2; i < size; i++) {
        buffer[i] = b0*in[i]+b1*in[i-1]+b2*in[i-2]-a1*buffer[i-1]-a2*buffer[i-2];
    }
}

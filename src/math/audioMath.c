#include <math.h>
#include <complex.h>
#include "audioMath.h"


//the difrent types of waves:
float sinwave(float ang) {
    ang -= (int)ang;
    float a = (ang - 1) * (ang - 0.5);
    return 20 * ang * a + 50 * ang * a * (ang - 0.205) * (ang - 0.795) * (ang * (ang - 1) - 0.91);
}


float sqrwave(float ang) {return((int)(2 * ang + 1) % 2 - 0.5);}


float sawwave(float ang) {return((ang - (int)ang) * 2 - 1);}


float triwave(float ang) {
    float temp = (ang - (int)(ang - 0.25) - 0.25);
    return((temp * 2 - 1) * ((temp > 0.5) * 2 - 1));
}


//usefull helper functions:

//clamps a float to a min and max value
float clamp(float value, float max, float min) {
    const float t = value < min ? min : value;
    return t > max ? max : t;
}


//returns the angle that would corespond to a point in a sine wave for the given frequency at a specific sample
float frequency(float sample, int samplerate, float frequency) {return sample / samplerate * frequency;}


//same as frequency but for a note on the latin piano scale
float note(float sample, int samplerate, float note) {return sample / samplerate * 440 * pow(2, (note - 49) / 12);}


//signal processing stuff:


typedef float complex compf;


//it works, don't ask
void _fft(compf buffer[], compf out[], int n, int step, compf precomp) {
    if(step < n) {
        _fft(out, buffer, n, step * 2, precomp);
        _fft(out + step, buffer + step, n, step * 2, precomp);
        for (int i = 0; i < n; i += 2 * step) {
            compf w = cpowf(precomp, i) * out[i + step];
            buffer[i / 2]     = out[i] + w;
            buffer[(i + n) / 2] = out[i] - w;
        }
    }
}


//fast forier transform
void FFT(compf buffer[], int size) {
    compf out[size];
    for (int i = 0; i < size; i++) {out[i] = buffer[i];}
    compf precomp = cexpf(-I * 3.14159265 / size);
    _fft(buffer, out, size, 1, precomp);
}


//inverse fast forier transform
void IFFT(compf buffer[], int size) {
    compf out[size];
    for (int i = 0; i < size; i++) {out[i] = buffer[i];}
    compf precomp = 1.0 / size * cexpf(I * 3.14159265 / size);
    _fft(buffer, out, size, 1, precomp);
}


//it just multiplies togheter 2 buffers of complex floats
void multcompbuffers(compf buffer[], compf multiplier[], int size) {for(int i = 0; i < size; i++) {buffer[i] *= multiplier[i];}}


//a descrete laprace transformation, or in less fancy terms a bi-quad filter, or in even less fancy terms, a filter
void biquadfilter(float buffer[], int size, float b0, float b1, float b2, float a0, float a1, float a2) {
    float in[size];
    for(int i = 0; i < size; i++) {in[i] = buffer[i];}
    buffer[0] = b0 * in[0];
    buffer[1] = b0 * in[1] + b1 * in[0] - a1 * buffer[0];
    for(int i = 2; i < size; i++) {buffer[i] = (b0 * in[i] + b1 * in[i - 1] + b2 * in[i - 2] - a1 * buffer[i - 1] - a2 * buffer[i - 2]) / a0;}
}

typedef struct {
    int sampleRate;
    int frameSize;
    int stereo;
} soundFormat;


struct trackData {
    int trackID;
    float level;
    float *audio;
};


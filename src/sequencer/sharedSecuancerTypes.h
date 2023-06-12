struct note {
    int data;
};


struct subSection {
    float bpm;
    int points;
    union point *point;
};


union point {
    struct note *data;
    struct subSection *subSection;
};


struct sequencerTrack {
    int points;
    int pointBufferSize;
    float bpm;
    int id;
    union point **point;
};


struct sequencerSection {
    int lengh;
    int tracks;
    int trackBufferSize;
    struct sequencerTrack **track;
};

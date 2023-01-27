struct timePoints {
    int startTime;
    int endTime;
    int data;
};


struct sequencerTrack {
    int lengh;
    int id;
    struct timePoints *points;
};


struct sequencerSection {
    int lengh;
    int tracks;
    struct sequencerTrack *track;
};

int initPa(soundFormat format); //intitiate main portaudio playback stuff
int terminatePa(); //terminate main portaudio playback stuff

int getCurrentSample(); //get the current sample the player is on
int getCurrentPlaybackTime(); //get the current time the player is on in seconds

int startPlayBack(unsigned int sample); //start playing at a specific sample
int stopPlayBack(); //stop playing

int setTracks(struct trackData *data, int tracks); //set the tracks that should be played and their data

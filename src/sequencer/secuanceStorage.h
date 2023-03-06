void initSequencer();

void addSection(int length);
void removeSection(int section);

struct sequencerSection *getSection(int section);
int getSectionCount();

void addSequanceTrack(struct sequencerSection *);
void removeSequanceTrack(struct sequencerSection *section, int track);
int getSequanceTrackCount(struct sequencerSection *);

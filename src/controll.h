enum flags {
    running,
    playing,
    songLength,
    sampleRate,
    playHeadPos,
    flagCount
};


struct event {
    int type;
    void *data;
};


struct basicFuncCall {
    void (*func)(int);
    int id;
};


void setGlobalVariable(enum flags, int);
int getGlobalVariable(enum flags);
void initControllSystem();
void freeGlobalVariables();

void newEvent(struct event *event);
void handleEvents();

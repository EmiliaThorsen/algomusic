struct keyConfig {
    char inputs;
    void (*action)(int);
};


void quit(int);


int configs = 1;
struct keyConfig keyConfigs[] = {
    {'q', quit}
};

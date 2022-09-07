struct keyConfig {
    char inputs;
    void (*action)(int);
};


void space(int);
void quit(int);


int configs = 2;
struct keyConfig keyConfigs[] = {
    {' ', space},
    {'q', quit}
};

struct keyConfig {
    char inputs;
    void (*action)();
};


void space();
void quit();


int configs = 2;
struct keyConfig keyConfigs[] = {
    {' ', space},
    {'q', quit}
};

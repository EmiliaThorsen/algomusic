void startTUI();
void updateTUI();
void quitTUI();


struct screen {
    char **(*renderer)(int, int, int);
    char *name;
    int id;
    void *data;
    struct keystrokes *screenKeystrokes;
};

void *getDataFromId(int id);

void addNewWindow(struct screen *(*initier)(), int id);
void removeWindow(int id);

void switchTab(int tab);

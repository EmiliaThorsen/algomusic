#include "../c-TUI-framework/cTUIFramework.h"

void startTUI();
void updateTUI();
void quitTUI();


struct screen {
    void (*maker)(struct container *);
    void (*destroyer)(struct container *);
    char *name;
};

#include "../c-TUI-framework/src/cTUIframework.h"
#include "../config.h"
#include <stdio.h>
#include <stdlib.h>
#include "./keystrokes.h"
#include "../controll.h"

void space() {
    printf("space detected uwu!\n");
}


void quit() {
    setGlobalVariable(running, 0);
}


struct keystrokes generateKeystrokes() {
    struct keystrokes keystrokesOut;
    struct keystroke *keystrokes = malloc(sizeof(struct keystroke) * configs);
    for (int key = 0; key < configs; key++) {
        struct keystroke keystroke;
        keystroke.key = keyConfigs[key].inputs;
        keystroke.type = 0;
        keystroke.function = keyConfigs[key].action;
        keystrokes[key] = keystroke;
    }
    keystrokesOut.keystrokeArray = keystrokes;
    keystrokesOut.keystorkes = configs;
    return keystrokesOut;
}

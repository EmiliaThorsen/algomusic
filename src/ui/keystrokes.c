#include "../c-TUI-framework/cTUIFramework.h"
#include "../config.h"
#include <stdio.h>
#include <stdlib.h>
#include "./keystrokes.h"
#include "../controll.h"

void space(int id) {
    printf("space detected uwu!\n");
}


void quit(int id) {
    setGlobalVariable(running, 0);
}


void generateKeystrokes(struct keystrokes *keystrokesOut) {
    struct keystroke *keystrokes = malloc(sizeof(struct keystroke) * configs);
    for (int key = 0; key < configs; key++) {
        struct keystroke keystroke;
        keystroke.key = keyConfigs[key].inputs;
        keystroke.type = 0;
        keystroke.id = 0;
        keystroke.function = keyConfigs[key].action;
        keystrokes[key] = keystroke;
    }
    keystrokesOut->keystrokeArray = keystrokes;
    keystrokesOut->keystorkes = configs;
}


void updateKeystrokes(struct keystrokes *keystrokes, struct keystrokes *currentKeystrokes) {
    free(currentKeystrokes->keystrokeArray);
    generateKeystrokes(currentKeystrokes);
    currentKeystrokes->keystrokeArray = realloc(currentKeystrokes->keystrokeArray, sizeof(struct keystroke) * (keystrokes->keystorkes + currentKeystrokes->keystorkes));
    for (int keystroke = 0; keystroke < keystrokes->keystorkes; keystroke++) {
        currentKeystrokes->keystrokeArray[currentKeystrokes->keystorkes + keystroke] = keystrokes->keystrokeArray[keystroke];
    }
    currentKeystrokes->keystorkes += keystrokes->keystorkes;
    setKeystrokes(*currentKeystrokes);
}

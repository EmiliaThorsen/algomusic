#include "../c-TUI-framework/cTUIFramework.h"
#include "../config.h"
#include <stdio.h>
#include <stdlib.h>
#include "./keystrokes.h"
#include "../controll.h"


void quit(int id) {
    setGlobalVariable(running, 0);
}


void updateKeystrokes(struct keystrokes *keystrokes, struct keystrokes *currentKeystrokes) {
    free(currentKeystrokes->keystrokeArray);

    struct keystroke *newKeystrokes = malloc(sizeof(struct keystroke) * (configs + keystrokes->keystorkes));
    for (int key = 0; key < configs; key++) {
        struct keystroke keystroke;
        keystroke.key = keyConfigs[key].inputs;
        keystroke.type = 0;
        keystroke.id = 0;
        keystroke.function = keyConfigs[key].action;
        newKeystrokes[key] = keystroke;
    }
    currentKeystrokes->keystrokeArray = newKeystrokes;

    for (int keystroke = 0; keystroke < keystrokes->keystorkes; keystroke++) {
        currentKeystrokes->keystrokeArray[configs + keystroke] = keystrokes->keystrokeArray[keystroke];
    }
    currentKeystrokes->keystorkes = configs + keystrokes->keystorkes;
    setKeystrokes(*currentKeystrokes);
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "../c-TUI-framework/cTUIFramework.h"
#include "commonTabFunctions.h"
#include "../sequencer/secuanceStorage.h"
#include "../controll.h"

struct mainMenuData {
    int selectedWindow;
    int sideBarSize;
    int selectedSection;
};


char **mainMenuContentRenderer(int height, int width, int id) {
    char **content = initWindowContent(height, width, ' ');
    struct mainMenuData *data = getDataFromId(id);

    //draw ui lines
    for (int x = 0; x < width; x++) {
        content[5][x] = '-';
    }
    for (int y = 5; y < height; y++) {
        content[y][data->sideBarSize] = '|';
    }
    content[5][data->sideBarSize] = '+';

    writeStr(content, 0, 0, "track name - artist name");
    writeStr(content, 0, 1, "playback: stopped");
    writeStr(content, 0, 2, "track lengh: 0ms");

    //calculating song lengh in ms
    int lenthInMS = (getGlobalVariable(songLength) * 1000) / getGlobalVariable(sampleRate);
    if(lenthInMS != 0) {
        char timeString[(int)(ceil(log10(lenthInMS))+3)];
        sprintf(timeString, "%dms", lenthInMS);
        writeStr(content, 13, 2, timeString);
    }

    writeStr(content, width - 13, 0, "level: 100%");
    writeStr(content, width - 13, 1, "-----------");
    writeStr(content, width - 13, 2, "#|");
    writeStr(content, width - 13, 3, "#|");




    return content;
}


void addSectionKeystroke(int id) {
    addSection(50000);
}


void deleteSectionKeystroke(int id) {
    removeSection(0);
}


struct screen *mainMenuScreenIniter(int id) {
    struct screen *screen = baseScreenBuilder("main menu", id, mainMenuContentRenderer);
    struct keystroke *keystrokes = malloc(sizeof(struct keystroke) * 2);
    keystrokes[0].key = 'a';
    keystrokes[0].type = 0;
    keystrokes[0].id = id;
    keystrokes[0].function = addSectionKeystroke;
    keystrokes[1].key = 'd';
    keystrokes[1].type = 0;
    keystrokes[1].id = id;
    keystrokes[1].function = deleteSectionKeystroke;
    struct keystrokes *keys = malloc(sizeof(struct keystrokes));
    screen->screenKeystrokes = keys;
    screen->screenKeystrokes->keystrokeArray = keystrokes;
    screen->screenKeystrokes->keystorkes = 2;
    struct mainMenuData *data = malloc(sizeof(struct mainMenuData));
    data->selectedWindow = 0;
    data->sideBarSize = 50;
    screen->data = data;
    return screen;
}

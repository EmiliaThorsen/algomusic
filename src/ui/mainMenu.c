#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "../c-TUI-framework/cTUIFramework.h"
#include "commonTabFunctions.h"
#include "../sequencer/secuanceStorage.h"
#include "../sequencer/sharedSecuancerTypes.h"
#include "../controll.h"

struct mainMenuData {
    int selectedWindow;
    int sideBarSize;
    int selectedSection;
    int selectedTrack;
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

    //write section count
    int sections = getSectionCount();
    char sectionCountStr[14];
    sprintf(sectionCountStr, "sections: %d", sections);
    writeStr(content, 0, 6, sectionCountStr);

    //draw sections
    for(int section = 0; section < sections; section++) {
        for (int x = 0; x < data->sideBarSize; x++) {
            content[7 + section * 2][x] = '-';
        }
        struct sequencerSection *sectionData = getSection(section);
        char sectionLength[30];
        sprintf(sectionLength, "lengh: %dms, tracks: %d", sectionData->lengh * 1000 / getGlobalVariable(sampleRate), getSequanceTrackCount(sectionData));
        writeStr(content, 2, 8 + section * 2, sectionLength);
        if(section == data->selectedSection) {
            content[8 + section * 2][0] = '>';
        }
    }
    for (int x = 0; x < data->sideBarSize; x++) {
        content[7 + sections * 2][x] = '-';
    }


    return content;
}


void addSectionKeystroke(int id) {
    addSection(50000);
}


void deleteSectionKeystroke(int id) {
    removeSection(0);
}


void goDownSections(int id) {
    struct mainMenuData *data = getDataFromId(id);
    data->selectedSection += 1;
    if(data->selectedSection > getSectionCount() - 1) data->selectedSection = 0;
}


void goUpSections(int id) {
    struct mainMenuData *data = getDataFromId(id);
    data->selectedSection -= 1;
    if(data->selectedSection < 0) data->selectedSection = getSectionCount() - 1;
}


void goLeftTrack(int id) {
    struct mainMenuData *data = getDataFromId(id);
    data->selectedTrack += 1;
}


void goRightTrack(int id) {
    struct mainMenuData *data = getDataFromId(id);
    data->selectedTrack -= 1;
}


void addTrackKeystroke(int id) {
    struct mainMenuData *data = getDataFromId(id);
    struct sequencerSection *section = getSection(data->selectedSection);
    addSequanceTrack(section);
}


void removeTrackKeystroke(int id) {
    struct mainMenuData *data = getDataFromId(id);
    struct sequencerSection *section = getSection(data->selectedSection);
    removeSequanceTrack(section, data->selectedTrack);
}


struct screen *mainMenuScreenIniter(int id) {
    struct screen *screen = baseScreenBuilder("main menu", id, mainMenuContentRenderer);
    struct keystroke *keystrokes = malloc(sizeof(struct keystroke) * 8);
    keystrokes[0].key = 'a';
    keystrokes[0].type = 0;
    keystrokes[0].id = id;
    keystrokes[0].function = addSectionKeystroke;
    keystrokes[1].key = 'd';
    keystrokes[1].type = 0;
    keystrokes[1].id = id;
    keystrokes[1].function = deleteSectionKeystroke;
    keystrokes[2].key = 'j';
    keystrokes[2].type = 0;
    keystrokes[2].id = id;
    keystrokes[2].function = goDownSections;
    keystrokes[3].key = 'k';
    keystrokes[3].type = 0;
    keystrokes[3].id = id;
    keystrokes[3].function = goUpSections;
    keystrokes[4].key = 'h';
    keystrokes[4].type = 0;
    keystrokes[4].id = id;
    keystrokes[4].function = goRightTrack;
    keystrokes[5].key = 'l';
    keystrokes[5].type = 0;
    keystrokes[5].id = id;
    keystrokes[5].function = goLeftTrack;
    keystrokes[6].key = 't';
    keystrokes[6].type = 0;
    keystrokes[6].id = id;
    keystrokes[6].function = addTrackKeystroke;
    keystrokes[7].key = 'r';
    keystrokes[7].type = 0;
    keystrokes[7].id = id;
    keystrokes[7].function = removeTrackKeystroke;
    struct keystrokes *keys = malloc(sizeof(struct keystrokes));
    screen->screenKeystrokes = keys;
    screen->screenKeystrokes->keystrokeArray = keystrokes;
    screen->screenKeystrokes->keystorkes = 8;
    struct mainMenuData *data = malloc(sizeof(struct mainMenuData));
    data->selectedWindow = 0;
    data->selectedSection = 0;
    data->selectedTrack = 0;
    data->sideBarSize = 50;
    screen->data = data;
    return screen;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "../c-TUI-framework/cTUIFramework.h"
#include "./mainMenu.h"
#include "commonTabFunctions.h"


struct startMenuData {
    int option;
};


char **startMenuContentRenderer(int height, int width, int id) {
    char **content = initWindowContent(height, width, ' ');
    if(width > 90 && height > 15) {
        char *title[11] = {
            " ######\\  ##\\                     ##\\      ##\\                     ##\\           ",
            "##  __##\\ ## |                    ###\\    ### |                    \\__|          ",
            "## /  ## |## | ######\\   ######\\  ####\\  #### |##\\   ##\\  #######\\ ##\\  #######\\ ",
            "######## |## |##  __##\\ ##  __##\\ ##\\##\\## ## |## |  ## |##  _____|## |##  _____|",
            "##  __## |## |## /  ## |## /  ## |## \\###  ## |## |  ## |\\######\\  ## |## /      ",
            "## |  ## |## |## |  ## |## |  ## |## |\\#  /## |## |  ## | \\____##\\ ## |## |      ",
            "## |  ## |## |\\####### |\\######  |## | \\_/ ## |\\######  |#######  |## |\\#######\\ ",
            "\\__|  \\__|\\__| \\____## | \\______/ \\__|     \\__| \\______/ \\_______/ \\__| \\_______|",
            "              ##\\   ## |                                                         ",
            "              \\######  |                                                         ",
            "               \\______/                                                          "
        };
        for(int x = 0; x < 81; x++) {
            for (int y = 0; y < 11; y++) {
                content[y + 3][x + 5] = title[y][x];
            }
        }
    }

    writeStr(content, 7, 17, "start New Project");
    writeStr(content, 7, 19, "open old Project (not implemented yet)");
    struct startMenuData *data = getDataFromId(id);
    if(data->option < 1) data->option = 2;
    if(data->option > 2) data->option = 1;
    content[data->option * 2 + 15][5] = '#';
    return content;
}


void keystrokeJ(int id) {
    struct startMenuData *data = getDataFromId(id);
    data->option++;
}


void keystrokeK(int id) {
    struct startMenuData *data = getDataFromId(id);
    data->option--;
}


void keystrokeSelect(int id) {
    struct startMenuData *data = getDataFromId(id);
    if(data->option == 1) {
        //temporarly goes straight to main menu
        addNewWindow(mainMenuScreenIniter, 2);
        removeWindow(1);
        switchTab(0);
    } else if (data->option == 2) {
        //implement this
    } else {
        //implement error handler
    }
}


struct screen *startMenuScreenIniter(int id) {
    struct screen *screen = baseScreenBuilder("Start menu", id, startMenuContentRenderer);
    struct keystroke *keystrokes = malloc(sizeof(struct keystroke) * 3);
    keystrokes[0].key = 'j';
    keystrokes[0].type = 0;
    keystrokes[0].id = id;
    keystrokes[0].function = keystrokeJ;
    keystrokes[1].key = 'k';
    keystrokes[1].type = 0;
    keystrokes[1].id = id;
    keystrokes[1].function = keystrokeK;
    keystrokes[2].key = ' ';
    keystrokes[2].type = 0;
    keystrokes[2].id = id;
    keystrokes[2].function = keystrokeSelect;
    struct keystrokes *keys = malloc(sizeof(struct keystrokes));
    screen->screenKeystrokes = keys;
    screen->screenKeystrokes->keystrokeArray = keystrokes;
    screen->screenKeystrokes->keystorkes = 3;

    struct startMenuData *data = malloc(sizeof(struct startMenuData));
    data->option = 1;
    screen->data = data;
    return screen;
}

#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "../c-TUI-framework/cTUIFramework.h"


struct data {
    int option;
};


char **contentRenderer(int height, int width, int id) {
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
    struct data *data = getDataFromId(id);
    content[15][data->option] = '#';
    return content;
}


void keystrokeJ(int id) {
    struct data *data = getDataFromId(id);
    data->option++;
}


void keystrokeK(int id) {
    struct data *data = getDataFromId(id);
    data->option--;
}


struct screen *startMenuScreenIniter(int id) {
    struct screen *screen = malloc(sizeof(struct screen));
    struct data *data = malloc(sizeof(struct data));
    screen->renderer = contentRenderer;
    data->option = 10;
    struct keystroke *keystrokes = malloc(sizeof(struct keystroke) * 2);
    keystrokes[0].key = 'j';
    keystrokes[0].type = 0;
    keystrokes[0].id = id;
    keystrokes[0].function = keystrokeJ;
    keystrokes[1].key = 'k';
    keystrokes[1].type = 0;
    keystrokes[1].id = id;
    keystrokes[1].function = keystrokeK;
    struct keystrokes *keys = malloc(sizeof(struct keystrokes));
    screen->screenKeystrokes = keys;
    screen->screenKeystrokes->keystrokeArray = keystrokes;
    screen->screenKeystrokes->keystorkes = 2;
    screen->data = data;
    screen->name = malloc(sizeof(char) * 9);
    strcpy(screen->name, "mainMenu");
    screen->id = id;
    return screen;
}

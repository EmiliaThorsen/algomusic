#include "ui.h"
#include <stdlib.h>
#include <string.h>


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
    data->option++;
    if (data->option == 'z') {
        data->option = 'a';
    }
    content[15][15] = data->option;
    return content;
}


struct screen *startMenuScreenIniter() {
    struct screen *screen = malloc(sizeof(struct screen));
    struct data *data = malloc(sizeof(struct data));
    screen->renderer = contentRenderer;
    data->option = 'a';
    screen->data = data;
    screen->name = malloc(sizeof(char) * 9);
    strcpy(screen->name, "mainMenu");
    return screen;
}

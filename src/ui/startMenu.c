#include "ui.h"
#include <stdlib.h>
#include <string.h>


void maker(struct container *container) {
    struct content *content = malloc(sizeof(struct content));
    container->content = content;
    container->type = 0;
}


void destroyer(struct container *container) {
    free(container->content);
}


struct screen *startMenuScreenIniter() {
    struct screen *screen = malloc(sizeof(struct screen));
    screen->destroyer = destroyer;
    screen->maker = maker;
    screen->name = malloc(sizeof(char) * 9);
    strcpy(screen->name, "mainMenu");
    return screen;
}

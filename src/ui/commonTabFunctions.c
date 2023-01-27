#include "string.h"
#include "./ui.h"
#include <stdlib.h>

void writeStr(char **content, int x, int y, char *str) {
    for(int ch=0; ch < strlen(str); ch++) {
        content[y][x +ch] = str[ch];
    }
}

struct screen *baseScreenBuilder(char *name, int id, char **(*renderer)(int, int, int)) {
    struct screen *screen = malloc(sizeof(struct screen));
    screen->renderer = renderer;
    screen->id = id;
    screen->name = malloc(sizeof(char) * strlen(name));
    strcpy(screen->name, name);
    return screen;
}

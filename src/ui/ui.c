#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "startMenu.h"
#include "string.h"
#include "stdbool.h"
#include "keystrokes.h"
#include "../c-TUI-framework/cTUIFramework.h"


struct theme algomusicTheme;
struct keystrokes currentAlgomusicKeyStrokes;

int currentTab;
int screenCount;
struct screen *screens[10];


void switchTab(int tab) {
    currentTab = tab;
    updateKeystrokes(screens[currentTab]->screenKeystrokes, &currentAlgomusicKeyStrokes);
}


void *getDataFromId(int id) {
    for (int screen = 0; screen < screenCount; screen++) {
        if(screens[screen]->id == id) {
            return(screens[screen]->data);
        }
    }
    return(NULL);
}


void addNewWindow(struct screen *(*initer)(int), int id) {
    screens[screenCount] = initer(id);
    screenCount++;
}


void removeWindow(int id) {
    bool found = false;
    for (int screen = 0; screen < screenCount; screen++) {
        if (screens[screen]->id == id) {
            free(screens[screen]->name);
            free(screens[screen]->data);
            free(screens[screen]->screenKeystrokes->keystrokeArray);
            free(screens[screen]->screenKeystrokes);
            free(screens[screen]);
            found = true;
            continue;
        }
        if (found) {
            screens[screen - 1] = screens[screen];
        }
    }
    screenCount--;
}


void startTUI() {
    initTUI();

    //defines keystrokes
    generateKeystrokes(&currentAlgomusicKeyStrokes);
    setKeystrokes(currentAlgomusicKeyStrokes);

    //define the tui theme
    algomusicTheme.splitBorders = 0;
    algomusicTheme.floatingWindowBorders = 0;
    algomusicTheme.topBarBorder = 0;
    algomusicTheme.sideEdgeBorder = 0;
    algomusicTheme.bottomBarBorder = 0;
    setTheme(algomusicTheme);

    addNewWindow(startMenuScreenIniter, 1);
    switchTab(0);
}


void _leftBarMaker(char *str) {
    strcpy(str, "idk left bar not implemented yet");
}


void _rightBarMaker(char *str) {
    strcpy(str, "idk right bar isnt implemented yet");
}


void _defineFloatingWindow(struct floatingWindow *floatingWindow) {
    floatingWindow->width = 0;
    floatingWindow->height = 0;
}


void updateTUI() {
    updateTUIKeystrokes();
    updateScreenSize();

    //main tui struct generation code
    struct TUI TUIStruct;

    //status bar defining code
    char *leftBar = malloc(sizeof(char) * 40);
    char *rightBar = malloc(sizeof(char) * 40);
    _leftBarMaker(leftBar);
    _rightBarMaker(rightBar);
    TUIStruct.barLeft = leftBar;
    TUIStruct.barRight = rightBar;

    //floating window defining code
    struct floatingWindow floatingWindow;
    _defineFloatingWindow(&floatingWindow);
    TUIStruct.floatingWindow = &floatingWindow;

    //main tab construction code
    setTab(currentTab);
    struct tab tabs[screenCount];
    for(int tab = 0; tab < screenCount; tab++) {
        tabs[tab].name = screens[tab]->name;
        if(tab == currentTab) {
            struct container content;
            tabs[tab].content = &content;
            tabs[tab].content->content = screens[tab]->renderer;
            tabs[tab].content->id = screens[tab]->id;
            tabs[tab].content->type = 0;
        }
    }
    TUIStruct.tabs = screenCount;
    TUIStruct.tab = tabs;

    //render the struct
    renderTUI(TUIStruct);
}


void quitTUI() {
    destroyTUI();
    free(currentAlgomusicKeyStrokes.keystrokeArray);
    for (int screen = 0; screen < screenCount; screen++) {
        free(screens[screen]->data);
        free(screens[screen]->name);
        free(screens[screen]);
    }
}

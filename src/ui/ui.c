#include "keystrokes.h"
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "startMenu.h"
#include "string.h"

int updateRendering = 0;
struct theme algomusicTheme;
struct keystrokes currentAlgomusicKeyStrokes;

int tabCount;
int currentTab;
struct screen screens[10];


void startTUI() {
    initTUI();

    //defines keystrokes
    currentAlgomusicKeyStrokes = generateKeystrokes();
    setKeystrokes(currentAlgomusicKeyStrokes);

    //define the tui theme
    algomusicTheme.splitBorders = 0;
    algomusicTheme.floatingWindowBorders = 0;
    algomusicTheme.topBarBorder = 0;
    algomusicTheme.sideEdgeBorder = 0;
    algomusicTheme.bottomBarBorder = 0;
    setTheme(algomusicTheme);

    tabCount = 1;
    currentTab = 0;
    screens[0] = *startMenuScreenIniter();
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
    struct tab tabs[tabCount];
    for(int tab = 0; tab < tabCount; tab++) {
        tabs[tab].name = screens[tab].name;
        if(tab == currentTab) {
            struct container container;
            screens[tab].maker(&container);
            tabs[tab].content = &container;
            printf("%i", tabs[tab].content->type);
        }
    }
    TUIStruct.tabs = tabCount;
    TUIStruct.tab = tabs;

    //render the struct
    renderTUI(TUIStruct);

    //free all malloced data
    for(int tab = 0; tab < tabCount; tab++) {
        if(tab == currentTab) {
            screens[tab].destroyer(tabs[tab].content);
        }
    }
}


void quitTUI() {
    destroyTUI();
    free(currentAlgomusicKeyStrokes.keystrokeArray);
}

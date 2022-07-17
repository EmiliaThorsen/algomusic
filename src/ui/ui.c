#include "../c-TUI-framework/src/cTUIframework.h"
#include "keystrokes.h"
#include <stdlib.h>


int updateRendering = 0;
struct TUI TUIStruct;
struct keystrokes currentAlgomusicKeyStrokes;

void startTUI() {
    initTUI();

    //defines keystrokes
    currentAlgomusicKeyStrokes = generateKeystrokes();
    setKeystrokes(currentAlgomusicKeyStrokes);
}


void updateTUI() {
    updateTUIKeystrokes();

  //if (updateRendering) {
  //    renderTUI(TUIStruct);
  //    updateRendering = 0;
  //}
}


void quitTUI() {
    destroyTUI();
    free(currentAlgomusicKeyStrokes.keystrokeArray);
}

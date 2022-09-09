#include "./controll.h"
#include <stdlib.h>


struct queueNode {
    struct queueNode *NextNode;
    struct event *data;
};


int *globalVariables;

struct queueNode *firstNode;
struct queueNode *lastNode;


void initControllSystem() {
    globalVariables = malloc(sizeof(int) * flagCount);
    firstNode = NULL;
    lastNode = NULL;
}


void setGlobalVariable(enum flags flag, int data) {
    globalVariables[flag] = data;
}


int getGlobalVariable(enum flags flag) {
    return globalVariables[flag];
}


void freeGlobalVariables() {
    free(globalVariables);
}


void newEvent(struct event *event) {
    struct queueNode *node = malloc(sizeof(struct queueNode));
    node->data = event;
    if(firstNode == NULL) {
        firstNode = node;
        lastNode = node;
    } else {
        lastNode->NextNode = node;
        lastNode = node;
    }
}


void *_getNextEvent() {
    if(firstNode == NULL) return NULL;
    struct queueNode *temp = firstNode;
    struct event *event = firstNode->data;
    if(firstNode->NextNode != NULL) {
        firstNode = firstNode->NextNode;
    } else {
        firstNode = NULL;
    }
    free(temp);
    return event;
}


void handleEvents() {
    struct event *event;
    while(1) {
        event = _getNextEvent();
        if(event == NULL) break;
        switch(event->type) {
            case 1: {
                struct basicFuncCall *funcCall = event->data;
                funcCall->func(funcCall->id);
                break;
            } default: {

                break;
            }
        }
    }
}

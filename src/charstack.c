#include "charstack.h"

#include <stdlib.h>

#define STACK_MEMORY sizeof(struct charStack)
#define NODE_MEMORY sizeof(struct charStackNode)

struct charStack* initCharStack() {
    struct charStack* stk = malloc(STACK_MEMORY);
    stk->top = NULL;

    return stk;
}

void pushChar(struct charStack* stk, char value) {
    struct charStackNode* newElem = malloc(NODE_MEMORY);
    newElem->value = value;

    if (!stk->top) {
        stk->top = newElem;
        stk->top->next = NULL;
    } else {
        newElem->next = stk->top;
        stk->top = newElem;
    }
}

char popChar(struct charStack* stk) {
    struct charStackNode* temp = stk->top->next;
    char value = stk->top->value;
    free(stk->top);
    stk->top = temp;

    return value;
}

char peekChar(struct charStack* stk) { return stk->top->value; }

void destroyCharStack(struct charStack* stk) {
    struct charStackNode* temp;
    while (stk->top != NULL) {
        temp = stk->top->next;
        free(stk->top);
        stk->top = temp;
    }
    free(stk);
}

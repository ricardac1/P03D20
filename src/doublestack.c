#include "doublestack.h"

#include <stdlib.h>

#define STACK_MEMORY sizeof(struct doubleStack)
#define NODE_MEMORY sizeof(struct doubleStackNode)

struct doubleStack* initDoubleStack() {
    struct doubleStack* stk = malloc(STACK_MEMORY);

    return stk;
}

void pushDouble(struct doubleStack* stk, double value) {
    struct doubleStackNode* newElem = malloc(NODE_MEMORY);
    newElem->value = value;

    if (!stk->top) {
        stk->top = newElem;
        stk->top->next = NULL;
    } else {
        newElem->next = stk->top;
        stk->top = newElem;
    }
}

double popDouble(struct doubleStack* stk) {
    struct doubleStackNode* temp = stk->top->next;
    double value = stk->top->value;
    free(stk->top);
    stk->top = temp;

    return value;
}

void destroyDoubleStack(struct doubleStack* stk) {
    struct doubleStackNode* temp;
    while (stk->top != NULL) {
        temp = stk->top->next;
        free(stk->top);
        stk->top = temp;
    }
    free(stk);
}

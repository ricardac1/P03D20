#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "charstack.h"
#include "check_exp.h"
#include "doublestack.h"

#define isDigit(c) (c >= '0' && c <= '9')
#define toDigit(c) (c - '0')

#define width 80
#define height 25

struct postfixNode {
    int value;
    char operand;
};

void printField(char* expression);
struct postfixNode* postfixExpression(char* expression, int* length);
double calculate(const struct postfixNode* const postfix, int length, double xValue);
double execute(char op, double first, double second);
int priority(char op);

int main() {
    char* expression = malloc(50);
    scanf("%50s", expression);

    if (!check_expression(expression)) {
        printField(expression);
    } else {
        printf("n/a");
    }

    free(expression);
    return 0;
}

void printField(char* expression) {
    int length;
    struct postfixNode* postfix = postfixExpression(expression, &length);
    double xStep = 4 * M_PI / (width - 1);
    double yStep = 2.0 / (height - 1);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double xValue = xStep * j;
            double yValue = calculate(postfix, length, xValue);
            int currentI = (int)round((1 + yValue) / yStep);
            if (i == currentI)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }

    free(postfix);
}

struct postfixNode* postfixExpression(char* expression, int* length) {
    struct charStack* stk = initCharStack();
    int len = strlen(expression);
    struct postfixNode* pNodes = malloc(50 * sizeof(struct postfixNode));
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isDigit(expression[i])) {
            pNodes[j].value = toDigit(expression[i]);  //======
            pNodes[j].operand = '\0';                  //======
            while (isDigit(expression[i + 1])) {
                pNodes[j].value = pNodes[j].value * 10 + toDigit(expression[++i]);
            }
            j++;
        } else if (expression[i] == 'x') {
            pNodes[j].value = 0;
            pNodes[j].operand = 'x';
            j++;
        } else if (i + 2 < len && expression[i] == 's' && expression[i + 1] == 'i' &&
                   expression[i + 2] == 'n') {
            pushChar(stk, 's');
            i += 2;
        } else if (i + 2 < len && expression[i] == 'c' && expression[i + 1] == 'o' &&
                   expression[i + 2] == 's') {
            pushChar(stk, 'c');
            i += 2;
        } else if (i + 2 < len && expression[i] == 't' && expression[i + 1] == 'a' &&
                   expression[i + 2] == 'n') {
            pushChar(stk, 't');
            i += 2;
        } else if (i + 2 < len && expression[i] == 'c' && expression[i + 1] == 't' &&
                   expression[i + 2] == 'g') {
            pushChar(stk, 'g');
            i += 2;
        } else if (i + 3 < len && expression[i] == 's' && expression[i + 1] == 'q' &&
                   expression[i + 2] == 'r' && expression[i + 3] == 't') {
            pushChar(stk, 'q');
            i += 3;
        } else if (i + 1 < len && expression[i] == 'l' && expression[i + 1] == 'n') {
            pushChar(stk, 'r');
            i++;
        } else if (expression[i] == '(') {
            pushChar(stk, expression[i]);
        } else if (expression[i] == ')') {
            while (stk->top != NULL && peekChar(stk) != '(') {
                pNodes[j].value = 0;
                pNodes[j].operand = popChar(stk);
                j++;
            }
            if (stk->top == NULL) {
                printf("Mismatched brackets");
                return NULL;
            }
            popChar(stk);
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' ||
                   expression[i] == '/') {
            char op = expression[i];

            if (op == '-' && (i == 0 || (i > 1 && priority(expression[i - 1]) != 100))) op = '~';

            while (stk->top != NULL && priority(op) <= priority(peekChar(stk))) {
                pNodes[j].value = 0;
                pNodes[j].operand = popChar(stk);
                j++;
            }
            pushChar(stk, op);
        }
    }
    while (stk->top != NULL) {
        pNodes[j].value = 0;
        pNodes[j].operand = popChar(stk);
        j++;
    }

    *length = j;
    destroyCharStack(stk);

    return pNodes;
}

double calculate(const struct postfixNode* postfix, int length, double xValue) {
    struct doubleStack* stk = initDoubleStack();

    for (int i = 0; i < length; i++) {
        struct postfixNode node = postfix[i];
        if (node.operand == '\0') {
            pushDouble(stk, (double)node.value);
        } else if (node.operand == '~') {
            double second = stk->top != NULL ? popDouble(stk) : 0;
            double first = 0;
            pushDouble(stk, execute('-', first, second));
        } else if (node.operand == 'x') {
            pushDouble(stk, xValue);
        } else if (node.operand == 's' || node.operand == 'c' || node.operand == 't' || node.operand == 'g' ||
                   node.operand == 'q' || node.operand == 'l') {
            double second = stk->top != NULL ? popDouble(stk) : 0;
            double first = 0;
            pushDouble(stk, execute(node.operand, first, second));
        } else {
            double second = stk->top != NULL ? popDouble(stk) : 0;
            double first = stk->top != NULL ? popDouble(stk) : 0;
            pushDouble(stk, execute(node.operand, first, second));
        }
    }

    double result = popDouble(stk);
    destroyDoubleStack(stk);

    return result;
}

double execute(char op, double first, double second) {
    double result;
    switch (op) {
        case '+': {
            result = first + second;
            break;
        }
        case '-': {
            result = first - second;
            break;
        }
        case '*': {
            result = first * second;
            break;
        }
        case '/': {
            result = first / second;
            break;
        }
        case 's': {
            result = sin(second);
            break;
        }
        case 'c': {
            result = cos(second);
            break;
        }
        case 't': {
            result = tan(second);
            break;
        }
        case 'g': {
            result = 1 / tan(second);
            break;
        }
        case 'q': {
            result = sqrt(second);
            break;
        }
        case 'l': {
            result = log(second);
            break;
        }
        default:
            result = 0;
    }

    return result;
}

int priority(char op) {
    int result;
    switch (op) {
        case '(': {
            result = 0;
            break;
        }
        case '+': {
            result = 1;
            break;
        }
        case '-': {
            result = 1;
            break;
        }
        case '*': {
            result = 2;
            break;
        }
        case '/': {
            result = 2;
            break;
        }
        case 's': {
            result = 2;
            break;
        }
        case 'c': {
            result = 2;
            break;
        }
        case 't': {
            result = 2;
            break;
        }
        case 'g': {
            result = 2;
            break;
        }
        case 'q': {
            result = 2;
            break;
        }
        case 'l': {
            result = 2;
            break;
        }
        default:
            result = 100;
    }

    return result;
}

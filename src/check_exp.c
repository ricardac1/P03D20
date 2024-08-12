#include <stdio.h>
#include <string.h>

int is_digit(char c) { return c >= '0' && c <= '9'; }

int is_operator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

int is_function(const char *str) {
    return strcmp(str, "cos") == 0 || strcmp(str, "x") == 0 || strcmp(str, "tan") == 0 ||
           strcmp(str, "ctg") == 0 || strcmp(str, "sin") == 0 || strcmp(str, "sqrt") == 0 ||
           strcmp(str, "ln") == 0;
}

int is_valid_char(char c) {
    return !is_digit(c) || is_function(&c) || is_operator(c) || c == '(' || c == ')' || c == '.' || c == 'x';
}

int check_expression(const char *expression) {
    int flag = 1;
    if (strlen(expression) == 0) {
        flag = 0;
    }

    for (int i = 0; (unsigned)i < strlen(expression); i++) {
        char c = expression[i];
        if (!is_valid_char(c)) {
            flag = 0;
        }
    }

    const char *functions[] = {"cos", "tan", "ctg", "sin", "sqrt", "ln", "x"};
    for (int i = 0; i < 7; i++) {
        const char *found = strstr(expression, functions[i]);
        while (found != NULL) {
            int pos = found - expression;
            if (pos > 0 && is_valid_char(expression[pos - 1])) {
                flag = 0;
            }
            if (!is_operator(expression[pos + strlen(functions[i])] &&
                             expression[pos + strlen(functions[i])] != '(')) {
                flag = 0;
            }
            found = strstr(found + strlen(functions[i]), functions[i]);
        }
    }

    return flag;
}
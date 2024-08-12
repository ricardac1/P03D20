struct charStackNode {
    char value;
    struct charStackNode* next;
};

struct charStack {
    struct charStackNode* top;
};

struct charStack* initCharStack();
void pushChar(struct charStack* stk, char value);
char popChar(struct charStack* stk);
char peekChar(struct charStack* stk);
void destroyCharStack(struct charStack* stk);

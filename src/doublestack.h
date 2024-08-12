struct doubleStackNode {
    double value;
    struct doubleStackNode* next;
};

struct doubleStack {
    struct doubleStackNode* top;
};

struct doubleStack* initDoubleStack();
void pushDouble(struct doubleStack* stk, double value);
double popDouble(struct doubleStack* stk);
void destroyDoubleStack(struct doubleStack* stk);
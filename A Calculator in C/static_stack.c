#include <stdlib.h>
#include <stdio.h>

typedef struct stack {
    int top;
    int size;
    int *array;
} 
stack;
stack *new_stack(int size) {
    int *array = (int*)malloc(size*sizeof(int));
    stack *stk = (stack*)malloc(sizeof(stack));
    //kod saknas
    stk->top = -1;
    stk->size = size;
    stk->array = array;
    
return stk;
}

void push(stack *stk, int val) {
    //kod saknas
    if (stk->top == stk->size-1)
    {
        printf("Stack Overflow");
    }
    stk->top++;
    stk->array[stk->top] = val;
    printf("Pushed %d onto the stack\n", val);
}

int pop(stack *stk) {
//kod saknas
    if (stk->top == -1)
    {
        printf("Stack Underflow");
        return -1;
    }
    int popped_item = stk->array[stk->top];
    stk->top--;
    return popped_item;
}

int main() {
stack *stk = new_stack(4);
    push(stk, 32);
    push(stk, 33);
    push(stk, 34);
    printf("pop : %d\n", pop(stk));
    printf("pop : %d\n", pop(stk));
    printf("pop : %d\n", pop(stk));
}
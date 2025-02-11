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
    if (stk->top == stk->size-1) {
        int size = stk->size*2; 
        int *copy = (int*)malloc(size*sizeof(int));

        for (int i = 0; i <= stk->top; i++) {
            copy[i] = stk->array[i];
        }
        stk->size = size;

        free(stk->array);
        stk->array = copy;
    }
    stk->top++;
    stk->array[stk->top] = val;
    printf("Pushed %d onto the stack\n", val);
}


int pop(stack *stk) { 
    if (stk->top == -1) {
        printf("Stack Underflow");
        return -1;
    }

    if (stk->size > 4 && stk->top == (stk->size)/4)
    {
       int size = (stk->size)/2;
       int *copy2 = (int*)malloc(size*sizeof(int));
       for (int i = 0; i <= stk->top; i++) {
        copy2[i] = stk->array[i];
       }       
       stk->size = size;

       free(stk->array);
       stk->array = copy2;
    }
    
    int popped_item = stk->array[stk->top];
    stk->top--;
    return popped_item;
}

int main() {
    stack *stk = new_stack(4);
    int n = 10;
    for(int i = 0; i < n; i++) {
        push(stk, i+30);
    }
    for(int i = 0; i < stk->top; i++) {
        printf("stack[%d] : %d\n", i, stk->array[i]);
    }
    int val = pop(stk);
    while(val != 0) { // assuming 0 is returned when the stack is empty
        printf("pop : %d\n", val);
        val = pop(stk);
    }
}*/
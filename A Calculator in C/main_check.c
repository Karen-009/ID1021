int main() {
stack *stk = stack(4);
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
}
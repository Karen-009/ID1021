#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
    (t_stop->tv_sec - t_start->tv_sec)*1000000000;
} 

typedef struct cell {
    int value;
    struct cell *tail;
} cell;

typedef struct linked {
    cell *first;
} linked;

linked *linked_create() {
    linked *new = (linked*)malloc(sizeof(linked));
    new->first = NULL;
    return new;
}

void linked_free(linked *lnk) {
    cell *nxt = lnk->first;
    while (nxt != NULL) {
        cell *tmp = nxt->tail;
        free(nxt);
        nxt = tmp;
    }
    free(lnk);
}

void add (linked *lnk, int item){
    cell* new_cell = (cell*) malloc (sizeof(cell));
    new_cell -> value = item;
    new_cell -> tail = lnk -> first;
    lnk -> first = new_cell;
}

void printList(linked* list){
    cell* current = list -> first;
    while (current != NULL)
    {
        printf("%d -> ", current->value);
        current = current->tail;
    }
    printf("NULL\n");
    
}

linked *linked_init(int n) {
    linked *a = linked_create();
    for (int i = 0; i < n; i++) {
        add(a, i);
    }
    return a;
}

int main (){
struct timespec t_start, t_stop;
long total_time = 0;

linked *list = linked_create();
int iterations = 1000;

add(list, 4);
add(list, 9);
add(list, 14);
for (size_t i = 0; i < iterations; i++)
{
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    add(list, 20);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    total_time += wall;

}
long average_time = total_time / iterations;
printf("Average time: %ld ns\n", average_time);

linked_free(list);
return 0;
}
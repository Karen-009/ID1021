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

void linked_append(linked *a, linked *b) {
    if (b->first == NULL) {
        return;
    }

    cell *nxt = a->first;
    cell *prv = NULL;
    while(nxt != NULL) {
        prv = nxt;
        nxt = nxt->tail;
    }

    if (prv != NULL){
        prv -> tail = b -> first;
    } else {
        a -> first = b ->first;
    }

    b->first = NULL;
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

int main (){ // the constant sizee was 10
struct timespec t_start, t_stop;
long total_time = 0;
int iterations = 1000;
int array_a_length = 10;
int array_b_length = 400;

for (size_t i = 0; i < iterations; i++)
{
    linked *list1 = linked_create();
        for (size_t j = 0; j < array_a_length; j++) {
            add(list1, 20);
        }
    linked *list2 = linked_create();

    for (size_t j = 0; j < array_b_length; j++) {
        add(list2, 13);
    }

    clock_gettime(CLOCK_MONOTONIC, &t_start);
    linked_append(list1, list2);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    total_time += wall;
    linked_free(list1);
    linked_free(list2);
}

long average_time = total_time / iterations;
printf("Average time: %ld ns\n", average_time);

return 0;
}
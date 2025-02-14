#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

bool linked_find(linked *lnk, int item){
    cell *current = lnk -> first;

    while (current != NULL)
    {
        if (current -> value == item)
        {
            return true;
        }
        current = current -> tail;
     }
     return false;
}

void add (linked *lnk, int item){
    cell* new_cell = (cell*) malloc (sizeof(cell));
    new_cell -> value = item;
    new_cell -> tail = lnk -> first;
    lnk -> first = new_cell;
}

int main (){
    linked *list = (linked *)malloc(sizeof(linked));
    list -> first = NULL; // initiating an empty list
    add(list, 4);
    add(list, 9);
    add(list, 14);
    add(list, 20);

    int item = 9;
    if (linked_find(list, item))
    {
        printf("The value %d is in the list.\n", item);
    } else {
        printf("The value %d is not in the list.\n", item);
    }
    
    linked_free(list);
    return 0;
}
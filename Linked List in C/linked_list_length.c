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

int length(linked *lnk){
    int length_list = 0;
    cell *current = lnk -> first;
    while (current != NULL)
    {
        length_list ++;
        current = current -> tail;
    }
    return length_list;
    
}

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

int main (){
    linked *list = (linked *)malloc(sizeof(linked));
    list -> first = NULL; // initiating an empty list
    add(list, 4);
    add(list, 9);
    add(list, 14);
    add(list, 20);
    
    int length_of_list = length(list);

    printf("The length is: %d\n", length_of_list);
    linked_free(list);
    return 0;
}
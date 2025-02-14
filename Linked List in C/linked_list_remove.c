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

void add (linked *lnk, int item){
    cell* new_cell = (cell*) malloc (sizeof(cell));
    new_cell -> value = item;
    new_cell -> tail = lnk -> first;
    lnk -> first = new_cell;
}

void linked_remove(linked *lnk, int item){
    cell *current = lnk -> first;
    cell *previous = NULL;
    while (current != NULL)
    {
        if (current -> value == item)
        {
            if (previous == NULL)
            {
                lnk -> first = current -> tail;
            } else {
                previous->tail = current->tail;
            }
        free(current);
        return;
        }
    previous = current;
    current = current -> tail;
    }
    printf("Value %d not found in the list.\n", item);
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


int main (){
    linked *list = (linked *)malloc(sizeof(linked));
    list -> first = NULL; // initiating an empty list
    add(list, 4);
    add(list, 9);
    add(list, 14);
    add(list, 20);

    printf("Original List:\n");
    printList(list);

    int item = 9;
    linked_remove(list, item);

    printf("List after removing %d:\n", item);
    printList(list);
    linked_free(&list);
    return 0;
}
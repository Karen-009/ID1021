#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
    (t_stop->tv_sec - t_start->tv_sec)*1000000000;
} 

bool unsorted_search(int array[], int length, int key) {
    for (int index = 0; index < length ; index++) {
        if (array[index] == key) {
return true;
}
    }
return false;
}

struct timespec t_start, t_stop;

long search(int length, int key) {
int *array = (int*)malloc(length*sizeof(int));
for (int i = 0; i < length; i++) array[i] = rand()%(length);

clock_gettime(CLOCK_MONOTONIC, &t_start);
unsorted_search(array, length, key);
clock_gettime(CLOCK_MONOTONIC, &t_stop);
long wall = nano_seconds(&t_start, &t_stop);
return wall;
}

int main() {
    int sizes[] = {125000, 125000*2, 125000*3, 125000*4, 125000*5, 125000*6, 125000*7, 125000*8};
     int key = rand();

    int k = 10;
    for (int i = 0; i < 8; i++) {
    int n = sizes[i];
    long min = LONG_MAX;
        for (int j = 0; j < k; j++) {
            long wall = search(n, key);
            if (wall < min){
                min = wall;
            }
        }
    printf("%d %lo ns\n", n, min);
    }
}
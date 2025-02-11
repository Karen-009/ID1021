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

bool recursive(int array[], int length, int key, int first, int last) {
    int mid = (first+last)/2;
    if (array[mid] == key) {
            return true;
    }
    if (array[mid] < key && mid < last) {
        recursive(array, length, key, mid+1, last);
    }

    if (array[mid] > key && mid > first) {
        recursive(array, length, key, first, mid);

    }
    return false;
}

int *sorted(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    int nxt = 0;
    for (int i = 0; i < n ; i++) {
        nxt += rand()%10 + 1;
        array[i] = nxt;
    }
    return array;
}

struct timespec t_start, t_stop;
long search(int length, int key) {
    int *array = sorted(length);
    int last = length-1;
    int first = 0;

    clock_gettime(CLOCK_MONOTONIC, &t_start);
    recursive(array, length, key, first, last);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    free(array);
    return wall;
}

int main() {
    int key = rand();
    int sizes[] = {125000, 125000*2, 125000*3, 125000*4, 125000*5, 125000*6, 125000*7, 125000*8};
    int k = 1000;
    for (int i = 0; i < 8; i++) {
    int n = sizes[i];
    long min = LONG_MAX;
        for (int j = 0; j < k; j++) {
            long wall = search(n, key);
            if (wall < min){
                min = wall;
            }
        }
    printf("%d %0.2f ns\n", n, (double)min);
    }
}
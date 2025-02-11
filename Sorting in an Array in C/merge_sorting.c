#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
    (t_stop->tv_sec - t_start->tv_sec)*1000000000;
} 

void sort(int *org, int *aux, int lo, int hi);
void merge(int *org, int *aux, int lo, int mid, int hi);

int main(){
    struct timespec t_start, t_stop;
    long total_time = 0;
    int size = 1000;
    int array [size];
    int iterations = 10;

    for (int k = 0; k < 1; k++)
    {
            srand(time(NULL));
        for(int i = 0; i < size; i ++){
            array [i] = rand()%1000;
        }
        int *aux = (int *)malloc(size * sizeof(int));
        for ( int i = 0; i < iterations; i++){
            for(int j = 0; j < size; j ++){
                array [j] = rand()%1000;
            }
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            sort(array, aux, 0, size-1);
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            total_time += wall;
        }
        long average_time = total_time / iterations;
        printf("Average time to sort the array using merge sort: %ld ns\n", average_time);
        total_time = 0;

    }
            return 0;
}

void sort(int *org, int *aux, int lo, int hi) {
    if (lo != hi) {
        int mid = (lo + hi)/2;
        sort(org, aux, lo, mid);
        sort(org, aux, mid+1, hi);
        merge(org, aux, lo, mid, hi);
    }
}

void merge(int *org, int *aux, int lo, int mid, int hi) {
    for (int i = lo; i <= hi; i++) {
        aux[i] = org[i];
    }
    int i = lo;
    int j = mid+1;
    for ( int k = lo; k <= hi; k++) {
        if (i > mid) {
            org[k] = aux[j++];
        } 
        else if(j > hi) {
            org[k] = aux[i++];
        }
        else if (i <= j)
        {
            org[k] = aux[i++];
        }
        else
        {
            org[k] = aux[j++];
        }
    }
}
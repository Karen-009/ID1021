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

void insert_sorting(int array[], int size);


int main(){
    struct timespec t_start, t_stop;
    long total_time = 0;
    int size = 16000;
    int array [size];
    int iterations = 10;

    for (int k = 0; k < 1; k++)
    {
            srand(time(NULL));
        for(int i = 0; i < size; i ++){
            array [i] = rand()%1000;
        }
        for ( int i = 0; i < iterations; i++){
            for(int j = 0; j < size; j ++){
                array [j] = rand()%1000;
            }
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            insert_sorting(array,size);
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            total_time += wall;
        }
        long average_time = total_time / iterations;
        printf("Average time to sort the array using insertion sort: %ld ns\n", average_time);
        long total_time = 0;
    }
            return 0;
}

void insert_sorting(int array[], int size){
    for (int i = 1; i < size; i++)
    {
        int key = array[i];
        int j;
        for (j = i-1; j >=0 && array[j] > key; j--)
        {
            array[j + 1] = array[j];
        }
    array[j+1] = key;
    }
}

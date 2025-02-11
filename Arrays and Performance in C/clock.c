#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
return (t_stop->tv_nsec - t_start->tv_nsec) +
(t_stop->tv_sec - t_start->tv_sec)*1000000000;
} 

int main() {
    struct timespec t_start, t_stop;
    const int iterations = 1000;
    for(int i = 0; i < 10; i++) { 
        long total_time = 0;
        for(int j = 0; j < iterations; j++){  //Inner for loop 
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            total_time += nano_seconds(&t_start, &t_stop);
        }
    long average_time = total_time/iterations; //Computs the average time for each iteration
    printf("Iteration %d: Average time per clock_getttime pair: %ld ns\n", i+1, average_time);
    }
    return 0;
}
/*
Name: Yi Qian Goh
Date: Thursday, 25 April 2024
Title: Lab3 Step 8 - Fixes bug in step7.c
Description: Passes value of i rather than the address of i so that the iteration printed out is correct.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {
    int i;
    int thread_args[NTHREADS];
    for (i = 0; i < NTHREADS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, go, &thread_args[i]);
    }
    for (i = 0; i < NTHREADS; i++) {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n", (int)(unsigned long) pthread_self(), *(int *)arg);
    return 0;
}
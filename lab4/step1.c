/*
Name: Yi Qian Goh
Date: thursday, 25 April 2024
Title: Lab4 Step 1 - Compile and run the modified program several times. How many threads complete their go
function? Explain the reasoning behind the program's behavior.
Description: Not all threads complete the go function because some threads cannot complete before the next
            thread goes.
*/

/*Sample C program for Lab 4*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void *go(void *);
#define NTHREADS 20
pthread_t threads[NTHREADS];
int main() {
    int i;
    for (i = 0; i < NTHREADS; i++) 
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n", (int)(unsigned
    long)pthread_self(), (int)(unsigned long)(size_t *)arg);
    sleep(15);  
    pthread_exit(0);
}
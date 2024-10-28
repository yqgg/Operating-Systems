/*
Name: Yi Qian Goh
Date: Thursday, 8 May 2024 
Title: Lab5, Step 2 - Modify threadSync.c in Step 1 using mutex locks.
Description: This program creates multiple threads, each of which attempts 
            to enter a critical section protected by a mutex lock. The 
            threads are spawned in a loop, and each thread prints its 
            identifier before attempting to acquire the mutex lock. Once 
            inside the critical section, the thread prints a message indicating 
            it's running in the critical section before releasing the mutex 
            lock. The program also registers a signal handler to clean up 
            resources (destroy the mutex) when it receives a SIGINT signal, 
            usually triggered by pressing Ctrl+C, ensuring proper termination.

*/

/*
pthread_mutex_t lock; //Declare a lock
int pthread_mutex_init(&lock, NULL); //Create a lock
int pthread_mutex_lock(&lock); //Acquire a lock
int pthread_mutex_unlock(&lock); //Release a lock
int pthread_mutex_destroy(&mutex); //Delete a lock
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include<unistd.h>
#include <signal.h>

#define NTHREADS 10
void *go(void *arg);
void cleanup(int sigtype);

pthread_t threads[NTHREADS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    signal(SIGINT, cleanup);
    int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++) 
        pthread_join(threads[i],NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}

void *go(void *arg) {
    printf("Thread %d is now attempting ....\n",  (int)(size_t)arg);
    pthread_mutex_lock(&mutex);
    sleep(1);
    printf("Thread %d is running in its Critical Section........\n",  (int)(size_t)arg);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void cleanup(int sigtype){
    pthread_mutex_destroy(&mutex);
    printf("\n Terminating\n");
    exit(0);
}
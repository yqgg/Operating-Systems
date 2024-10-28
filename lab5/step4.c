/*
Name: Yi Qian Goh
Date: Thursday, 8 May 2024 
Title: Lab5, Step 4 - implement producer consumer problem using mutex locks and
                        condition variables to prevent wasteful busy waiting
Description: This program implements a simple producer-consumer problem using 
            pthreads in C. It creates two threads, one for the producer and one 
            for the consumer. The producer generates random numbers and inserts 
            them into a shared buffer, while the consumer removes items from 
            the buffer. Both threads synchronize their access to the buffer using 
            mutex locks and condition variables to ensure that the producer doesn't 
            insert into a full buffer and the consumer doesn't remove from an 
            empty buffer.

*/


/*
pthread_mutex_t lock; //Declare a lock
int pthread_mutex_init(&lock, NULL); //Create a lock
int pthread_mutex_lock(&lock); //Acquire a lock
int pthread_mutex_unlock(&lock); //Release a lock
int pthread_mutex_destroy(&mutex); //Delete a lock
pthread_cond_t cond; //Create a condition variable
int pthread_cond_wait(&cond, &lock); //Unlocks lock then relocks it on a signal
int pthread_cond_signal(&cond); //Signals at least one other thread waiting on cond
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include<unistd.h>
#include <signal.h>

#define N 10
void *producer(void *arg);
void *consumer(void *arg);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
int buffer[N];
int in = 0;
int out = 0;

int main(){
    pthread_t p_thread, c_thread; //producer and consumer thread
    pthread_create(&p_thread, NULL, (void*)producer, NULL);
    pthread_create(&c_thread, NULL, (void*)consumer, NULL);
    pthread_join(p_thread, NULL);
    pthread_join(c_thread, NULL);
    return 0;
}

void *producer(void *arg) {
    int item, i;
    for(i = 0; i < N; i++) {
        item = rand() %10;
        pthread_mutex_lock(&mutex); //lock mutex
        while(sizeof(buffer) == N) { //while buffer is full, wait.
            pthread_cond_wait(&empty, &mutex); //wait for empty signal from other thread
        }
        //add item to buffer
        buffer[in] = item;
        printf("Producer: Insert %d at index %d\n",buffer[in],in);
        in = (in + 1 ) % N;

        pthread_cond_signal(&full); //signals other thread waiting for full
        pthread_mutex_unlock(&mutex); //unlock mutex
        //sleep(1);
    }
}

void *consumer(void *arg){
    int item, i;
    for(i = 0; i < N; i++) {
        pthread_mutex_lock(&mutex); //lock mutex
        while(sizeof(buffer) == 0) { //while buffer is empty, wait.
            pthread_cond_wait(&full, &mutex); //wait for empty signal from other thread
        }
        //add item to buffer
        item = buffer[out];
        printf("Consumer: Remove %d at index %d\n", item, out);
        out = (out + 1 ) % N;

        pthread_cond_signal(&empty); //signals other thread waiting for empty
        pthread_mutex_unlock(&mutex); //unlock mutex
        //sleep(1);
    }
}
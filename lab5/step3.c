/*
Name: Yi Qian Goh
Date: Thursday, 8 May 2024 
Title: Lab5, Step 3 - implement producer consumer problem using sempaphores.
Description: This program implements a producer-consumer problem using 
            pthreads in C, but it uses semaphores for synchronization. It 
            creates two semaphores (full and empty) to control the number 
            of items in the buffer and one semaphore (mutex) to ensure 
            mutual exclusion when accessing the buffer. The producer generates 
            random numbers and inserts them into the buffer, while the 
            consumer removes items from the buffer. Semaphores are used to 
            control access to the buffer, ensuring that the producer doesn't 
            insert into a full buffer and the consumer doesn't remove from an 
            empty buffer.

*/
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define N 3
void *producer(void *arg);
void *consumer(void *arg);

sem_t full, empty, mutex;
int buffer[N];
int in = 0;
int out = 0;

int main(){
    sem_init(&full,0,0);
    sem_init(&empty,0,N);
    sem_init(&mutex, 0, 1);

    pthread_t p_thread, c_thread;
    pthread_create(&p_thread, NULL, producer, NULL);
    pthread_create(&c_thread, NULL, consumer, NULL);
    pthread_join(p_thread, NULL);
    pthread_join(c_thread, NULL);

    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutex);

   	return 0;
}

void *producer(void *arg){
    int item, i;
    for(i = 0; i < N; i++) {
        item = rand() %10;
        sem_wait(&empty);
        sem_wait(&mutex);
            buffer[in] = item;
            printf("Producer: Insert %d at index %d\n",buffer[in],in);
            in = (in + 1 ) % N;
        sem_post(&mutex);
        sem_post(&full);
        //sleep(1);
    }
}

void *consumer(void *arg){
    int item, i;
    for(i = 0; i <N; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
            item = buffer[out];
            printf("Consumer: Remove %d at index %d\n", item, out);
            out = (out + 1 ) % N;
        sem_post(&mutex);
        sem_post(&empty);
        //sleep(1);
    }
}
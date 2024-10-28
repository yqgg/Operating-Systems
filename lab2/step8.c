/*
Name: Yi Qian Goh
Date: Thursday, 11 April 2024
Title: Lab2 – step 8
Description: This program creates two concurrent threads called a parent_thread and child_thread.
             Similar to step3.c but creates threads rather than processes. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *parent_thread(void *arg) {
    int n = *((int *)arg);
    int i;
    for (i = 0; i < 10; i++) {
        printf("\tI am the parent Thread displaying iteration %d \n", i);
        usleep(n);
    }
    pthread_exit(NULL);
}

void *child_thread(void *arg) {
    int n = *((int *)arg);
    int i;
    for (i = 0; i < 10; i++) {
        printf("I am the child Thread displaying iteration %d\n", i);
        usleep(n);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <delay> \n", argv[0]);
        exit(0);
    }

    int n = atoi(argv[1]); // n microseconds is taken as command-line argument
    pthread_t parent_tid, child_tid;

    printf("\n Before creating threads.\n");

    // Create parent thread
    if (pthread_create(&parent_tid, NULL, parent_thread, &n) != 0) {
        perror("Failed to create parent thread");
        exit(EXIT_FAILURE);
    }

    // Create child thread
    if (pthread_create(&child_tid, NULL, child_thread, &n) != 0) {
        perror("Failed to create child thread");
        exit(EXIT_FAILURE);
    }

    // Wait for parent thread to finish
    if (pthread_join(parent_tid, NULL) != 0) {
        perror("Failed to join parent thread");
        exit(EXIT_FAILURE);
    }

    // Wait for child thread to finish
    if (pthread_join(child_tid, NULL) != 0) {
        perror("Failed to join child thread");
        exit(EXIT_FAILURE);
    }

    printf("Both threads have completed their tasks.\n");

    return 0;
}
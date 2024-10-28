/*
Name: Yi Qian Goh
Date: Thursday, 25 April 2024
Title: Lab3 Step 6 - Write a C program that implements some form of producer-consumer message communication
using a shared memory segment. 
Description: This program will ask the user to input a string to be written onto the shared memory segment.
            Then, it will return what was written onto the shared memory.
*/
#include <stdio.h>
/* printf, stderr */
#include <stdlib.h>
/* atoi */
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<errno.h>
#include<stdbool.h>

#define BUFFER_SIZE 100
key_t KEY = 1243;

//create shared message segment struct type
struct shmseg {
    char buff[BUFFER_SIZE];
    bool writingComplete;
};

int main() {
    int shmid;
    struct shmseg *shs;

    //create segment shared among all processes with the same key
    if((shmid = shmget(KEY, sizeof(struct shmseg), IPC_CREAT | 0666)) == -1) {
        perror("error at shmget");
        exit(EXIT_FAILURE);
    }

    //attach all involved processes to the segment
    if((shs = shmat(shmid, 0, 0))== (void*) - 1) {
        perror("error at shmat");
        exit(EXIT_FAILURE);
    }

    if(fork() == 0) { //child process, consumer, removes content from shared mem
        char *str = "This is the consumer";
        printf("Consumer begin.\n");
        //write content into shared memory segment
        while(shs->writingComplete == false) {}
        printf("Consumer removed this string from the shared memory segment: %s\n", shs->buff);
        shs->writingComplete = false;

        //detach shared segment
        if(shmdt(shs) == -1) {
            perror("error at shmdt");
            exit(EXIT_FAILURE);
        }
    } else { //parent process, producer, writing to shared mem    
        printf("Producer begin.\n");
        sleep(1); //parent process sleep to give consumer time to begin
        //write content into shared memory segment
        printf("Enter string to write to the shared memory segment: ");
        fgets(shs->buff, BUFFER_SIZE, stdin);
        printf("Producer put this string in the shared memory segment: %s", shs->buff);
        shs->writingComplete = true;

        //detach shared segment
        if(shmdt(shs) == -1) {
            perror("error at shmdt");
            exit(EXIT_FAILURE);
        }

        //wait for child process to complete
        wait(0);
    }
    return 0;
}
/*
Name: Yi Qian Goh
Date: Thursday, 11 April 2024
Title: Lab2 – step 6
Description: This program is similar to step5.c except it creates 5 processes
            including the initial program itself. Each process has a different 
            delay time taken from command line arguments.
*/
#include <stdio.h>
/* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>
/* fork */
#include <stdlib.h>
/* atoi */
#include <errno.h>
/* errno */
/* main function */
int main(int argc, char *argv[]) {
    //user should enter 5 numbers, each number is the delay time between each iteration in each process
    if (argc != 6){
        printf ("Usage: %s <delay> <delay> <delay> <delay> <delay>\n",argv[0]);
        exit(0);
    }
    pid_t pid1, pid2, pid3, pid4;
    int i, j;
    int count = 0;
    int numProcesses = argc-1;
    int delay[numProcesses]; //create an array to store the delay times entered int he command line
    for(j = 0; j<numProcesses; j++ ) {
        delay[j] = atoi(argv[j+1]);
    }
    printf("\n Before forking\n");
    pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid1){ // Parent process: pid is > 0
        pid2 = fork(); //will only fork a child process from only the parent pid1
        if(pid2) { //parent process pid2
            for (i=0;i<10;i++) {
                printf("\tI am parent process PID %d displaying iteration %d (delay %d microseconds).\n", getpid(), i, delay[0]);
                usleep(delay[0]);
            }
            pid3 = fork(); //will fork a child process from only the parent pid2
            if(pid3 == 0) { //only need to check for the child process because this process has the same parent as pid2
                for (i=0;i<10;i++) {
                    printf("I am child process PID %d displaying iteration %d (delay %d microseconds).\n", getpid(), i, delay[1]);
                    usleep(delay[1]);
                }
            }
        } else { //child process of pid2
            for (i=0;i<10;i++) {
                printf("I am child process PID %d displaying iteration %d (delay %d microseconds).\n", getpid(), i, delay[2]);
                usleep(delay[2]);
            }
        }
    } else { // Child process: pid is == 0
        pid4 = fork(); //will only fork a child process from only the child process of pid1
        if(pid4) { //parent process pid4
            for (i=0;i<10;i++) {
                printf("\t\tI am parent process PID %d displaying iteration %d (delay %d microseconds).\n", getpid(), i, delay[3]);
                usleep(delay[3]);
            }
        } else { //child process of pid4
            for (i=0;i<10;i++) {
                printf("I am child process PID %d displaying iteration %d (delay %d microseconds).\n", getpid(), i, delay[4]);
                usleep(delay[4]);
            }
        }
    }
    wait(0);
    wait(0);
    wait(0);
    return 0;
}
/*
Name: Yi Qian Goh
Date: Thursday, 11 April 2024
Title: Lab2 – step 5
Description: This program is similar to step2.c except that this program creates 4 processes instead of 2.
             Each process has a different delay time taken from command line arguments.
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
    //user should enter 4 numbers, each number is the delay time between each iteration in each process
    if (argc != 5){
        printf ("Usage: %s <delay> <delay> <delay> <delay>\n",argv[0]);
        exit(0);
    }
    pid_t pid;
    int i, j;
    int count = 0;
    int numProcesses = argc-1;
    int delay[numProcesses]; //create an array to store the delay times entered int he command line
    for(j = 0; j<numProcesses; j++ ) {
        delay[j] = atoi(argv[j+1]);
    }
    printf("\n Before forking\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid){ // Parent process: pid is > 0
        pid = fork(); //will fork a child process from only the processes with pid>0
        if(pid) {
            for (i=0;i<10;i++) {
                printf("\tI am parent process PID %d displaying iteration %d (delay %d microseconds).\n", pid, i, delay[0]);
                usleep(delay[0]);
            }
        } else {
            for (i=0;i<10;i++) {
                printf("I am child process PID %d displaying iteration %d (delay %d microseconds).\n", pid, i, delay[1]);
                usleep(delay[1]);
            }
        }
    } else { // Child process: pid is == 0
        pid = fork(); //will fork a child process from only the processes with pid==0
        if(pid) {
            for (i=0;i<10;i++) {
                printf("\tI am parent process PID %d displaying iteration %d (delay %d microseconds).\n", pid, i, delay[2]);
                usleep(delay[2]);
            }
        } else {
            for (i=0;i<10;i++) {
                printf("I am child process PID %d displaying iteration %d (delay %d microseconds).\n", pid, i, delay[3]);
                usleep(delay[3]);
            }
        }
    }
    wait(0);
    wait(0);
    return 0;
}



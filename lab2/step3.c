/*
Name: Yi Qian Goh
Date: Thursday, 11 April 2024
Title: Lab2 – step 3
Description: This program is similar to step1.c except that this program takes
            a command line argument as the delay time between each iteration. 
*/
/* C program to demonstrate the use of fork()*/
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
    if (argc != 2){
        printf ("Usage: %s <delay> \n",argv[0]);
        exit(0);
    }
    pid_t pid;
    int i;
    int n = atoi(argv[1]); // n microseconds is taken as command-line argument
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid){
        // Parent process: pid is > 0
        for (i=0;i<10;i++) {
            printf("\tI am the parent Process displaying iteration %d \n",i);
            usleep(n);
        }
    }
    else{
        // Child process: pid = 0
        for (i=0;i<10;i++) {
            printf("I am the child process displaying iteration %d\n",i);
            usleep(n);
        }
    }
    return 0;
}
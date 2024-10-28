/*
Name: Yi Qian Goh
Date: Thursday, 11 April 2024
Title: Lab2 – step 7
Description: This program creates two process, a parent and child process.
             The child process runs the ls command and the parent process waits until 
             the child process terminates before it exits.
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
#include <sys/types.h>
#include <sys/wait.h>
/* main function */
int main() {
    pid_t pid;
    int i, n = 3000; // n is a delay in microseconds inserted in parent and child iterations
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if(pid == 0) {
        execlp("/bin/ls", "ls", 0);
    } else {
        wait(0);
        printf("Child has completed the task! \n");
        exit(0);
    }
    return 0;           
}
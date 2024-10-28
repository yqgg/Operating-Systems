/*
Name: Yi Qian Goh
Date: Thursday, 25 April 2024
Title: Lab3 Step 5 - Write a C program that implements some form of producer-consumer message communication
Description: This program will ask the user to enter their name. Although, it can be any string inputed by
            the keyboard. Then the upstream end of pipe will print out the received inputted string.
*/

/*
using pipes.*/
#include <stdio.h>
/* printf, stderr */
#include <unistd.h>
/* fork */
#include <stdlib.h>
/* atoi */


int main(int argc, char *argv[]) {
    int fds[2];
    int BUFFER_SIZE = 100;
    char buff[BUFFER_SIZE];
    pipe(fds);
    if(fork()==0) { //child process, the consumer
        dup2(fds[0], 0); //set as stdout, upstream
        close(fds[1]); //close downstream
        read(fds[0], buff, BUFFER_SIZE);
        printf("Consumer removed this string from the buffer: %s\n", buff);
    } else { //parent process, the producer
        close(fds[0]); //close upstream
        printf("Enter your name: ");
        fgets(buff, BUFFER_SIZE, stdin);
        write(fds[1], buff, BUFFER_SIZE);
        printf("Producer put this string in the buffer: %s\n", buff);
        exit(0);
    }
    close(fds[0]);
    close(fds[1]);
}
/*
Name: Yi Qian Goh
Date: Thursday, 25 April 2024
Title: Lab3 Step 4 - Write a C program that implements the shell command: cat /etc/passwd | grep root.
Description: This program is similar to step1.c. However, it implements different shell commands. 
            "cat /etc/passwd" This command prints the contents of the file /etc/passwd to the standard output. 
            The /etc/passwd file typically contains information about user accounts on the system, including 
            usernames, user IDs, group IDs, home directories, and shell types.

            "|" This is a pipe operator in the shell. It connects the standard output (stdout) of the command 
            on its left (cat /etc/passwd) to the standard input (stdin) of the command on its right (grep root).

            "grep root" This command filters the input it receives from the cat /etc/passwd command using a pattern 
            match. Specifically, it searches for lines that contain the string "root". In the context of /etc/passwd, this 
            typically selects the line(s) corresponding to the root user account.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
int main() {
    int fds[2];
    pipe(fds);
    /*pid_t cat, grep;
    cat = fork();
    if (cat < 0) { //error checking for fork process cat
        fprintf(stderr, "can't fork cat, error %d\n", errno);
        exit(0);
    }*/
    if(fork() == 0) { //child process
        dup2(fds[1], 1);  //fds[1] will become a standard output, this the upstream end
        close(fds[0]); //close the opposite end
        execlp("cat", "cat", "/etc/passwd",0);
    } else if (fork() == 0) {
        dup2(fds[0], 0); //fds[0] will become a standard input, this is the downstream end
        close(fds[1]); //close the opposite end
        execlp("grep", "grep", "root", 0);
    } else {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}
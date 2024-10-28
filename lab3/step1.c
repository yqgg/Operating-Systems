/*
Name: Yi Qian Goh
Date: Thursday, 25 April 2024
Title: Lab3 Step 1 - Compile and run the following program and write your observations. Then, modify it to pass the -l
option to the ls command.
Description: This program uses fork to create processes to input command line prompts "ls" and "-l"
                through the pipe. The file details and permission configuration of all files in this
                directiory should be outputted.
                For example, "-rw-r--r--. 1 ygoh2 dip    654 Apr 18 10:20 step1.c"
*/

/*Sample C program for Lab 3 step 1*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//main
int main() {
    int fds[2];
    pipe(fds);
    /*child 1 duplicates downstream into stdin */
    if (fork() == 0) {
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("more", "more", 0);
    }
    /*child 2 duplicates upstream into stdout */
    else if (fork() == 0) {
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("ls", "ls", "-l",0);
    }
    else { /*parent closes both ends and wait for children*/
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}
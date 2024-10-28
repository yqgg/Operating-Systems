/*
Name: Yi Qian Goh
Date: Thursday, 25 April 2024
Title: Lab3 Step 2 - Compile and run the following program and write your observations.
Description: This program implements piping and forking. On the upstream end of the pipe, the
                process inputs all command line arguments given when executing the program. 
                At the downstream end, the pipe outputs the received input into the process
                at the downstream end. Thus, the output should look like this 
                "   Writer on the upstream end of the pipe -> # arguments 

                    Reader on the downstream end of the pipe 
                    . / 2 (whatever output)"
*/


/*Sample C program for Lab 3 step 2*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
// main
int main(int argc,char *argv[]){
    int fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);
    if (fork()==0){
        printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
        close(fds[0]);
        for(i=0;i<argc;i++){
            write(fds[1],argv[i],strlen(argv[i]));
        }
        exit(0);
    }else if(fork()==0){
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]);
        while((count=read(fds[0],buff,60))>0){
            for(i=0;i<count;i++){
                write(1,buff+i,1);
                write(1," ",1);
            }
            printf("\n");
        }
        exit(0);
    }else{
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}

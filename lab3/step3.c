/*
Name: Yi Qian Goh
Date: Thursday, 25 April 2024
Title: Lab3 Step 3 - Modify the program in Step 2. so that the writer process passes the output of “ls” command to the
upstream end of the pipe instead of writing its arguments to it. You may use dup2(fds[1],1); for
redirection and execlp("ls", "ls", 0); to run the “ls” command.
Description: using piping and forking, this program outputs what "ls" would output on the command line as just text.
*/
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
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("ls", "ls",0);
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

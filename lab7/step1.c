/*
Name: Yi Qian Goh
Date: Thursday, 30 May 2024
Title: Lab7 Step 1: This program generates a text file called testInput10k.txt with 10000 lines of 10000 random numbers.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer [sizeof(int)];
    int i;
    int numRequests = 10000;
    int maxPageNumber = 20;
    fp = fopen("testInput10k.txt", "w");
    for (i=0; i<numRequests; i++){
        sprintf(buffer, "%d\n", rand()%maxPageNumber);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}
/*
Name: Yi Qian Goh
Date: Thursday, 30 May 2024
Title: Lab7 Step 3: This program simulates LRU (Least Recently Used) page replacement algorithm.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[10000]; // Cache that holds the input from test file
    int i, count;
    int totalFaults = 0; // keeps track of the total page faults
    int timesUsed[C_SIZE];
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    int indexes[C_SIZE]; //stores recently used indices
    int placeInArray = 0;
    int lru = 0; //least recently used page number
    while (fgets(pageCache, 10000, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        bool foundInCache = false;
        for (i=0; i<C_SIZE; i++){
            if (cache[i].pageno == page_num){
                foundInCache = true;
                count++;
                timesUsed[i] = count;
                break;
            }
        }   
        if (foundInCache == false){
            //You may print the page that caused the page fault
            printf("%d\n", page_num);
            int i;
            int min = timesUsed[0];
            int lru = 0;
            for(i = 1; i<C_SIZE; i++) {
                if(timesUsed[i] < min) {
                    min = timesUsed[i];
                    lru = i;
                }
            }
            cache[lru].pageno = page_num;
            count++;
            timesUsed[lru] = count;
            totalFaults++;
        }
    }

    printf("%d Total Page Faults", totalFaults++);
    return 0;



}

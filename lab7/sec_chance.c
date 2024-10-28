/*
Name: Yi Qian Goh
Date: Thursday, 30 May 2024
Title: Lab7 Step 3: This program simulates Second Chance page replacement algorithm.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {//to 
    int pageno;
    bool referenceBit;
} ref_page;


int main(int argc, char *argv[]) {
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[10000]; // Cache that holds the input from test file
    int i;
    int totalFaults = 0; // keeps track of the total page faults
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
        cache[i].pageno = -1;
        cache[i].referenceBit = false;
    }
    int placeInArray = 0;
    while (fgets(pageCache, sizeof(pageCache), stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        bool foundInCache = false;
        for (i=0; i<C_SIZE; i++){
            if (cache[i].pageno == page_num){
                foundInCache = true;
                cache[i].referenceBit = true;
                break; //break out loop because found page_num in cache  
            }
        }   

        if(foundInCache == false) {
            //You may print the page that caused the page fault
            printf("%d\n", page_num);
            while(cache[placeInArray].referenceBit) {
                cache[placeInArray].referenceBit = false;
                placeInArray = (placeInArray + 1) % C_SIZE;
            }
            cache[placeInArray].pageno = page_num;
            //cache[placeInArray].referenceBit = true;
            totalFaults++;
            placeInArray = (placeInArray + 1) % C_SIZE;
        }
    }
    printf("%d Total Page Faults", totalFaults);
    return 0;
}

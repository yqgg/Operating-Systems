/*
Name: Yi Qian Goh
Date: Thursday, 30 May 2024
Title: Lab7 Step 2: This program iteratively reads input from stdin when the command 'cat filename.txt' is used.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int

    	/*

		
		Page Replacement Implementation Goes Here 


    	*/
    }

    printf("%d Total Page Faults", totalFaults);
    return 0;



}

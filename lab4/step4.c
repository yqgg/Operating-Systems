/*
Name: Yi Qian Goh
Date: thursday, 25 April 2024
Title: Lab4 Step 4 - Write a program that implements matrix multiplication in a multi-threaded environment.
Description: This program computes the product matC of matA multiplied by matB. Matrix A and B are initialized 
                with random values from [0,10]. Then, each thread of the process will each compute the resulting 
                values in only one row of matC. This way, the matrix-matrix multiplication computation is parallelized
                among N threads (value of N is specified by command line input).
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

//global variables
int N, M, L;
double **matA, **matB, **matC;
void *multiplyRow(void *);

void printMat(int r, int c, double **mat) {
    int i, j;
    for(i = 0; i<r; i++) {
        for(j = 0; j< c; j++) {
            printf("%.0f ", mat[i][j]);
        }
        printf("\n");
    }
}

double** allocateMatMem(int r, int c, double **mat) {
    int i;
    mat = (double **)malloc(r * sizeof(double *)); //matA[r][c]
    if (mat == NULL) {
        printf("Memory allocation failed\n");
        exit(1); // Exit program on failure
    }
    for(i = 0; i<r; i++) {
        mat[i] = (double *)malloc(c * sizeof(double));
        if (mat[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1); // Exit program on failure
        }
    }
    return mat;
}

//allocate space and initialize matrix with random numbers
double** initializeMat(int r, int c, double **mat) {
    int i, j;
    mat = (double **)malloc(r * sizeof(double *)); //matA[r][c]
    if (mat == NULL) {
        printf("Memory allocation failed\n");
        exit(1); // Exit program on failure
    }
    for(i = 0; i<r; i++) {
        mat[i] = (double *)malloc(c * sizeof(double));
        if (mat[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1); // Exit program on failure
        }
    }
    for(i = 0; i<r; i++) {
        for(j = 0; j<c; j++) {
            mat[i][j] = rand() % 10;
        }
    }
    printMat(r, c, mat);
    printf("\n");
    return mat;
}

int main(int argc, char *argv[]) { 
    if(argc != 4) {
        printf ("Usage: %s <N> <M> <L>\n",argv[0]);
        exit(0);
    }

    //int N, M, L;
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    L = atoi(argv[3]);
    
    srand(time(NULL));

    printf("Matrix A:\n");
    matA = initializeMat(N, M, matA);

    printf("Matrix B:\n");\
    matB = initializeMat(M, L, matB);

    matC = allocateMatMem(N, L, matC);

    //create threads
    pthread_t threads[N];
    int thread_args[N];
    int i;
    for(i = 0; i<N; i++) { //ith row of matA
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, multiplyRow, &thread_args[i]);
    }

    //wait for threads to finish
    for(i = 0; i<N; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Matrix C:\n");
    printMat(N, L, matC);

    free(matA);
    free(matB);
    free(matC);
    
    return 0;
}

void *multiplyRow(void* arg) {
    int i = *(int *)arg;
    int j, k;
    for(j = 0; j<L; j++) {
        double temp = 0;
        for(k = 0; k<M; k++) {
            temp += matA[i][k] * matB[k][j]; 
        }
        matC[i][j] = temp;
    }
    pthread_exit(NULL);
}
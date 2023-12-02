// Gabriel Schrader Vilas Boas, RA: 150981
// João Pedro Assumpção Evaristo, RA: 147887
// Ramon da Silva Passos, RA: 148011

// mpicc -o main main.c 
// mpiexec -np 4 ./main

#include <stdio.h>
#include "mpi.h"
#include "common.h"
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include "../../trabalho-1/openMP/common.h"
#define GENERATIONS 50
#define DIMENSION 2048

// MPI_Send definition
// int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)

// MPI_Recv definition
// int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)

void sendGridToWorkers(float **readingGrid, int numProcesses) {
    int i, j;
    for (i = 1; i < numProcesses; i++) {
        for (j = 0; j < DIMENSION; j++) {
            MPI_Send(readingGrid[j], DIMENSION, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
        }
    }
}

void receiveGridFromMaster(float **readingGrid) {
    int i;
    for (i = 0; i < DIMENSION; i++) {
        MPI_Recv(readingGrid[i], DIMENSION, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

void workerProcess(int numProcesses) {
    float **readingGrid = (float **)malloc(DIMENSION * sizeof(float *));
    float **writingGrid = (float **)malloc(DIMENSION * sizeof(float *));

    for (int i = 0; i < DIMENSION; i++) {
        readingGrid[i] = (float *)malloc(DIMENSION * sizeof(float));
    }

    for (int i = 0; i < DIMENSION; i++) {
        writingGrid[i] = (float *)malloc(DIMENSION * sizeof(float));
    }

    receiveGridFromMaster(readingGrid);
    play(readingGrid, writingGrid);
    printf("Numero celulas vivas: %d\n", getAliveCells(readingGrid));
}

void masterProcess(int numProcesses) {
    float **readingGrid = (float **)malloc(DIMENSION * sizeof(float *));
    float **writingGrid = (float **)malloc(DIMENSION * sizeof(float *));

    for (int i = 0; i < DIMENSION; i++) {
        readingGrid[i] = (float *)malloc(DIMENSION * sizeof(float));
    }

    for (int i = 0; i < DIMENSION; i++) {
        writingGrid[i] = (float *)malloc(DIMENSION * sizeof(float));
    }

    fillZeros(readingGrid);
    initializeGrid(readingGrid);
    sendGridToWorkers(readingGrid, numProcesses);
}

int main(void) {
    int processId, numProcesses;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &processId);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    if(processId == 0) {
        masterProcess(numProcesses);
    } else {
        workerProcess(numProcesses);
    }

    MPI_Finalize();
    return 0;
}

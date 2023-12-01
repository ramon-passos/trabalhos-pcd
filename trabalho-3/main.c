// Gabriel Schrader Vilas Boas, RA: 150981
// João Pedro Assumpção Evaristo, RA: 147887
// Ramon da Silva Passos, RA: 148011

// mpicc -o main main.c 
// mpiexec -np 4 ./main


#include <stdio.h>
#include <mpi.h>
#include "common.h"
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include "../../trabalho-1/openMP/common.h"
#define GENERATIONS 50
#define DIMENSION 2048

//  Funcao que retorna o numero de celulas
//  vivas no tabuleiro.

int main(void)
{
    MPI_Init(NULL, NULL);
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // readingGrid refere-se ao tabuleiro da
    // geracao atual
    float **readingGrid = (float **)malloc(DIMENSION * sizeof(float *));
    for (int i = 0; i < DIMENSION; i++)
    {
        readingGrid[i] = (float *)malloc(DIMENSION * sizeof(float));
    }

    fillZeros(readingGrid);
    initializeGrid(readingGrid);

    // writingGrid refere-se ao tabuleiro da
    // geracao futura
    float **writingGrid = (float **)malloc(DIMENSION * sizeof(float *));
    for (int i = 0; i < DIMENSION; i++)
    {
        writingGrid[i] = (float *)malloc(DIMENSION * sizeof(float));
    }
    play(readingGrid, writingGrid);
    printf("Numero celulas vivas: %d\n", getAliveCells(readingGrid));
    return 0;
}
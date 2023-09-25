// Gabriel Schrader Vilas Boas, RA: 150981
// João Pedro Assumpção Evaristo, RA: 147887
// Ramon da Silva Passos, RA: 148011

#include "common.h"
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#define GENERATIONS 2000

//  Funcao que retorna o numero de celulas
//  vivas no tabuleiro.
int getAliveCells(float **grid)
{
    int sum = 0;
    int numThreads;
    int i, j;
#pragma omp parallel private(j) reduction(+ : sum)
#pragma omp for

    for (i = 0; i < DIMENSION; i++)
    {
        for (j = 0; j < DIMENSION; j++)
        {
            if (grid[i][j] > 0.0)
                sum = sum + 1;
        }
    }

    return sum;
}

void fillZeros(float **grid)
{
    int i, j;
#pragma omp parallel private(j)
#pragma omp for
    for (i = 0; i < DIMENSION; i++)
    {
        for (j = 0; j < DIMENSION; j++)
        {
            grid[i][j] = 0.0;
        }
    }
}

// Funcao que itera sobre as geracoes
// e altera os tabuleiros.
void play(float **readingGrid, float **writingGrid)
{
    int aux = 0;
    int i, j;
    double start, end;
    start = omp_get_wtime();
    while (aux < GENERATIONS)
    {
        printf("%d\n", aux);
#pragma omp parallel private(j)
#pragma omp for
        for (i = 0; i < DIMENSION; i++)
        { // paralelizar
            for (j = 0; j < DIMENSION; j++)
            {
                assignCellValue(readingGrid, writingGrid, i, j);
            }
        }
        swap(&readingGrid, &writingGrid);
        aux++;
    }
    end = omp_get_wtime();
    printf(" took %f seconds.\n", end - start);
}

int main(void)
{
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
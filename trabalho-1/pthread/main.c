// Gabriel Schrader Vilas Boas, RA: 150981
// João Pedro Assumpção Evaristo, RA: 147887
// Ramon da Silva Passos, RA: 148011

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "common.h"
#define GENERATIONS 2000
#define NUM_THREADS 4

float **readingGrid;
float **writingGrid;
int aliveCells = 0;
int aliveCellsMatrix[NUM_THREADS];

typedef struct arguments
{
    int ini;
    int end;
    int threadNumber;
} arguments;

void create_threads(pthread_t *threads, int n, int length, void *(*func)(void *))
{
    int i;
    int b = ceil(length / (double)n);
    for (i = 0; i < n; i++)
    {
        arguments *offset = (arguments *)malloc(sizeof(arguments));
        offset->ini = b * i;
        offset->end = b * (i + 1) < length ? b * (i + 1) : length;
        offset->threadNumber = i;
        pthread_create(&threads[i], NULL, func, offset);
    }
    return;
}

void join_threads(pthread_t *threads, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

void parallelizeOperation(void *(*func)(void *))
{
    pthread_t threads[NUM_THREADS];

    for (int t = 0; t < NUM_THREADS; t++)
    {
        create_threads(threads, NUM_THREADS, DIMENSION, func);
    }

    for (int t = 0; t < NUM_THREADS; t++)
    {
        join_threads(threads, NUM_THREADS);
    }
}

void *getAliveCellPerThread(void *args)
{
    arguments *offset = (arguments *)args;
    int ini = offset->ini;
    int end = offset->end;
    int threadNumber = offset->threadNumber;
    int sum = 0;

    for (int i = ini; i < end; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            if (readingGrid[i][j] > 0.0)
                sum = sum + 1;
        }
    }

    aliveCellsMatrix[threadNumber] = sum;
}

int getAliveCells() // parallelize
{
    int sum = 0;
    parallelizeOperation(getAliveCellPerThread);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        sum += aliveCellsMatrix[i];
    }

    return sum;
}

// Funcao para trocar os grids
void swap(float ***readingGrid, float ***writingGrid)
{
    float **temp = *readingGrid;
    *readingGrid = *writingGrid;
    *writingGrid = temp;
}

// Funcao que itera sobre as geracoes
// e altera os tabuleiros.

void *playPerThread(void *args)
{
    arguments *offset = (arguments *)args;
    int ini = offset->ini;
    int end = offset->end;

    for (int i = ini; i < end; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            assignCellValue(readingGrid, writingGrid, i, j);
        }
    }
}

void play()
{
    int aux = 0;
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    while (aux < GENERATIONS)
    {
        printf("%d\n", aux);
        printGrid(readingGrid);
        parallelizeOperation(playPerThread);
        printf("Numero celulas vivas: %d. Geração: %d\n", getAliveCells(), aux);
        swap(&readingGrid, &writingGrid);
        aux++;
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f\n", cpu_time_used);
}

void *fillZeroPerThread(void *args)
{
    arguments *offset = (arguments *)args;
    int ini = offset->ini;
    int end = offset->end;

    for (int i = ini; i < end; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            readingGrid[i][j] = 0.0;
        }
    }
}

void fillZeros()
{
    parallelizeOperation(fillZeroPerThread);
}

int main()
{
    readingGrid = (float **)malloc(DIMENSION * sizeof(float *));
    writingGrid = (float **)malloc(DIMENSION * sizeof(float *));

    for (int i = 0; i < DIMENSION; i++)
    {
        readingGrid[i] = (float *)malloc(DIMENSION * sizeof(float));
    }

    for (int i = 0; i < DIMENSION; i++)
    {
        writingGrid[i] = (float *)malloc(DIMENSION * sizeof(float));
    }

    fillZeros();
    initializeGrid(readingGrid);
    play();
    printf("Numero celulas vivas: %d\n", getAliveCells());
    return 0;
}

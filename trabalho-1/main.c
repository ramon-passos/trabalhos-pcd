// Gabriel Schrader Vilas Boas, RA: 150981
// João Pedro Assumpção Evaristo, RA:
// Ramon da Silva Passos, RA:

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#define GENERATIONS 10


// Funcao que retorna o numero de celulas
// vivas no tabuleiro.
int getAliveCells(float **grid) {
  int sum = 0;
  for (int i = 0; i < DIMENSION; i++) {
    for (int j = 0; j < DIMENSION; j++) {
      if (grid[i][j] > 0.0)
        sum++;
    }
  }
  return sum;
}

// Funcao que itera sobre as geracoes
// e altera os tabuleiros.
void play(float **readingGrid, float **writingGrid) {
  int aux = 0;
  while (aux < GENERATIONS) {
    printf("geracao %d\n", aux);
    printf("Numero celulas vivas: %d\n", getAliveCells(readingGrid));
    printGrid(readingGrid);
    for (int i = 0; i < DIMENSION; i++) {
      for (int j = 0; j < DIMENSION; j++) {
        assignCellValue(readingGrid, writingGrid, i, j);
      }
    }
    readingGrid = writingGrid;
    aux++;
  }
}

int main(void) {
  // readingGrid refere-se ao tabuleiro da
  // geracao atual
  float **readingGrid = (float **)malloc(DIMENSION * sizeof(float *));
  for (int i = 0; i < DIMENSION; i++) {
    readingGrid[i] = (float *)malloc(DIMENSION * sizeof(float));
  }

  initializeGrid(readingGrid);

  // writingGrid refere-se ao tabuleiro da
  // geracao futura
  float **writingGrid = (float **)malloc(DIMENSION * sizeof(float *));
  for (int i = 0; i < DIMENSION; i++) {
    writingGrid[i] = (float *)malloc(DIMENSION * sizeof(float));
  }
  play(readingGrid, writingGrid);
  Neighbors teste = getNeighbors(readingGrid, 0, 0);
  return 0;
}

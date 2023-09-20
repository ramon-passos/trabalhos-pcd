// Gabriel Schrader Vilas Boas, RA: 150981
// João Pedro
// Ramon

#include <stdio.h>
#include <stdlib.h>
#define DIMENSION 100
#define GENERATIONS 2000
#define LIGHTGREY 176
#define MEDIUMGREY 177
#define DARKGREY 178

void initializeGrid(float **grid) {
  for (int i = 0; i < DIMENSION; i++) {
    for (int j = 0; j < DIMENSION; j++) {
      grid[i][j] = 0.0;
    }
  }
  int lin = 1, col = 1;
  grid[lin][col + 1] = 1.0;
  grid[lin + 1][col + 2] = 1.0;
  grid[lin + 2][col] = 1.0;
  grid[lin + 2][col + 1] = 1.0;
  grid[lin + 2][col + 2] = 1.0;
  lin = 10;
  col = 30;
  grid[lin][col + 1] = 1.0;
  grid[lin][col + 2] = 1.0;
  grid[lin + 1][col] = 1.0;
  grid[lin + 1][col + 1] = 1.0;
  grid[lin + 2][col + 1] = 1.0;
}

void printGrid(float **grid) {
  for (int i = 0; i < DIMENSION; i++) {
    for (int j = 0; j < DIMENSION; j++) {
      if (grid[i][j] == 1.0)
        printf("#");
      else
        printf("_");
    }
    printf("\n");
  }
}

int aliveCells(float **grid) {
  int sum = 0;
  for (int i = 0; i < DIMENSION; i++) {
    for (int j = 0; j < DIMENSION; j++) {
      if (grid[i][j] > 0)
        sum++;
    }
  }
  return sum;
}

int main(void) {
  float **grid = (float **)malloc(DIMENSION * sizeof(float *));
  for (int i = 0; i < DIMENSION; i++) {
    grid[i] = (float *)malloc(DIMENSION * sizeof(float));
  }
  initializeGrid(grid);
  printGrid(grid);
  printf("Hello World\n");
  return 0;
}
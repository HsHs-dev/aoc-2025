#include <stdlib.h>
#include <stdio.h>
#include "main.h"

#define MAX 100

int main(void) {

  char* filename = "input1.txt";

  // read the file line by line
  FILE* fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("Failed to open %s\n", filename);
    exit(EXIT_FAILURE);
  }

  int dial_zero = 0;
  int dial = 50;
  char rotation;
  int dist;
  while (fscanf(fp, " %c%d", &rotation, &dist) == 2) {
    // printf("rotation = %c and dist = %d\n", rotation, dist);

    if (rotation == 'L') {
      dial = floor_mod((dial - dist), MAX);
    } else {
      dial = floor_mod((dial + dist), MAX);
    }

    if (dial == 0) {
      dial_zero++;
    }

  }

  printf("%d\n", dial_zero);

  
  fclose(fp);

  return 0;
}

// floor mod function doesn't allow the input to go beyond b (100 in this case)
// or below 0. giving us the circular functionality we want
int floor_mod(int a, int b) { return ((a % b) + b) % b; }
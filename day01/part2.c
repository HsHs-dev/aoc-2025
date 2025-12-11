#include <stdlib.h>
#include <stdio.h>
#include "main.h"

#define MAX 100

int main(void) {

  char* filename = "input2.txt";

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
      dial_zero += dec(&dial, dist);
    } else {
      dial_zero += inc(&dial, dist);
    }

  }

  printf("%d\n", dial_zero);
  
  fclose(fp);

  return 0;
}

int inc(int* dial, int dist) {
  int zero_times = 0;
  for (int i = 0; i < dist; i++) {
    if ((*dial) == 0) {
      zero_times++;
    }
    *dial = *dial + 1;
    // floor mod
    *dial = ((*dial % MAX) + MAX) % MAX;
  }

  return zero_times;
}

int dec(int* dial, int dist) {
  int zero_times = 0;
  for (int i = 0; i < dist; i++) {
    if ((*dial) == 0) {
      zero_times++;
    }
    *dial = *dial - 1;
    // floor mod
    *dial = ((*dial % MAX) + MAX) % MAX;
  }

  return zero_times;
}

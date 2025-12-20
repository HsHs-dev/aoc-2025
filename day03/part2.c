#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include "main.h"

#define BANK_BATTERIES 12

int main(void) {

  FILE* fp = fopen("input.txt", "r");

  if (fp == NULL) {
    printf("Failed to open the file");
    exit(EXIT_FAILURE);
  }

  uint64_t sum = 0;

  char* line = NULL;
  size_t len = 0;
  while(getline(&line, &len, fp) != -1) {
    sum += find_largest(line);
  }

  free(line);

  printf("%" PRIu64 "\n", sum);

  return 0;
}


uint64_t find_largest(char* line) {

  printf("line is %s", line);

  int len = strlen(line);
  // remove new-line char if present
  if (len > 0 && line[len - 1] == '\n') {
    len--;
  }

  // number of substitutes left before we run out of digits
  int substitutes = len - BANK_BATTERIES;

  int max = 0, batteries = BANK_BATTERIES;
  bool subDown = false;
  uint64_t best = 0;
  for (int i = 0; i < len; i++) {

    int left = len - i;

    int current = line[i] - '0';


    if (current > (best % 10) && substitutes > 0 && best > 0 && batteries != 1) {
      best /= 10;
      best = concatenate(best, current);
      substitutes--;
      subDown = true;
    } else {
      if (batteries == 1 && i != len - 1) continue;
      best = concatenate(best, current);
      batteries--;
    }
    
    if (current > max && substitutes > 0 && max > 0 && left >= BANK_BATTERIES) {
      best = current;
      max = current;
      if (subDown) {
        subDown = false;
      } else {
        substitutes--;
      }
    }

    if (current > max) {
      max = current;
    }

  }

  printf("best is %" PRIu64 "\n\n", best);

  return best;

}

// code from https://stackoverflow.com/questions/12700497/how-to-concatenate-two-integers-in-c
uint64_t concatenate(uint64_t x, uint64_t y) {
  uint64_t pow = 10;
  while (y >= pow)
    pow *= 10;
  return x * pow + y;
}


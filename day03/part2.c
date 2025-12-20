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

  int len = strlen(line);
  if (len > 0 && line[len - 1] == '\n') {
    len--;
  }

  int substitutes = len - BANK_BATTERIES;

  uint64_t best = 0;
  int best_digits = 0;
  int max = -1;

  for (int i = 0; i < len; i++) {

    int current = line[i] - '0';
    int left = len - i - 1;

    while (best_digits > 0 && substitutes > 0 && current > (best % 10) && best_digits + left >= BANK_BATTERIES) {

      best /= 10;
      best_digits--;
      substitutes--;
    }

    if (best_digits < BANK_BATTERIES) {
      best = concatenate(best, current);
      best_digits++;
    } else {
      substitutes--;
    }

    if (current > max) {
      max = current;
    }
  }

  return best;
}

// code from https://stackoverflow.com/questions/12700497/how-to-concatenate-two-integers-in-c
uint64_t concatenate(uint64_t x, uint64_t y) {
  uint64_t pow = 10;
  while (y >= pow)
    pow *= 10;
  return x * pow + y;
}


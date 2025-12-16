#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(void) {

  FILE* fp = fopen("input1.txt", "r");

  if (fp == NULL) {
    printf("Failed to open the file");
    exit(EXIT_FAILURE);
  }

  int sum = 0;

  char* line = NULL;
  size_t len = 0;
  while(getline(&line, &len, fp) != -1) {
    sum += find_two_largest(line);
  }

  free(line);

  printf("%d\n", sum);

  return 0;
}

int find_two_largest(char* line) {

  int big1 = 0;
  int big1index = 0;

  int big2 = 0;

  int len = strlen(line);

  for (int i = 0; i < len - 2; i++) {
    int current = line[i] - '0';
    if (current > big1) {
      big1 = current;
      big1index = i;
    }
  }

  for (int i = 0; i < len; i++) {
    int current = line[i] - '0';
    if (current > big2 && i > big1index) {
      big2 = current;
    }
  }

  return concatenate(big1, big2);
}


// code from https://stackoverflow.com/questions/12700497/how-to-concatenate-two-integers-in-c
unsigned concatenate(unsigned x, unsigned y) {
  unsigned pow = 10;
  while (y >= pow)
    pow *= 10;
  return x * pow + y;
}


// linear solution of the problem. CC: ChatGPT
// int find_two_largest_linear(char *line) {
//     int max_so_far = -1;   // best digit seen so far (for tens place)
//     int best = 0;          // best 2-digit number found

//     for (int i = 0; line[i] != '\0'; i++) {
//         if (line[i] < '0' || line[i] > '9')
//             continue;  // skip newline or any non-digit

//         int d = line[i] - '0';

//         if (max_so_far != -1) {
//             int candidate = max_so_far * 10 + d;
//             if (candidate > best)
//                 best = candidate;
//         }

//         if (d > max_so_far)
//             max_so_far = d;
//     }

//     return best;
// }
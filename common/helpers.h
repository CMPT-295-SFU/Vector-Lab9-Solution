#ifndef HELPER_H
#define HELPER_H

#include "intrin.h"
#include <stdio.h>


bool verifyint(int *x, int *y, int *output, int *gold, int N) {
  int incorrect = -1;
  for (int i = 0; i < N + VLEN; i++) {
    if (output[i] != gold[i]) {
      incorrect = i;
      break;
    }
  }

  if (incorrect != -1) {
    if (incorrect >= N) {
      printf("You have written to out of bound value!\n");
    }
    printf("Wrong calculation at value[%d]!\n", incorrect);
    printf("values x,y  = ");
    for (int i = 0; i < N; i++) {
      printf("[X=%d Y=%d]", x[i],y[i]);
    }
    printf("\n");
    printf("output = ");
    for (int i = 0; i < N; i++) {
      printf("% d ", output[i]);
    }
    printf("\n");

    printf("gold   = ");
    for (int i = 0; i < N; i++) {
      printf("% d ", gold[i]);
    }
    printf("\n");
    return false;
  }
  printf("Results matched with answer!\n");
  return true;
}

#endif
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include "Dot.h"
#include "dataset.h"
#include "helpers.h"
#include "intrin.h"
#include "logger.h"

using namespace std;

#define EXP_MAX 1024

Logger SFU431Logger;

void usage(const char *progname);
void initValue(int *values, int *exponents, int *output, int *gold,
               unsigned int N);
bool verifyResult(int *values, int *exponents, int *output, int *gold, int N);

int main(int argc, char *argv[]) {
  bool printLog = false;

  // parse commandline options ////////////////////////////////////////////
  int opt;
  static struct option long_options[] = {
      {"log", 0, 0, 'l'}, {"help", 0, 0, '?'}, {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "s:l?", long_options, NULL)) != EOF) {
    switch (opt) {
      case 'l':
        printLog = true;
        break;
      case '?':
      default:
        usage(argv[0]);
        return 1;
    }
  }

  printf("\n\e[1;31mDot Product Result[] = X[] * Y[] \e[0m  \n");
    int *output_serial = new int[SIZE + VECTOR_WIDTH];
    int *output_vector = new int[SIZE + VECTOR_WIDTH];


  // Adding padding to verify against gold_data
    for (int i = SIZE; i < SIZE + VECTOR_WIDTH; i++) {
      output_serial[i] = 0xbeef;
      output_vector[i] = 0xbeef;
    }

    DotSerial(input_X, input_Y, output_serial, SIZE);

    printf("\e[1;31mDot Serial \e[0m  \n");
    bool result_serial = verifyint(input_X, input_Y, output_serial, gold_data, SIZE);

    if (!result_serial) {
      printf("@@@ Failed!!!\n");
      return 1;
    } else {
      printf("Passed!!!\n");
    }

    printf("\e[1;31mDot Vector \e[0m  \n");
    DotVector(input_X, input_Y, output_vector, SIZE);

    bool result_vector = verifyint(input_X, input_Y, output_vector, gold_data, SIZE);

    if (printLog) {
      SFU431Logger.printLog();
      SFU431Logger.printStats();
    }
    if (!result_vector) {
      printf("@@@ Failed!!!\n");
      return 1;
    } else {
      printf("Passed!!!\n");
      return 0;
    }
}

void usage(const char *progname) {
  printf("Usage: %s [options]\n", progname);
  printf("Program Options:\n");
  printf("  -l  --log          Print vector unit execution log\n");
  printf("  -?  --help         This message\n");
}

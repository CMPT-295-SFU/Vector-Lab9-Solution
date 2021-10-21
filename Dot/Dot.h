#include <math.h>
#include <stdio.h>
#include <algorithm>
#include "intrin.h"
#include "logger.h"
using namespace std;

void DotSerial(int x[], int y[], int output[], int N) {
  for (int i = 0; i < N; i++) {
    output[i] = x[i] * y[i];
  }
}

// implementation of relu using instrinsics
void DotVector(int x[], int y[], int output[], int N) {

  // Create vector registers for processing
  __cs295_vec_int x_v, y_v;
  __cs295_vec_int result_v;

  // Check the loop bound; it increments in VLEN segments
  // It considers the array a VLEN elements at a time.
  for (int i = 0; i < N; i += VLEN) {
  
    // Activate VLEN lanes
    __cs295_mask maskAll = _cs295_init_ones(VLEN);

    // Both X and Y pointers move VLEN at a time. 

    // Load VLEN elements from X; values from contiguous memory
    // addresses
    _cs295_vload_int(x_v, x + i, maskAll);  // x = values[i];

    // Load VLEN elements from Y; values from contiguous memory
    // addresses.    
    _cs295_vload_int(y_v, y + i, maskAll);  // x = values[i];

    // Activate maskAll lanes.
    _cs295_vmult_int(result_v, x_v, y_v, maskAll);

    // Write results back to memory
    _cs295_vstore_int(output + i, result_v, maskAll);

    printf("Iteration %d processing %d to %d \n", i, i, i+VLEN);
    cs295Logger.printLog();
    cs295Logger.clearLog();
  }
  printf("Done Vector");
}
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
  __sfu431_vec_int x_v, y_v;
  __sfu431_vec_int result_v;

  // Check the loop bound; it increments in VECTOR_WIDTH segments
  // It considers the array a VECTOR_WIDTH elements at a time.
  for (int i = 0; i < N; i += VECTOR_WIDTH) {
  
    // Activate VECTOR_WIDTH lanes
    __sfu431_mask maskAll = _sfu431_init_ones(VECTOR_WIDTH);

    // Both X and Y pointers move VECTOR_WIDTH at a time. 

    // Load VECTOR_WIDTH elements from X; values from contiguous memory
    // addresses
    _sfu431_vload_int(x_v, x + i, maskAll);  // x = values[i];

    // Load VECTOR_WIDTH elements from Y; values from contiguous memory
    // addresses.    
    _sfu431_vload_int(y_v, y + i, maskAll);  // x = values[i];

    // Activate maskAll lanes.
    _sfu431_vmult_int(result_v, x_v, y_v, maskAll);

    // Write results back to memory
    _sfu431_vstore_int(output + i, result_v, maskAll);

    printf("Iteration %d processing %d to %d \n", i, i, i+VECTOR_WIDTH);
    SFU431Logger.printLog();
    SFU431Logger.clearLog();
  }
  printf("Done Vector");
}
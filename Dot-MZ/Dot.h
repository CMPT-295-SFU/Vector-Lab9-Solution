#include <math.h>
#include <stdio.h>
#include <algorithm>
#include "intrin.h"
#include "logger.h"
using namespace std;

void DotSerial(int x[], int y[], int output[], int N) {
  for (int i = 0; i < N; i++) {
    if (x[i] != 0 && y[i] != 0) {
    output[i] = x[i] * y[i];
    }
  }
}

// implementation of relu using instrinsics
void DotVector(int x[], int y[], int output[], int N) {

  // Create vector registers for processing
  __sfu431_vec_int x_v, y_v;
  __sfu431_vec_int result_v;

  __sfu431_vec_int zeros = _sfu431_vset_int(0);

  for (int i = 0; i < N; i += VECTOR_WIDTH) {
   
    // Disable non zeros.
    // Find out lanes for which either X or Y are 0.

    // Load VECTOR_WIDTH elements from X; values from contiguous memory
    // Is x[i] == 0 ?

    __sfu431_mask maskAll = _sfu431_init_ones(VECTOR_WIDTH);

    _sfu431_vload_int(x_v, x + i, maskAll);  // x = values[i];
    __sfu431_mask mask_x_zeros;
    _sfu431_veq_int(mask_x_zeros, x_v, zeros, maskAll);

    // Load VECTOR_WIDTH elements from Y; values from contiguous memory
    // Is y[i] == 0 ?

    _sfu431_vload_int(y_v, y + i, maskAll);  // x = values[i];
    __sfu431_mask mask_y_zeros;
    _sfu431_veq_int(mask_y_zeros,y_v, zeros,
                    maskAll);  // x = values[i];

    // Zero lanes
    __sfu431_mask mask_x_or_y_zeros = _sfu431_mask_or(mask_x_zeros, mask_y_zeros);

    // Activate non-zero lanes
    __sfu431_mask mask_nz = _sfu431_mask_not(mask_x_or_y_zeros);

    // Multiply non-zero values
    _sfu431_vmult_int(result_v, x_v, y_v, mask_nz);

    // Write results back to memory
    _sfu431_vstore_int(output + i, result_v, mask_nz);

    printf("Iteration %d \n", i);
    SFU431Logger.printLog();
    SFU431Logger.clearLog();
  }
  printf("Done Vector");
}
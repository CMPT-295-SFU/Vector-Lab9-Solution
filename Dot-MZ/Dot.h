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
  __cs295_vec_int x_v, y_v;
  __cs295_vec_int result_v;

  __cs295_vec_int zeros = _cs295_vset_int(0);

  for (int i = 0; i < N; i += VLEN) {
   
    // Disable non zeros.
    // Find out lanes for which either X or Y are 0.

    // Load VLEN elements from X; values from contiguous memory
    // Is x[i] == 0 ?

    __cs295_mask maskAll = _cs295_init_ones(VLEN);

    _cs295_vload_int(x_v, x + i, maskAll);  // x = values[i];
    __cs295_mask mask_x_zeros;
    _cs295_veq_int(mask_x_zeros, x_v, zeros, maskAll);

    // Load VLEN elements from Y; values from contiguous memory
    // Is y[i] == 0 ?

    _cs295_vload_int(y_v, y + i, maskAll);  // x = values[i];
    __cs295_mask mask_y_zeros;
    _cs295_veq_int(mask_y_zeros,y_v, zeros,
                    maskAll);  // x = values[i];

    // Zero lanes
    __cs295_mask mask_x_or_y_zeros = _cs295_mask_or(mask_x_zeros, mask_y_zeros);

    // Activate non-zero lanes
    __cs295_mask mask_nz = _cs295_mask_not(mask_x_or_y_zeros);

    // Multiply non-zero values
    _cs295_vmult_int(result_v, x_v, y_v, mask_nz);

    // Write results back to memory
    _cs295_vstore_int(output + i, result_v, mask_nz);

    printf("Iteration %d \n", i);
    cs295Logger.printLog();
    cs295Logger.clearLog();
  }
  printf("Done Vector");
}
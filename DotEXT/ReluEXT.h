#include "intrin.h"
#include "logger.h"
#include <algorithm>
#include <math.h>
#include <stdio.h>
using namespace std;

void ReluSerial(int *values, int *output, int N)
{
  for (int i = 0; i < N; i++)
  {
    int x = values[i];
    if (x < 0)
    {
      output[i] = 0;
    }
    else
    {
      output[i] = x;
    }
  }
}

// implementation of relu using instrinsics
void ReluVector(int *values, int *output, int N)
{
  __sfu431_vec_int x;
  __sfu431_vec_int result;
  __sfu431_vec_int zero = _sfu431_vset_int(0);
  __sfu431_mask maskAll, maskIsNegative, maskIsNotNegative;


  //  Note: Take a careful look at this loop indexing.  This example
  //  code is not guaranteed to work when (N % VECTOR_WIDTH) != 0.
  //  Why is that the case?
  for (int i = 0; i < N; i += VECTOR_WIDTH)
  {

    int width = VECTOR_WIDTH;
    if (N - i < VECTOR_WIDTH)
    {
      width = N - i;
    }

    // All ones
    maskAll = _sfu431_init_ones(width);

    // All zeros
    maskIsNegative = _sfu431_init_ones(0);

    // Load vector of values from contiguous memory addresses
    _sfu431_vload_int(x, values + i, maskAll); // x = values[i];

    // Set mask according to predicate
    _sfu431_vlt_int(maskIsNegative, x, zero, maskAll); // if (x < 0) {

    // Execute instruction using mask ("if" clause)
    _sfu431_vsub_int(result, x, x, maskIsNegative); //   output[i] = -x;

    // Inverse maskIsNegative to generate "else" mask
    maskIsNotNegative = _sfu431_mask_not(maskIsNegative); // } else {

    // Execute instruction ("else" clause)
    _sfu431_vload_int(result, values + i,
                        maskIsNotNegative); //   output[i] = x; }

    // Write results back to memory
    _sfu431_vstore_int(output + i, result, maskAll);
  }
}
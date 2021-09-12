// Define vector unit width here
#define VECTOR_WIDTH 8

#ifndef SFU431INTRIN_H_
#define SFU431INTRIN_H_

#include <cstdlib>
#include <cmath>
#include "logger.h"

//*******************
//* Type Definition *
//*******************

extern Logger SFU431Logger;

template <typename T>
struct __sfu431_vec {
  T value[VECTOR_WIDTH];
};

// Declare a mask with __sfu431_mask
struct __sfu431_mask : __sfu431_vec<bool> {};

// Declare a floating point vector register with __sfu431_vec_float
#define __sfu431_vec_float __sfu431_vec<float>

// Declare an integer vector register with __sfu431_vec_int
#define __sfu431_vec_int   __sfu431_vec<int>

//***********************
//* Function Definition *
//***********************

// Return a mask initialized to 1 in the first N lanes and 0 in the others
__sfu431_mask _sfu431_init_ones(int first = VECTOR_WIDTH);

// Return the inverse of maska
__sfu431_mask _sfu431_mask_not(__sfu431_mask &maska);

// Return (maska | maskb)
__sfu431_mask _sfu431_mask_or(__sfu431_mask &maska, __sfu431_mask &maskb);

// Return (maska & maskb)
__sfu431_mask _sfu431_mask_and(__sfu431_mask &maska, __sfu431_mask &maskb);

// Count the number of 1s in maska
int _sfu431_cntbits(__sfu431_mask &maska);

// Set register to value if vector lane is active
//  otherwise keep the old value
void _sfu431_vset_float(__sfu431_vec_float &vecResult, float value, __sfu431_mask &mask);
void _sfu431_vset_int(__sfu431_vec_int &vecResult, int value, __sfu431_mask &mask);
// For user's convenience, returns a vector register with all lanes initialized to value
__sfu431_vec_float _sfu431_vset_float(float value);
__sfu431_vec_int _sfu431_vset_int(int value);

// Copy values from vector register src to vector register dest if vector lane active
// otherwise keep the old value
void _sfu431_vmove_float(__sfu431_vec_float &dest, __sfu431_vec_float &src, __sfu431_mask &mask);
void _sfu431_vmove_int(__sfu431_vec_int &dest, __sfu431_vec_int &src, __sfu431_mask &mask);

// Load values from array src to vector register dest if vector lane active
//  otherwise keep the old value
void _sfu431_vload_float(__sfu431_vec_float &dest, float* src, __sfu431_mask &mask);
void _sfu431_vload_int(__sfu431_vec_int &dest, int* src, __sfu431_mask &mask);

// Store values from vector register src to array dest if vector lane active
//  otherwise keep the old value
void _sfu431_vstore_float(float* dest, __sfu431_vec_float &src, __sfu431_mask &mask);
void _sfu431_vstore_int(int* dest, __sfu431_vec_int &src, __sfu431_mask &mask);

// Segmented loads
void _sfu431_vload_seg_float(__sfu431_vec_float dest[], float *src,
                           __sfu431_mask &mask, const int fields);

void _sfu431_vload_seg_int(__sfu431_vec_int dest[], int *src, __sfu431_mask &mask, const int fields);

// Return calculation of (veca + vecb) if vector lane active
//  otherwise keep the old value
void _sfu431_vadd_float(__sfu431_vec_float &vecResult, __sfu431_vec_float &veca, __sfu431_vec_float &vecb, __sfu431_mask &mask);
void _sfu431_vadd_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca, __sfu431_vec_int &vecb, __sfu431_mask &mask);

// Return calculation of (veca - vecb) if vector lane active
//  otherwise keep the old value
void _sfu431_vsub_float(__sfu431_vec_float &vecResult, __sfu431_vec_float &veca, __sfu431_vec_float &vecb, __sfu431_mask &mask);
void _sfu431_vsub_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca, __sfu431_vec_int &vecb, __sfu431_mask &mask);

// Return calculation of (veca * vecb) if vector lane active
//  otherwise keep the old value
void _sfu431_vmult_float(__sfu431_vec_float &vecResult, __sfu431_vec_float &veca, __sfu431_vec_float &vecb, __sfu431_mask &mask);
void _sfu431_vmult_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca, __sfu431_vec_int &vecb, __sfu431_mask &mask);

// Return calculation of (veca / vecb) if vector lane active
//  otherwise keep the old value
void _sfu431_vdiv_float(__sfu431_vec_float &vecResult, __sfu431_vec_float &veca, __sfu431_vec_float &vecb, __sfu431_mask &mask);
void _sfu431_vdiv_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca, __sfu431_vec_int &vecb, __sfu431_mask &mask);

// Return calculation of (veca >> vecb) if vector lane active
//  otherwise keep the old value
void _sfu431_vshiftright_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca, __sfu431_vec_int &vecb, __sfu431_mask &mask);

// Return calculation of (veca & vecb) if vector lane active
//  otherwise keep the old value
void _sfu431_vbitand_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca, __sfu431_vec_int &vecb, __sfu431_mask &mask);

// Return calculation of absolute value abs(veca) if vector lane active
//  otherwise keep the old value
void _sfu431_vabs_float(__sfu431_vec_float &vecResult, __sfu431_vec_float &veca, __sfu431_mask &mask);
void _sfu431_vabs_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca, __sfu431_mask &mask);

// Return a mask of (veca > vecb) if vector lane active
//  otherwise keep the old value
void _sfu431_vgt_float(__sfu431_mask &vecResult, __sfu431_vec_float &veca, __sfu431_vec_float &vecb, __sfu431_mask &mask);
void _sfu431_vgt_int(__sfu431_mask &vecResult, __sfu431_vec_int &veca, __sfu431_vec_int &vecb, __sfu431_mask &mask);

// Return a mask of (veca < vecb) if vector lane active
//  otherwise keep the old value
void _sfu431_vlt_float(__sfu431_mask &vecResult, __sfu431_vec_float &veca, __sfu431_vec_float &vecb, __sfu431_mask &mask);
void _sfu431_vlt_int(__sfu431_mask &vecResult, __sfu431_vec_int &veca, __sfu431_vec_int &vecb, __sfu431_mask &mask);

// Return a mask of (veca == vecb) if vector lane active
//  otherwise keep the old value
void _sfu431_veq_float(__sfu431_mask &vecResult, __sfu431_vec_float &veca, __sfu431_vec_float &vecb, __sfu431_mask &mask);
void _sfu431_veq_int(__sfu431_mask &vecResult, __sfu431_vec_int &veca, __sfu431_vec_int &vecb, __sfu431_mask &mask);

// Adds up adjacent pairs of elements, so
//  [0 1 2 3] -> [0+1 0+1 2+3 2+3]
void _sfu431_hadd_float(__sfu431_vec_float &vecResult, __sfu431_vec_float &vec);
void _sfu431_hadd_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &vec);

// Performs an even-odd interleaving where all even-indexed elements move to front half
//  of the array and odd-indexed to the back half, so
//  [0 1 2 3 4 5 6 7] -> [0 2 4 6 1 3 5 7]
void _sfu431_interleave_float(__sfu431_vec_float &vecResult, __sfu431_vec_float &vec);
void _sfu431_interleave_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &vec);
// Add a customized log to help debugging
void addUserLog(const char * logStr);

#endif

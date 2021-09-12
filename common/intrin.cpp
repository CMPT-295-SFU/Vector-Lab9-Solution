#include "intrin.h"
#include "logger.h"

//******************
//* Implementation *
//******************

__sfu431_mask _sfu431_init_ones(int first) {
  __sfu431_mask mask;
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    mask.value[i] = (i < first) ? true : false;
  }
  return mask;
}

__sfu431_mask _sfu431_mask_not(__sfu431_mask &maska) {
  __sfu431_mask resultMask;
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    resultMask.value[i] = !maska.value[i];
  }
  SFU431Logger.addLog("masknot", _sfu431_init_ones(), VECTOR_WIDTH);
  return resultMask;
}

__sfu431_mask _sfu431_mask_or(__sfu431_mask &maska, __sfu431_mask &maskb) {
  __sfu431_mask resultMask;
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    resultMask.value[i] = maska.value[i] | maskb.value[i];
  }
  SFU431Logger.addLog("maskor", _sfu431_init_ones(), VECTOR_WIDTH);
  return resultMask;
}

__sfu431_mask _sfu431_mask_and(__sfu431_mask &maska, __sfu431_mask &maskb) {
  __sfu431_mask resultMask;
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    resultMask.value[i] = maska.value[i] && maskb.value[i];
  }
  SFU431Logger.addLog("maskand", _sfu431_init_ones(), VECTOR_WIDTH);
  return resultMask;
}

int _sfu431_cntbits(__sfu431_mask &maska) {
  int count = 0;
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    if (maska.value[i])
      count++;
  }
  SFU431Logger.addLog("cntbits", _sfu431_init_ones(), VECTOR_WIDTH);
  return count;
}

template <typename T>
void _sfu431_vset(__sfu431_vec<T> &vecResult, T value, __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? value : vecResult.value[i];
  }
  SFU431Logger.addLog("vset", mask, VECTOR_WIDTH);
}

template void _sfu431_vset<float>(__sfu431_vec_float &vecResult, float value,
                                  __sfu431_mask &mask);
template void _sfu431_vset<int>(__sfu431_vec_int &vecResult, int value,
                                __sfu431_mask &mask);

void _sfu431_vset_float(__sfu431_vec_float &vecResult, float value,
                        __sfu431_mask &mask) {
  _sfu431_vset<float>(vecResult, value, mask);
}
void _sfu431_vset_int(__sfu431_vec_int &vecResult, int value,
                      __sfu431_mask &mask) {
  _sfu431_vset<int>(vecResult, value, mask);
}

__sfu431_vec_float _sfu431_vset_float(float value) {
  __sfu431_vec_float vecResult;
  __sfu431_mask mask = _sfu431_init_ones();
  _sfu431_vset_float(vecResult, value, mask);
  return vecResult;
}
__sfu431_vec_int _sfu431_vset_int(int value) {
  __sfu431_vec_int vecResult;
  __sfu431_mask mask = _sfu431_init_ones();
  _sfu431_vset_int(vecResult, value, mask);
  return vecResult;
}

template <typename T>
void _sfu431_vmove(__sfu431_vec<T> &dest, __sfu431_vec<T> &src,
                   __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    dest.value[i] = mask.value[i] ? src.value[i] : dest.value[i];
  }
  SFU431Logger.addLog("vmove", mask, VECTOR_WIDTH);
}

template void _sfu431_vmove<float>(__sfu431_vec_float &dest,
                                   __sfu431_vec_float &src,
                                   __sfu431_mask &mask);
template void _sfu431_vmove<int>(__sfu431_vec_int &dest, __sfu431_vec_int &src,
                                 __sfu431_mask &mask);

void _sfu431_vmove_float(__sfu431_vec_float &dest, __sfu431_vec_float &src,
                         __sfu431_mask &mask) {
  _sfu431_vmove<float>(dest, src, mask);
}
void _sfu431_vmove_int(__sfu431_vec_int &dest, __sfu431_vec_int &src,
                       __sfu431_mask &mask) {
  _sfu431_vmove<int>(dest, src, mask);
}

template <typename T>
void _sfu431_vload(__sfu431_vec<T> &dest, T *src, __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    dest.value[i] = mask.value[i] ? src[i] : dest.value[i];
  }
  SFU431Logger.addLog("vload", mask, VECTOR_WIDTH);
}

template void _sfu431_vload<float>(__sfu431_vec_float &dest, float *src,
                                   __sfu431_mask &mask);
template void _sfu431_vload<int>(__sfu431_vec_int &dest, int *src,
                                 __sfu431_mask &mask);

void _sfu431_vload_float(__sfu431_vec_float &dest, float *src,
                         __sfu431_mask &mask) {
  _sfu431_vload<float>(dest, src, mask);
}
void _sfu431_vload_int(__sfu431_vec_int &dest, int *src, __sfu431_mask &mask) {
  _sfu431_vload<int>(dest, src, mask);
}

template <typename T>
void _sfu431_vload_seg(__sfu431_vec<T> dest[], T *src, __sfu431_mask &mask,
                       const int fields) {
  for (int i = 0; i < fields; i++) {
    for (int j = 0; j < VECTOR_WIDTH; j++) {
      dest[i].value[j] =
          mask.value[j] ? src[(i * fields) + j] : dest[i].value[j];
    }
    SFU431Logger.addLog("vlseg", mask, VECTOR_WIDTH);
  }
}

void _sfu431_vload_seg_float(__sfu431_vec_float dest[], float *src,
                             __sfu431_mask &mask, const int fields) {
  _sfu431_vload_seg<float>(dest, src, mask, fields);
}

void _sfu431_vload_seg_int(__sfu431_vec_int dest[], int *src,
                           __sfu431_mask &mask, const int fields) {
  _sfu431_vload_seg<int>(dest, src, mask, fields);
}

template <typename T>
void _sfu431_vstore(T *dest, __sfu431_vec<T> &src, __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    dest[i] = mask.value[i] ? src.value[i] : dest[i];
  }
  SFU431Logger.addLog("vstore", mask, VECTOR_WIDTH);
}

template void _sfu431_vstore<float>(float *dest, __sfu431_vec_float &src,
                                    __sfu431_mask &mask);
template void _sfu431_vstore<int>(int *dest, __sfu431_vec_int &src,
                                  __sfu431_mask &mask);

void _sfu431_vstore_float(float *dest, __sfu431_vec_float &src,
                          __sfu431_mask &mask) {
  _sfu431_vstore<float>(dest, src, mask);
}
void _sfu431_vstore_int(int *dest, __sfu431_vec_int &src, __sfu431_mask &mask) {
  _sfu431_vstore<int>(dest, src, mask);
}

template <typename T>
void _sfu431_vadd(__sfu431_vec<T> &vecResult, __sfu431_vec<T> &veca,
                  __sfu431_vec<T> &vecb, __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    vecResult.value[i] =
        mask.value[i] ? (veca.value[i] + vecb.value[i]) : vecResult.value[i];
  }
  SFU431Logger.addLog("vadd", mask, VECTOR_WIDTH);
}

template void _sfu431_vadd<float>(__sfu431_vec_float &vecResult,
                                  __sfu431_vec_float &veca,
                                  __sfu431_vec_float &vecb,
                                  __sfu431_mask &mask);
template void _sfu431_vadd<int>(__sfu431_vec_int &vecResult,
                                __sfu431_vec_int &veca, __sfu431_vec_int &vecb,
                                __sfu431_mask &mask);

void _sfu431_vadd_float(__sfu431_vec_float &vecResult, __sfu431_vec_float &veca,
                        __sfu431_vec_float &vecb, __sfu431_mask &mask) {
  _sfu431_vadd<float>(vecResult, veca, vecb, mask);
}
void _sfu431_vadd_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca,
                      __sfu431_vec_int &vecb, __sfu431_mask &mask) {
  _sfu431_vadd<int>(vecResult, veca, vecb, mask);
}

template <typename T>
void _sfu431_vsub(__sfu431_vec<T> &vecResult, __sfu431_vec<T> &veca,
                  __sfu431_vec<T> &vecb, __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    vecResult.value[i] =
        mask.value[i] ? (veca.value[i] - vecb.value[i]) : vecResult.value[i];
  }
  SFU431Logger.addLog("vsub", mask, VECTOR_WIDTH);
}

template void _sfu431_vsub<float>(__sfu431_vec_float &vecResult,
                                  __sfu431_vec_float &veca,
                                  __sfu431_vec_float &vecb,
                                  __sfu431_mask &mask);
template void _sfu431_vsub<int>(__sfu431_vec_int &vecResult,
                                __sfu431_vec_int &veca, __sfu431_vec_int &vecb,
                                __sfu431_mask &mask);

void _sfu431_vsub_float(__sfu431_vec_float &vecResult, __sfu431_vec_float &veca,
                        __sfu431_vec_float &vecb, __sfu431_mask &mask) {
  _sfu431_vsub<float>(vecResult, veca, vecb, mask);
}
void _sfu431_vsub_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca,
                      __sfu431_vec_int &vecb, __sfu431_mask &mask) {
  _sfu431_vsub<int>(vecResult, veca, vecb, mask);
}

template <typename T>
void _sfu431_vmult(__sfu431_vec<T> &vecResult, __sfu431_vec<T> &veca,
                   __sfu431_vec<T> &vecb, __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    vecResult.value[i] =
        mask.value[i] ? (veca.value[i] * vecb.value[i]) : vecResult.value[i];
  }
  SFU431Logger.addLog("vmult", mask, VECTOR_WIDTH);
}

template void _sfu431_vmult<float>(__sfu431_vec_float &vecResult,
                                   __sfu431_vec_float &veca,
                                   __sfu431_vec_float &vecb,
                                   __sfu431_mask &mask);
template void _sfu431_vmult<int>(__sfu431_vec_int &vecResult,
                                 __sfu431_vec_int &veca, __sfu431_vec_int &vecb,
                                 __sfu431_mask &mask);

void _sfu431_vmult_float(__sfu431_vec_float &vecResult,
                         __sfu431_vec_float &veca, __sfu431_vec_float &vecb,
                         __sfu431_mask &mask) {
  _sfu431_vmult<float>(vecResult, veca, vecb, mask);
}
void _sfu431_vmult_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca,
                       __sfu431_vec_int &vecb, __sfu431_mask &mask) {
  _sfu431_vmult<int>(vecResult, veca, vecb, mask);
}

template <typename T>
void _sfu431_vdiv(__sfu431_vec<T> &vecResult, __sfu431_vec<T> &veca,
                  __sfu431_vec<T> &vecb, __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    vecResult.value[i] =
        mask.value[i] ? (veca.value[i] / vecb.value[i]) : vecResult.value[i];
  }
  SFU431Logger.addLog("vdiv", mask, VECTOR_WIDTH);
}

void _sfu431_vshiftright_int(__sfu431_vec_int &vecResult,
                             __sfu431_vec_int &veca, __sfu431_vec_int &vecb,
                             __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++)
    vecResult.value[i] =
        mask.value[i] ? (veca.value[i] >> vecb.value[i]) : vecResult.value[i];
}

void _sfu431_vbitand_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca,
                         __sfu431_vec_int &vecb, __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++)
    vecResult.value[i] =
        mask.value[i] ? (veca.value[i] & vecb.value[i]) : vecResult.value[i];
}

template void _sfu431_vdiv<float>(__sfu431_vec_float &vecResult,
                                  __sfu431_vec_float &veca,
                                  __sfu431_vec_float &vecb,
                                  __sfu431_mask &mask);
template void _sfu431_vdiv<int>(__sfu431_vec_int &vecResult,
                                __sfu431_vec_int &veca, __sfu431_vec_int &vecb,
                                __sfu431_mask &mask);

void _sfu431_vdiv_float(__sfu431_vec_float &vecResult, __sfu431_vec_float &veca,
                        __sfu431_vec_float &vecb, __sfu431_mask &mask) {
  _sfu431_vdiv<float>(vecResult, veca, vecb, mask);
}
void _sfu431_vdiv_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca,
                      __sfu431_vec_int &vecb, __sfu431_mask &mask) {
  _sfu431_vdiv<int>(vecResult, veca, vecb, mask);
}

template <typename T>
void _sfu431_vabs(__sfu431_vec<T> &vecResult, __sfu431_vec<T> &veca,
                  __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    vecResult.value[i] =
        mask.value[i] ? (abs(veca.value[i])) : vecResult.value[i];
  }
  SFU431Logger.addLog("vabs", mask, VECTOR_WIDTH);
}

template void _sfu431_vabs<float>(__sfu431_vec_float &vecResult,
                                  __sfu431_vec_float &veca,
                                  __sfu431_mask &mask);
template void _sfu431_vabs<int>(__sfu431_vec_int &vecResult,
                                __sfu431_vec_int &veca, __sfu431_mask &mask);

void _sfu431_vabs_float(__sfu431_vec_float &vecResult, __sfu431_vec_float &veca,
                        __sfu431_mask &mask) {
  _sfu431_vabs<float>(vecResult, veca, mask);
}
void _sfu431_vabs_int(__sfu431_vec_int &vecResult, __sfu431_vec_int &veca,
                      __sfu431_mask &mask) {
  _sfu431_vabs<int>(vecResult, veca, mask);
}

template <typename T>
void _sfu431_vgt(__sfu431_mask &maskResult, __sfu431_vec<T> &veca,
                 __sfu431_vec<T> &vecb, __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    maskResult.value[i] =
        mask.value[i] ? (veca.value[i] > vecb.value[i]) : maskResult.value[i];
  }
  SFU431Logger.addLog("vgt", mask, VECTOR_WIDTH);
}

template void _sfu431_vgt<float>(__sfu431_mask &maskResult,
                                 __sfu431_vec_float &veca,
                                 __sfu431_vec_float &vecb, __sfu431_mask &mask);
template void _sfu431_vgt<int>(__sfu431_mask &maskResult,
                               __sfu431_vec_int &veca, __sfu431_vec_int &vecb,
                               __sfu431_mask &mask);

void _sfu431_vgt_float(__sfu431_mask &maskResult, __sfu431_vec_float &veca,
                       __sfu431_vec_float &vecb, __sfu431_mask &mask) {
  _sfu431_vgt<float>(maskResult, veca, vecb, mask);
}
void _sfu431_vgt_int(__sfu431_mask &maskResult, __sfu431_vec_int &veca,
                     __sfu431_vec_int &vecb, __sfu431_mask &mask) {
  _sfu431_vgt<int>(maskResult, veca, vecb, mask);
}

template <typename T>
void _sfu431_vlt(__sfu431_mask &maskResult, __sfu431_vec<T> &veca,
                 __sfu431_vec<T> &vecb, __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    maskResult.value[i] =
        mask.value[i] ? (veca.value[i] < vecb.value[i]) : maskResult.value[i];
  }
  SFU431Logger.addLog("vlt", mask, VECTOR_WIDTH);
}

template void _sfu431_vlt<float>(__sfu431_mask &maskResult,
                                 __sfu431_vec_float &veca,
                                 __sfu431_vec_float &vecb, __sfu431_mask &mask);
template void _sfu431_vlt<int>(__sfu431_mask &maskResult,
                               __sfu431_vec_int &veca, __sfu431_vec_int &vecb,
                               __sfu431_mask &mask);

void _sfu431_vlt_float(__sfu431_mask &maskResult, __sfu431_vec_float &veca,
                       __sfu431_vec_float &vecb, __sfu431_mask &mask) {
  _sfu431_vlt<float>(maskResult, veca, vecb, mask);
}
void _sfu431_vlt_int(__sfu431_mask &maskResult, __sfu431_vec_int &veca,
                     __sfu431_vec_int &vecb, __sfu431_mask &mask) {
  _sfu431_vlt<int>(maskResult, veca, vecb, mask);
}

template <typename T>
void _sfu431_veq(__sfu431_mask &maskResult, __sfu431_vec<T> &veca,
                 __sfu431_vec<T> &vecb, __sfu431_mask &mask) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    maskResult.value[i] =
        mask.value[i] ? (veca.value[i] == vecb.value[i]) : maskResult.value[i];
  }
  SFU431Logger.addLog("veq", mask, VECTOR_WIDTH);
}

template void _sfu431_veq<float>(__sfu431_mask &maskResult,
                                 __sfu431_vec_float &veca,
                                 __sfu431_vec_float &vecb, __sfu431_mask &mask);
template void _sfu431_veq<int>(__sfu431_mask &maskResult,
                               __sfu431_vec_int &veca, __sfu431_vec_int &vecb,
                               __sfu431_mask &mask);

void _sfu431_veq_float(__sfu431_mask &maskResult, __sfu431_vec_float &veca,
                       __sfu431_vec_float &vecb, __sfu431_mask &mask) {
  _sfu431_veq<float>(maskResult, veca, vecb, mask);
}
void _sfu431_veq_int(__sfu431_mask &maskResult, __sfu431_vec_int &veca,
                     __sfu431_vec_int &vecb, __sfu431_mask &mask) {
  _sfu431_veq<int>(maskResult, veca, vecb, mask);
}

template <typename T>
void _sfu431_hadd(__sfu431_vec<T> &vecResult, __sfu431_vec<T> &vec) {
  for (int i = 0; i < VECTOR_WIDTH / 2; i++) {
    T result = vec.value[2 * i] + vec.value[2 * i + 1];
    vecResult.value[2 * i] = result;
    vecResult.value[2 * i + 1] = result;
  }
}

template void _sfu431_hadd<float>(__sfu431_vec_float &vecResult,
                                  __sfu431_vec_float &vec);

void _sfu431_hadd_float(__sfu431_vec_float &vecResult,
                        __sfu431_vec_float &vec) {
  _sfu431_hadd<float>(vecResult, vec);
}

template void _sfu431_hadd<int>(__sfu431_vec_int &vecResult,
                                  __sfu431_vec_int &vec);

void _sfu431_hadd_int(__sfu431_vec_int &vecResult,
                        __sfu431_vec_int &vec)
{
  _sfu431_hadd<int>(vecResult, vec);
}

template <typename T>
void _sfu431_interleave(__sfu431_vec<T> &vecResult, __sfu431_vec<T> &vec) {
  for (int i = 0; i < VECTOR_WIDTH; i++) {
    int index =
        i < VECTOR_WIDTH / 2 ? (2 * i) : (2 * (i - VECTOR_WIDTH / 2) + 1);
    vecResult.value[i] = vec.value[index];
  }
}

template void _sfu431_interleave<float>(__sfu431_vec_float &vecResult,
                                        __sfu431_vec_float &vec);

template void _sfu431_interleave<int>(__sfu431_vec_int &vecResult,
                                        __sfu431_vec_int &vec);

void _sfu431_interleave_float(__sfu431_vec_float &vecResult,
                              __sfu431_vec_float &vec) {
  _sfu431_interleave<float>(vecResult, vec);
}

void _sfu431_interleave_int(__sfu431_vec_int &vecResult,
                              __sfu431_vec_int &vec)
{
  _sfu431_interleave<int>(vecResult, vec);
}

void addUserLog(const char *logStr) {
  SFU431Logger.addLog(logStr, _sfu431_init_ones(), 0);
}

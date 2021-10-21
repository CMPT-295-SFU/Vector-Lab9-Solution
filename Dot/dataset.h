#define SIZE 16
#define VLEN 8
int input_X[SIZE] = {-3, 3, 6, 3,  7,  4,  3, 5,
                               7,  2, 5, -2, -5, -8, 0, -9};
int input_Y[SIZE] = {-8, -3, 9,  -7, 1, 0,  -3, -10,
                               -2, -7, 10, 2,  6, -2, -2, 6};
int gold_data[SIZE + VLEN] = {
    24,     -9,     54,     -21,    7,      0,      -9,     -50,
    -14,    -14,    50,     -4,     -30,    16,     0,      -54,
    0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef};
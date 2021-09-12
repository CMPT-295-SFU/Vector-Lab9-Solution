#define SIZE 12
#define VECTOR_WIDTH 8
int input_X[SIZE] = {-3, 3, 6, 3,  7,  4,  3, 5,
                               7,  2, 5, -2};
int input_Y[SIZE] = {-8, -3, 9,  -7, 1, 0,  -3, -10,
                               -2, -7, 10, 2};
int gold_data[SIZE + VECTOR_WIDTH] = {
    24,     -9,     54,     -21,    7,      0,      -9,     -50,
    -14,    -14,    50,     -4, // Gold data ends here
    // Padding to detect overflow errors in vector impelementation
    0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef, 0xbeef};
In this lab, you will write vector code to gain a better understanding of
how data-parallel code maps to vector-style processors, and to practice optimizing vector
code for a given implementation.

# Check yourself
- Have you gone through Week 9 videos?
- What is vector code trying to optimize? 
- What is a vector ? (a one-dimensional array data structure) 

The programming model is best explained by using a simple application. We use a simple dot multiplication of two arrays. The equivalent RISC-V code is shown as well. 

Looking at the C code it 

```c
void DotSerial(int x[], int y[], int output[], int N) {
  for (int i = 0; i < N; i++) {
    output[i] = x[i] * y[i];
  }
}
```

```asm
loop:
    # load x[i] and y[i]
    lw      a4,0(a5)
    lw      a3,0(a1)
    # multiplication
    mul     a4,a4,a3
    # store word
    sw      a4,0(a2)
    # Bump pointers
    addi    a5,a5,4
    addi    a1,a1,4
    addi    a2,a2,4
    bne     a5,a0,loop
````
**Limitations**
- You can see that there is only useful instruction performing the actual multiplication and 8 other instructions loading data and manipulating the loop. For the entire loop we need 8*n instructions. How do we reduce the number of instructions for performing this computation?
**How do you increase operational intensity? i.e., get instructions to process more data than a single element**

- It appears that you are calculating the output one at a time; however if you unrolled and wrote down the loop manually. You can see that each of the loop iterations are independent of each other. output[0] requires only x[0] and y[0], output[1] requires x[1] and y[1]. **How can we exploit the observation to work on multiple elements in parallel**


```   
    output[0] = x[0] * y[0];
    output[1] = x[1] * y[1];
    output[2] = x[2] * y[2];
    output[3] = x[3] * y[3];
    ...
    output[N] = x[N] * y[N];
```

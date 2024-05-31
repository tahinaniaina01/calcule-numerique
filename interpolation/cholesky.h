#ifndef CHOLESKY_H
    #define CHOLESKY_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    float **allocFloat2D(int l, int c);
    void freeFloat2D(float **tab,int l,int c);
    void cleanup(float* b, float* x, float **M, int dim);
    void print2D(float **tab,int l,int c);
    void getDataF(int *dim, float ***A, float **b,float **x);
    void cholesky(float *x,float **A, float *b, int dim);
    void displayResult(float* x, float* b, float** A, int dim);

#endif
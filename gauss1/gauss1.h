#ifndef GAUSS1_H
    #define GAUSS1_H

    #include <stdio.h>
    #include <stdlib.h>

    void getData(int *dim, float ***A, float **b,float **x);
    void getDataF(int *dim, float ***A, float **b,float **x);
    void triangulation(float **a,float *b,int n);
    void gauss(float *x,float **A, float *b, int dim);
    void displayResult(float* x, float* b, float** A, int dim);
    float **allocFloat2D(int l, int c);
    void print2D(float **tab,int l,int c);
    void cleanup(float* b, float* x, float **A, int dim);

#endif
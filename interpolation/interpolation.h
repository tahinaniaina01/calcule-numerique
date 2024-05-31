#ifndef INTERPOLATION_H
  #define INTERPOLATION_H

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  
  void getData(float *xmin, float *xmax, float *ymin, float * ymax, float **x, float **y, int *dim);
  void gplot(float xmin, float xmax, float ymin, float ymax, float *x, float *y, int dim);
  void cleanupI(float *x, float *y);
  float Lagrange(float xi,float *x, float *y, int dim);
  float dj(int j, float *x);
  float lamdaJ(int j, float *x);
  float pj(int j, float *x);
  float Yj(int j, float *x, float *y);
  float S2j(int J, float *x, float *y, int dim);
  float aj(int j, float *x, float *y, int dim);
  float bj(int j, float *x, float *y, int dim);
  float Sx(float xi, float *x, float *y, int dim);

#endif
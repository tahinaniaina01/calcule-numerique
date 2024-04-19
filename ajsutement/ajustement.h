#ifndef AJUSTEMENT_H
    #define AJUSTEMENT_H

    #include <stdio.h>
    #include <stdlib.h>

    void error(const char *message);
    float *newVect(int dim);
    void getData(char *filename, float *xmin, float *xmax, float *ymin, float *ymax, int *dim, float **xd, float **yd);
    // void gplot(float *xd, float *yd, float xmin, float xmax, float ymin, float ymax, int dim, float *als);
    void gplot(float ymin, float ymax, float *als);
    void linLastSq(float *xd, float *yd, int dim, float *a);
    void leastSquare(float *xd, float *yd, int dim, float *a);

#endif
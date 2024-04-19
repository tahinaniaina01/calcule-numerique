#ifndef DESCENTE_H
    #define DESCENTE_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    void getData(float *x0, float *alpha, float *xmin, float *xmax);
    void gplot(float x0, float alpha, float xmin, float xmax);
    void descente(float x0, float alpha);
    float f(float x);
    double derive(double x);
    void descente(float x0, float alpha);
    int getChoice();
    int menu();
    int whatToDo(int choice, float *x0, float *alpha, float xmin, float xmax);

#endif
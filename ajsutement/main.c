#include "ajustement.h"

int main(){
    //char filename[] = "data1.txt";
    float xmin;
    float xmax;
    float ymin;
    float ymax;
    int dim;
    float *xd;
    float *yd;
    float *a = malloc(sizeof(float)*2);

    getData("data1.txt", &xmin, &xmax, &ymin, &ymax, &dim, &xd, &yd);

    linLastSq(xd, yd, dim, a);

    gplot(ymin, ymax, a);

    free(a);
    return 0;
}
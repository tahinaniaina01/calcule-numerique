#include "interpolation.h"

int main(){
  float xmin = 0.0,
        xmax = 0.0,
        ymin = 0.0,
        ymax = 0.0;
  float *x;
  float *y;
  int dim;

  getData(&xmin, &xmax, &ymin, &ymax, &x, &y, &dim);
  gplot(xmin, xmax, ymin, ymax, x, y, dim);

  // for(int i=0; i<dim; i++){
  //   float xi = x[i];
  //   float yi = Sx(xi, x, y, dim);
  //   printf("%g %g\n", xi, yi);
  // }

  return 0;
}
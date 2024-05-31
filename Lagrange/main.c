#include "Lagrange.h"

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

  return 0;
}
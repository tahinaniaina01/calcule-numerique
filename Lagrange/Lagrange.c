#include "Lagrange.h"

float Lagrange(float xi,float *x, float *y, int dim){
  float lagrange = 0.0;

  for(int j=0; j<dim; j++){
    float p = y[j];
    for(int k=0; k<dim; k++){
      if(k != j){
        p = p * ( (xi - x[k]) / (x[j] - x[k]) );
      }
    }
    lagrange = lagrange + p;
  }
  
  return lagrange;
}

void getData(float *xmin, float *xmax, float *ymin, float * ymax, float **x, float **y, int *dim){
  float *X = NULL;
  float *Y = NULL;
  FILE * file;
  *xmin = -1.0;
  *xmax = 7.0;
  *ymin = -3.0;
  *ymax = 3.0;
  file = fopen("data.txt", "r");
  if(file == NULL){
    printf("erreur d'ouverture du fichier data.txt\n");
    cleanupI(X,Y);
    exit(1);
  }
  fscanf(file,"%d",dim);

  X = (float*)malloc(sizeof(float) * (*dim));
  if(X == NULL){
    printf("erreur d'allocation de X\n");
    exit(1);
  }

  Y = (float*)malloc(sizeof(float) * (*dim));
  if(Y == NULL){
    printf("erreur d'allocation de Y\n");
    if(X != NULL)
      free(X);
    exit(1);
  }

  for(int i=0; i<(*dim); i++)
    fscanf(file,"%f, %f", &X[i], &Y[i]);

  *x = X;
  *y = Y;

  fclose(file);
}

void gplot(float xmin, float xmax, float ymin, float ymax, float *X, float *Y, int dim){
  FILE *gp = popen("gnuplot -persist", "w");
  float x = 0.0,
        y = 0.0;

  fprintf(gp, "set title 'Traceur gnuplot'\n");
  fprintf(gp, "set xzeroaxis\n");
  fprintf(gp, "set yzeroaxis\n");

  fprintf(gp,"$data1 << EOF\n");
  for(int i=0; i<dim; i++){
    fprintf(gp,"%g %g\n", X[i], Y[i]);
  }
  fprintf(gp,"EOF\n");

  fprintf(gp,"$data2 << EOF\n");
  float pas = (float)(xmax-xmin)/100;
  for(float i=xmin; i<xmax; i+=pas){
    x = i;
    y = Lagrange(i, X, Y, dim);
    if(y>ymax)
      ymax = y;
    fprintf(gp,"%g %g\n", x, y);
  }
  fprintf(gp,"EOF\n");

  fprintf(gp, "plot [x=%g:%g] [y=%g:%g] $data1 using 1:2 with linespoints pt 7 ps 1, $data2 w l lc 'red' lw 1\n",xmin,xmax,ymin,ymax);

  pclose(gp);
}

void cleanupI(float *x, float *y){
  if(x != NULL){
    free(x);
    printf("liberation de x\n");
  }
  if(y != NULL){
    free(y);
    printf("liberation de x\n");
  }
}

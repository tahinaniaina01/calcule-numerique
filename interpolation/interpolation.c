#include "interpolation.h"
#include "cholesky.h"

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
  *xmin = 0;
  *xmax = 6.0;
  *ymin = -2.0;
  *ymax = 2.0;
  file = fopen("data1.txt", "r");
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

  fprintf(gp,"$data3 << EOF\n");
  pas = (float)(xmax-xmin)/100;
  for(float i=xmin; i<xmax; i+=pas){
    x = i;
    y = Sx(i, X, Y, dim);
    if(y>ymax)
      ymax = y;
    fprintf(gp,"%g %g\n", x, y);
  }
  fprintf(gp,"EOF\n");

  fprintf(gp, "plot [x=%g:%g] [y=%g:%g] $data1 using 1:2 with linespoints pt 7 ps 1, $data2 w l lc 'blue' lw 1,  $data3 w l lc 'red' lw 1\n",xmin-1,xmax+1,ymin-1,ymax+1);

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

// splines cubique
float dj(int j, float *x){
  return x[j+1] - x[j];
}

float lamdaJ(int j, float *x){
  return dj(j, x) / (dj(j-1, x) + dj(j,x));
}

float pj(int j, float *x){
  return 1 - lamdaJ(j, x);
}

float Yj(int j, float *x, float *y){
  return ( 6 / (dj(j-1,x) + dj(j,x)) ) * ( ( (y[j+1]-y[j]) / dj(j,x) ) - ( (y[j] - y[j-1]) / dj(j-1,x) )) ;
}

float S2j(int J, float *x, float *y, int dim){
  float *sj=NULL;
  float **A = allocFloat2D(dim-2, dim-2);
  float *Y = NULL;
  int p = 1;
  int a = 1;
  int cy = 1;
  float *s = NULL;

  for(int i=0; i<dim-2; i++){
    for(int j=0; j<dim-2; j++){
      if(i==j)
        A[i][j] = 2;
      else if(i+1==j){
        A[i][j] = pj(p,x);
        p++;
      }
      else if(i==j+1){
        A[i][j] = lamdaJ(a,x);
        a++;
      }
      else{
        A[i][j] = 0;
      }
    }
  }

  Y = (float*)malloc(sizeof(float)*(dim-2));
  if(Y == NULL){
    printf("erreur d'allocation\n");
    exit(1);
  }

  for(int i=0; i<dim-2; i++){
    Y[i] = Yj(cy, x, y);
    cy++;
  }

  s = (float*)malloc(sizeof(float)*(dim-2));

  cholesky(s, A, Y, dim-2);

  sj = (float*)malloc(sizeof(float)*dim);

  if(sj == NULL){
    printf("erreur d'allocation de sj\n");
    cleanupI(x,y);
    exit(1);
  }

  sj[0] = 0.0;
  for(int i=0; i<dim-2; i++){
    sj[i+1] = s[i];
  }
  sj[dim-1] = 0.0;

  free(Y);

  return sj[J];
}

float aj(int j, float *x, float *y, int dim){
  float a = 0.0;
  a = ( (y[j]/dj(j,x)) - S2j(j, x, y, dim)*(dj(j, x) / 6));
  return a;
}

float bj(int j, float *x, float *y, int dim){
  float b = 0.0;
  b = (y[j+1] / dj(j,x)) - (S2j(j+1, x, y, dim) * (dj(j,x) / 6));
  return b;
}

float Sx(float xi, float *x, float *y, int dim){
  float s = 0.0;
  int j = 0;
  for(int k=0; k<dim; k++){
    if(xi >= x[k] && xi <= x[k+1]){
      j = k;
      break;
    }
  }

  float tmp1 = (x[j+1] - xi)*(x[j+1] - xi)*(x[j+1] - xi); 
  float tmp2 = (xi - x[j])*(xi - x[j])*(xi - x[j]);

  // printf("tmp1 : %g | tmp2 = %g\n", tmp1, tmp2);
  // printf("s2J : %g | s2J+1 = %g\n", S2j(j, x, y, dim), S2j(j+1, x, y, dim));
  // printf("dj = %g\n",dj(j,x));

  s = ( (float)1/(6*dj(j,x)) ) * ( S2j(j, x, y, dim)*tmp1 + (S2j(j+1, x, y, dim)*tmp2 ));
  // printf("a : %g | b = %g\n", aj(j, x, y,dim)*(x[j+1] - xi) , bj(j, x, y, dim)*( xi - x[j] ));
  s = s + ( aj(j, x, y,dim)*(x[j+1] - xi) ) + ( bj(j, x, y, dim)*( xi - x[j] ) );
  return s;
}

#include <stddef.h>
void tridiag(float *a, float *b, float *c,float *r, float *u, int n);
float *newVect(int dim);
void problem(char* message);

void solveS2(float* lambda, float* rho, float *Y, float *s2, int dim){
    float *B=NULL, *C=NULL, *D=NULL;
    int j=0;

    B = newVect(dim);			// diagonale principale
    C = newVect(dim);			// première surdiagonale
    D = newVect(dim);			// première sous-diagonale
    for(j=0; j<dim; j++){
        B[j] = 2;
        C[j] = lambda[j];		// on ne suppose pas que les points sont équidistants
        D[j] = rho[j];
    }
    tridiag(D,B,C,Y,s2,dim);
}

/* Tridiagonal matrix solver.  Nonzero diagonals of the matrix are
  represented by arrays a, b, and c (see Numerical Recipes).
  All arrays start at 0
  [b_0 c_0                  ] [ u_0 ]   [ r_0 ]
  [a_1 b_1 c_1              ] [ u_1 ]   [ r_1 ]
  [          ...            ] [ ... ] = [ ... ]
  [        a_n-2 b_n-2 c_n-2] [u_n_2]   [r_n-2]
  [              a_n-1 b_n-1] [u_n-1]   [r_n-1]
 */
void tridiag(float *a, float *b, float *c,float *r, float *u, int n){
    int j;
    float bet, gam[n];

    if (b[0] == 0.0) problem("Division par 0");
    u[0] = r[0] / (bet=b[0]);
    for (j = 1; j < n; j++) {
        gam[j] = c[j-1]/bet;
        bet = b[j] - a[j]*gam[j];
        if (bet == 0.0) problem("Division par 0");
        u[j] = (r[j]-a[j]*u[j-1]) / bet;
    }
    for (j = n-2; j >= 0; j--)
        u[j] -= gam[j+1]*u[j+1];
}

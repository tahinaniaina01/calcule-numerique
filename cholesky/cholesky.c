#include "cholesky.h"

float **allocFloat2D(int l, int c){
    float **res = (float**)malloc(sizeof(float*)*l);
    if(res == NULL){
        printf("Erreur d'allocation du float 2 dimention\n");
        return NULL;
    }
    for(int i=0; i<l;i++){
        res[i] = NULL;
        res[i] = (float*)malloc(sizeof(float)*c);
        if(res == NULL){
            printf("Erreur d'allocation d'une des tableau du float 2 dimention\n");
            return NULL;
        }
    }
    return res;
}

// Libération du mémoire allouer dynamiquement par allocFloat2D
void freeFloat2D(float **tab,int l,int c){
    for(int i=0; i<l;i++){
        if(tab[i] != NULL)
            free(tab[i]);
    }
    if(tab != NULL)
        free(tab);
}


void cleanup(float* b, float* x, float **M, int dim){
    if(x != NULL){
        free(b);
        printf("je libère b\n");
    }
    if(x != NULL){
        free(x);
        printf("Je libère x\n");
    }
    freeFloat2D(M,dim,dim);
    printf("Je libère A\n");
}

void print2D(float **tab,int l,int c){
    for(int i=0; i<l; i++){
        for(int j=0; j<c; j++){
            printf("%g ",tab[i][j]);
        }
        printf("\n");
    }
}

void getDataF(int *dim, float ***A, float **b,float **x){
    printf("Voici les données\n");
    float *s = NULL,        // pointeur pour la solution
          *v = NULL;        // pointeur pour la second membre
    float **mat = NULL;     // pointeur pour la matrice
    FILE *data = fopen("data3.txt","r");

    if(data == NULL){
        printf("Erreur d'ouverture du fichier");
        exit(1);
    }

    fscanf(data,"%d",dim);

    mat = allocFloat2D(*dim, *dim);

    if(mat == NULL){
        printf("Erreur d'allocation du matrice A\n");
        cleanup(*b,*x,*A,*dim);
    }

    for(int i=0;i<*dim;i++){
        for(int j=0;j<*dim;j++){
            fscanf(data,"%f",&mat[i][j]);
        }
    }

    s = (float*)malloc(*dim * sizeof(float));
    if(s == NULL){
        printf("Erreur d'allocation de v\n");
        exit(1);
    }
    
    for(int i=0; i<*dim; i++)
        fscanf(data,"%f",&s[i]);

    v = (float*)malloc(*dim * sizeof(float));
    if(v == NULL){
        printf("Erreur d'allocation de v\n");
        exit(1);
    }
    for(int i=0; i<*dim; i++)
        v[i] = i;

    *b = s;
    *x = v;
    *A = mat;
    fclose(data);
}

void cholesky(float *x,float **A, float *b, int dim){
// Factoriser A: A=B.Bt sachant qu'on travaille en place

    float tmp = 0;
    for(int i=0; i<dim; i++){
        for(int j=0; j<i; j++){
            tmp = 0;
            for(int k=0; k<j; k++)
                tmp += A[i][k] * A[j][k];
            A[i][j] = (A[i][j] - tmp) / A[j][j];
        }
        tmp = 0;
        for(int k=0; k<i; k++)
            tmp += A[i][k] * A[i][k];
        A[i][i] = sqrt(A[i][i] - tmp);
    }

    printf("Matrice B du devoir : \n");
    print2D(A,dim,dim);

    // Resolution de B.y = b
    float *y = NULL;
    y = (float*)malloc(sizeof(float)*dim);
    if(y == NULL){
        printf("Une erreur d'allocation à été produit");
        cleanup(b,x,A,dim);
        exit(1);
    }

    for(int i=0; i<dim; i++){
        float tmp = 0;
        for(int j=0; j<i; j++){
            tmp += A[i][j] * y[j];
        }
        y[i] = (b[i] - tmp) / A[i][i];
    }

    printf("\n");
    // Résolution de Bt.x = y
    for(int i=dim-1; i>=0; i--){
        float tmp = 0;
        for(int j=i+1; j<dim; j++){
            tmp += A[j][i] * x[j];
        }
        x[i] = (y[i] - tmp) / A[i][i];
    }
}

void displayResult(float* x, float* b, float** A, int dim){
    printf("Voici le resultat\n");

    printf("dim = %d\n\n",dim);

    printf("Voici la Matrice A:\n");
    //print2D(A,dim,dim);
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++)
            printf("%g ",A[i][j]);
        printf("\n");
    }
    printf("\n");

    printf("Voici le vecteur b :\n");
    for(int i=0; i<dim; i++)
        printf("b[%d] = %g\n", i, b[i]);
    printf("\n");
    
    printf("Voici le vecteur x :\n");
    for(int i=0; i<dim; i++)
        printf("x[%d] = %g\n", i, x[i]);
    printf("\n");

}
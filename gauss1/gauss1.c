#include "gauss1.h"


// Allocation dynamique d'un tableau float 2D
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
            exit(1);
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
    char a[100];

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
    //printf("Erreur %d\n",*dim);
    
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


void getData(int *dim, float ***A, float **b,float **x){
    printf("Voici les données\n");
    float *s = NULL,        // pointeur pour la solution
          *v = NULL;        // pointeur pour la second membre
    float **mat = NULL;     // pointeur pour la matrice

    *dim = 4;

    mat = allocFloat2D(*dim, *dim);

    if(mat == NULL){
        printf("Erreur d'allocation du matrice A\n");
        cleanup(*b,*x,*A,*dim);
    }

    for(int i=0;i<*dim;i++){
        for(int j=0;j<*dim;j++){
            mat[i][j] = i + j;
        }
    }

    s = (float*)malloc(*dim * sizeof(float));
    if(s == NULL){
        printf("Erreur d'allocation de v\n");
        exit(1);
    }
    for(int i=0; i<*dim; i++)
        s[i] = i - 1.78;

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
}


// transformatio du matrice A en matrice triangle supérieur
void triangulation(float **a,float *b,int n){
    for(int k=0; k<n; k++){
        for(int i=k+1; i<n; i++){
            for(int j=k+1; j<n; j++){
                a[i][j] = a[i][j] - a[i][k] / a[k][k] * a[k][j];
            }
            b[i] = b[i] - a[i][k] / a[k][k] * b[k];
            a[i][k] = 0;
        }
    }
}

void gauss(float *x,float **A, float *b, int dim){
    printf("matrice A : \n");
    print2D(A,dim,dim);
    // Triangulation 
    triangulation(A, b, dim);
    printf("Voici la Matrice triangulare:\n");
    print2D(A,dim,dim);
    printf("\n");

    // Resolution du système triangulaire
    for(int i=dim-1; i>=0; i--){
        float tmp = 0;
        for(int j=i+1; j<=dim-1; j++){
            tmp += A[i][j] * x[j];
        }
        x[i] = (b[i] - tmp) / A[i][i]  ;
    }
}

void displayResult(float* x, float* b, float** A, int dim){
    printf("Voici le resultat\n");

    printf("dim = %d\n\n",dim);

    // printf("Voici la Matrice A:\n");
    // print2D(A,dim,dim);
    // printf("\n");

    printf("Voici le vecteur b :\n");
    for(int i=0; i<dim; i++)
        printf("b[%d] = %g\n", i, b[i]);
    printf("\n");
    
    printf("Voici le vecteur x :\n");
    for(int i=0; i<dim; i++)
        printf("x[%d] = %g\n", i, x[i]);
    printf("\n");

}
#include "cholesky.h"

int main(){
    printf("Resolution de A.x=b par le methode de Cholesky\n");
    // Entrée des données
    int dim = 1;            
    float **A = NULL;           // adresse de la matrice du problème
    float *b = NULL;            // adresse du vecteur second membre
    float *x = NULL;            // adresse du vecteur solution

    getDataF(&dim, &A, &b, &x);  // donne à getData les adresse à utiliser

    // Traitement
    cholesky(x, A, b, dim);

    // Sortie des resultats
    displayResult(x, b, A, dim);

    // Netoyage des espaces alloués dynamiquement
    cleanup(b, x, A, dim);

    return 0;
}
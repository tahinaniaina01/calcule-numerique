#include "gaussPiv.h"

int main(){

    printf("Resolution de A.x=b par le methode de Gauss\n");
    // Entrée des données
    int dim = 1;            
    float **A = NULL;           // adresse de la matrice du problème
    float *b = NULL;            // adresse du vecteur second membre
    float *x = NULL;            // adresse du vecteur solution
    int *p = NULL;              // adresse des indice

    getDataF(&dim, &A, &b, &x, &p);  // donne à getData les adresse à utiliser

    // Traitement
    gauss(x, A, b, p, dim);

    // Sortie des resultats
    displayResult(x, b, A, p, dim);

    // Netoyage des espaces alloués dynamiquement
    cleanup(b, x, A, dim);

    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void alloue_tableau (int **T,int n){
    *T = (int *)malloc(n * sizeof(int));
}

void desalloue_tableau(int *T) {
    if (T != NULL) {
        free(T);
    }
}

void remplir_tableau(int *T, int taille, int V){
    srand(time(NULL));  //facultatif

    for (int i = 0; i < taille; i++)
    {
        T[i] = rand() % V;
    }
}

void afficher_tableau(const int *T, int taille) {
    printf("Tableau T :\n[");
    
    for (int i = 0; i < taille; i++) {
        if(i+1 == taille){
            printf("%d]", T[i]);
        }
        else{
            printf("%d, ", T[i]);
        }
    }
    printf("\n");
}

int main() {
    int *monTableau;
    int tailleTableau = 10;
    int valeurMax = 100;

    alloue_tableau(&monTableau, tailleTableau);

    remplir_tableau(monTableau, tailleTableau, valeurMax);

    afficher_tableau(monTableau, tailleTableau);

    desalloue_tableau(monTableau);

    return 0;
}
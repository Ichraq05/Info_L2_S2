#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "biblioH.h"
#include "biblioLC.h"
#include "entreeSortieLC.h"
#include "entreeSortieH.h"


void mesurer_temps_recherche(char *fichier, int n) {

    Biblio *b = charger_n_entrees(fichier, n);
    Biblio *b2 = charger_n_entreesH(fichier, n);
    if (b == NULL ||b2 == NULL) {
        printf("Erreur lors du chargement du fichier.\n");
        return;
    }

    // Mesure le temps de recherche pour la structure de liste
    double temps_liste = 0.0;
    for (int i = 0; i < 10; i++) {
        clock_t debut_liste = clock();
        Livre *dup_liste = dupliques(b);
        clock_t fin_liste = clock();
        temps_liste += (double)(fin_liste - debut_liste) / CLOCKS_PER_SEC;
        liberer_livre(dup_liste);
    }
    temps_liste /= 10.0;

    // Mesure le temps de recherche pour la table de hachage
    double temps_table_hachage = 0.0;
    for (int i = 0; i < 10; i++) {
        clock_t debut_table_hachage = clock();
        LivreH *dup_table_hachage = dupliquesH(b2);
        clock_t fin_table_hachage = clock();
        temps_table_hachage += (double)(fin_table_hachage - debut_table_hachage) / CLOCKS_PER_SEC;
        liberer_livreH(dup_table_hachage);
    }
    temps_table_hachage /= 10.0;

    printf("Temps de recherche pour la structure de liste: %f secondes\n", temps_liste);
    printf("Temps de recherche pour la structure de hachage: %f secondes\n", temps_table_hachage);

    liberer_biblio(b);
    liberer_biblioH(b2);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("arguments manquants!\n");
        return 0;
    }

    int n = 1000;
    for (n; n <= 50000; n *= 2) {
        printf("Mesure du temps de recherche pour n = %d\n", n);
        mesurer_temps_recherche("GdeBiblio.txt", n);
    }

    printf("Fin.\n\n");
    return 0;
}
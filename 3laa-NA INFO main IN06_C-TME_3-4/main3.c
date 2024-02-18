#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Pour mesurer le temps d'exécution

#include "biblioLC.h"
#include "biblioH.h"

// Fonction pour mesurer le temps de recherche dans une liste chaînée
double mesurer_temps_recherche(Biblio *b, int num_recherches) {
    clock_t debut, fin;
    double temps_total = 0.0;

    for (int i = 0; i < num_recherches; i++) {
        debut = clock();

        // Exemple : recherche_livre_titre(b, "Titre");

        fin = clock();

        temps_total += ((double)(fin - debut)) / CLOCKS_PER_SEC;
    }

    // Retourner le temps moyen de recherche
    return temps_total / num_recherches;
}

// Fonction pour mesurer le temps de recherche dans une table de hachage
double mesurer_temps_recherche_hachage(BiblioH *b, int num_recherches) {
    clock_t debut, fin;
    double temps_total = 0.0;

    for (int i = 0; i < num_recherches; i++) {
        // Mesurer le temps de début
        debut = clock();

        // Effectuer la recherche
        // Exemple : recherche_livre_titre_hachage(b, "Titre");

        // Mesurer le temps de fin
        fin = clock();

        // Calculer le temps écoulé et l'ajouter au temps total
        temps_total += ((double)(fin - debut)) / CLOCKS_PER_SEC;
    }

    // Retourner le temps moyen de recherche
    return temps_total / num_recherches;
}

int main() {
    FILE *fichier; // Le fichier de données
    char ligne[256]; // Pour stocker chaque ligne du fichier

    // Ouvrir le fichier en mode lecture
    fichier = fopen("donnees.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Initialiser les variables pour stocker les données lues
    int num, num_lignes = 0;
    char titre[256], auteur[256];

    // Compter le nombre total de lignes dans le fichier
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        num_lignes++;
    }

    // Fermer et réouvrir le fichier pour le remettre au début
    fclose(fichier);
    fichier = fopen("donnees.txt", "r");

    // Variables pour stocker les temps de recherche
    double temps_recherche_liste, temps_recherche_hachage;
    int num_recherches = 100; // Nombre de recherches à effectuer

    // Boucle pour varier la taille de la bibliothèque
    for (int n = 1000; n <= 50000; n += 2) {
        // Créer une bibliothèque de la taille actuelle
        Biblio *bibliotheque_liste = creer_biblio();
        BiblioH *bibliotheque_hachage = creer_biblio(n); // Taille de la table de hachage

        // Lire les n premières lignes du fichier et les insérer dans les bibliothèques
        for (int i = 0; i < n; i++) {
            // Lire une ligne du fichier
            fgets(ligne, sizeof(ligne), fichier);
            sscanf(ligne, "%d %s %s", &num, titre, auteur);

            // Insérer dans la liste chaînée
            inserer_en_tete(bibliotheque_liste, num, titre, auteur);

            // Insérer dans la table de hachage
            inserer(bibliotheque_hachage, num, titre, auteur);
        }

        // Mesurer le temps de recherche pour chaque structure de données
        temps_recherche_liste = mesurer_temps_recherche(bibliotheque_liste, num_recherches);
        temps_recherche_hachage = mesurer_temps_recherche_hachage(bibliotheque_hachage, num_recherches);

        // Afficher les résultats ou les sauvegarder pour une visualisation ultérieure

        // Libérer la mémoire allouée pour les bibliothèques actuelles
        liberer_biblio(bibliotheque_liste);
        liberer_biblio_hachage(bibliotheque_hachage);
    }

    // Fermer le fichier
    fclose(fichier);

    return 0;
}

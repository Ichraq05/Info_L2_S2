#ifndef _BIBLIO_H_H_
#define _BIBLIO_H_H_

typedef struct livreh{
    int clef;
    int num;
    char *titre;
    char *auteur;
    struct livreh * suivant;
} LivreH;

typedef struct table {
    int nE; /*nombre d’elements contenus dans la table de hachage */
    int m; /*taille de la table de hachage */
    LivreH ** T; /*table de hachage avec resolution des collisions par chainage */
} BiblioH;

int fonctionClef(char* auteur);

LivreH* creer_livreH(int num,char* titre,char* auteur);

void liberer_livreH(LivreH* l);

BiblioH* creer_biblioH(int m);

void liberer_biblioH(BiblioH* b);

int fonctionHachageH(int cle, int m);

void insererH(BiblioH* b,int num,char* titre,char* auteur);

void afficher_livreH(LivreH* l);

void afficher_biblioH(BiblioH *b);

LivreH *recherche_livre_numH(BiblioH *b,int n);

LivreH *recherche_livre_titreH(BiblioH *b,char *titre);

BiblioH *recherche_livres_auteurH(BiblioH *b,char *auteur);

void supprimer_livreH(BiblioH* b,int num,char* titre,char* auteur);

void fusionH(BiblioH *b1, BiblioH *b2);

LivreH *dupliquesH(BiblioH *b);

#endif
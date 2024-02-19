#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioH.h"

int fonctionClef(char* auteur){
    int res=0;
    for(size_t i=0; i<strlen(auteur); i++){
        res+=auteur[i];
    }

    return res;
}

LivreH* creer_livreH(int num,char* titre,char* auteur){
    LivreH* new = (LivreH*)malloc(sizeof(LivreH));

    new->clef = fonctionClef(auteur);
    new->num = num;
    new->titre = strdup(titre);
    new->auteur = strdup(auteur);
    new->suivant = NULL;

    return new;
}

void liberer_livreH(LivreH* l){
    free(l->titre);
    free(l->auteur);

    free (l);
}



BiblioH* creer_biblioH(int m){
    BiblioH* b = (BiblioH*)malloc(sizeof(BiblioH));
    b->nE = 0;
    b->m = m;
    b->T = (LivreH **)malloc(sizeof(LivreH*)*m);

    return b;
}



void liberer_biblioH(BiblioH* b){

    for(int i=0; i<b->m; i++){
        LivreH* tmp = b->T[i];
        while(tmp){
            LivreH *s = tmp;
            tmp=tmp->suivant;
            liberer_livreH(s);
        }
    }

    free(b->T);
    free(b);
}



int fonctionHachage(int cle, int m){
    float a = (sqrt(5)-1)/2 ;
    return (int)(m*(cle*a - (int)(cle*a)));
}



void insererH(BiblioH* b,int num,char* titre,char* auteur){
    
    LivreH *l = creer_livreH(num,titre,auteur);
    int i = fonctionHachage(l->clef,b->m);

    l->suivant = b->T[i];

    b->T[i] = l;
    b->nE++;
}



void afficher_livreH(LivreH *l){
    if(l){
        printf("\nLivre numéro: %d\n   Titre: %s\n   Auteur: %s\n",l->num,l->titre,l->auteur);
    }
}



void afficher_biblioH(BiblioH *b){
    if(!b->nE){
        printf("\nLe biblio est vide!\n");
        return;
    }

    printf("\nLa biblio contient %d livre(s), le(s) voilà:\n",b->nE);
    for(int i=0; i<b->m; i++){
        LivreH *l = b->T[i];

        while(l){
            afficher_livreH(l);
            l=l->suivant;
        }
    }

}



LivreH *recherche_livre_numH(BiblioH *b,int n){
    
    if(!b->nE){
        printf("\nLe biblio est vide!\n");
        return NULL;
    }

    for(int i=0; i<b->m; i++){
        LivreH *l = b->T[i];

        while(l){
            if(l->num == n){
                printf("\nLivre trouvé!\n");
                return l;
            }
            l=l->suivant;
        }
    }
    
    printf("\nLivre non trouvé par numéro!\n");
    return NULL;
}



LivreH *recherche_livre_titreH(BiblioH *b,char *titre){

    if(!b->nE){
        printf("\nLe biblio est vide!\n");
        return NULL;
    }

    for(int i=0; i<b->m; i++){
        LivreH *l = b->T[i];

        while(l){
            if(!strcmp(l->titre,titre)){
                printf("\nLivre trouvé!\n");
                return l;
            }
            l=l->suivant;
        }
    }
    
    printf("\nLivre non trouvé par titre!\n");
    return NULL;
}



BiblioH *recherche_livres_auteurH(BiblioH *b,char *auteur){

    if(!b->nE){
        printf("\nLe biblio est vide!\n");
        return NULL;
    }
    
    BiblioH *res = NULL;

    int i = fonctionHachage(fonctionClef(auteur),b->m);
    LivreH *l = b->T[i];

    while(l){
        if(!strcmp(l->auteur,auteur)){
            if(!res){ //on fait en sorte que la biblioH ne soit pas créée à moins qu'on a trouvé un livreH
                res = creer_biblioH(1); //meme auteur donc meme clef pas une biblio comme cela suffit
            }
            insererH(res,l->num,l->titre,l->auteur);
        }
        l=l->suivant;
    }
    
    return res;
}



void supprimer_livreH(BiblioH* b,int num,char* titre,char* auteur){

    if(!b->nE){
        printf("\nLe biblio est vide!\n");
    }


    int i = fonctionHachage(fonctionClef(auteur),b->m);
    LivreH *tmp = b->T[i];
        
    if(tmp->num==num && !strcmp(tmp->titre,titre) && !strcmp(tmp->auteur,auteur)){
        b->T[i]=tmp->suivant;
        liberer_livreH(tmp);

        printf("\nLivre supprimé!\n");
        return ;
    }
    
    LivreH *s; //livreH suivant
    
    while(tmp){
        s = tmp->suivant;

        if(!s){
            printf("\nLivre non trouvé!\n");
            return;
        }

        if(s->num==num && !strcmp(s->titre,titre) && !strcmp(s->auteur,auteur)){
            tmp->suivant=s->suivant;
            liberer_livreH(s);

            printf("\nLivre supprimé!\n");
            return ;
        }
        tmp=tmp->suivant;
    }
    
}



void fusionH(BiblioH *b1, BiblioH *b2){

    for(int i=0; i<b2->m; i++){
        LivreH *l = b2->T[i];

        while(l){
            insererH(b1, l->num, l->titre, l->auteur);
            l=l->suivant;
        }
    }

    liberer_biblioH(b2);

}



LivreH *dupliquesH(BiblioH *b){

    LivreH *res = NULL;
    for(int i=0; i<b->m; i++){
        LivreH *tmp = b->T[i];
        while(tmp){
            LivreH *tmp2 = tmp->suivant;
            int d=0; //indique si le livreH dupliqué est déja dans 'res'
            while(tmp2){
                if(!strcmp(tmp2->titre,tmp->titre) && !strcmp(tmp2->auteur,tmp->auteur) ){
                    if(!d){ //on doit ajouter tout les exemplaires!!
                        LivreH* l = creer_livreH(tmp->num,tmp->titre,tmp->auteur);
                        l->suivant = res;
                        res = l;
                        supprimer_livreH(b, tmp->num, tmp->titre, tmp->auteur);
                        d++;
                    }

                    LivreH* l2 = creer_livreH(tmp2->num,tmp2->titre,tmp2->auteur);
                    l2->suivant = res;
                    res = l2;
                    supprimer_livreH(b, tmp2->num, tmp2->titre, tmp2->auteur);
                }
                tmp2=tmp2->suivant;
            }
            tmp=tmp->suivant;
        }
    }
    return res;
}
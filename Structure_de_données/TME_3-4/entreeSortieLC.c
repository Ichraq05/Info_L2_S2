#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

Biblio* charger_n_entrees(char* nomfic, int n){
    Biblio* b = creer_biblio();

    char ch[1024];

    for(int i=0; i<n; i++){
        fscanf((FILE*)*nomfic, " %1023s", ch);
    }
}

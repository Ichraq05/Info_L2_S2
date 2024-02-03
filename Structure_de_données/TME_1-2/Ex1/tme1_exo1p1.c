#include<stdio.h>
#include<stdlib.h>

//gcc -ggdb -o tme1_exo1p1 tme1_exo1p1.c
//gdb tme1_exo1p1

//gcc -o tme1_exo1p1 tme1_exo1p1.c

const static int len = 10;

int main(void) {
    int *tab;
    unsigned int i;

    //printf("[");

    tab = (int*)malloc(len*sizeof(int));

    for (i=len-1; i>=0; i--) {
        tab[i] = i;
        //printf("%d, ", tab[i]);
    }

    //printf("%d]\n", tab[0]);

    free(tab);
    return 0;
}


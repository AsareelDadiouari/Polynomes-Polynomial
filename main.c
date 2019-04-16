#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main()
{
    Polynome poly;
    Polynome poly2;
    initialisation(&poly2);
    initialisation(&poly);

    insertion(&poly, 7,1);
    insertion(&poly, 7,1);
    insertion(&poly2, 20,1);
    insertion(&poly2, 10,7);
    insertion(&poly2, 10,2);

    printf("Polynome 1 :\n");
    affichage_decroissant(poly);

    printf("Polynome 2 :\n");
    affichage_decroissant(poly2);

    printf("Somme :\n");
    affichage_decroissant(somme(poly, poly2));


    return 0;
}

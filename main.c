#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main()
{

    Polynome poly;
    Polynome poly2;
    initialisation(&poly2);
    initialisation(&poly);

    insertion(&poly, 5, 1);
    insertion(&poly, 10, 2);
    insertion(&poly, 1, 1);

    affichage_decroissant(poly);

    insertion(&poly2, 10, 8);
    insertion(&poly2, 1, 9);
    insertion(&poly2, 2, 10);

    affichage_decroissant(poly2);

    affichage_decroissant(somme(poly, poly2));


    /*insertion(&poly2, 2,2);
    insertion(&poly2, 4,2);

    affichage_decroissant(poly2);

    affichage_decroissant(somme(poly, poly2));*/

    /*Polynome poly;
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
    affichage_decroissant(somme(poly, poly2));*/

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "header/header.h"

int main()
{

    Polynome *poly = initialisation();
    Polynome *poly2 = initialisation();

    insertion(poly, 2, 2);
    insertion(poly, 4, 1);
    affichageDec(poly);

    insertion(poly2, 1, 1);
    insertion(poly2, 5, 10);
    affichageDec(poly2);

    affichageDec(somme(poly, poly2));
    affichageDec(soustraction(poly, poly2));

    system("pause");
    return 0;
}

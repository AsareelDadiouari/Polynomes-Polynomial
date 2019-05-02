#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "header/header.h"

int main()
{
    float coef;
    int deg;
    int choix, choixPoly, entierImg;
    int i = 0; // indice de la matrice
    int t = 0; // taille de la matrice
    Polynome **matPoly;
    matPoly = (Polynome **)malloc(sizeof(Polynome *));

    matPoly[i] = initialisation();

    do
    {
        menu();
        printf("Entrer coef=0 et deg =0 pour arreter\n");
        printf("----------------------------------------------\n");

        affichMat(matPoly, i);

        printf("Creation d' un polynome :\n");
        printf("Enter un coefficient :");
        scanf("%f", &coef);

        printf("Enter un degree :");
        scanf("%d", &deg);

        insertion(matPoly[i], coef, deg);
        system("cls");

    } while (coef != 0 || deg != 0);

    do
    {
        menu();

        affichMat(matPoly, i);
        if (i == 0 || i == -1)
            menu2();
        else
            menu3();
        printf("choix :");
        scanf("%d", &choix);
        fflush(stdin);

        switch (choix)
        {
        case 0:
            printf("Fin du programme\n");
            break;

        case 1:
            i++;
            matPoly[i] = initialisation();

            if (i == 0 && i == -1)
                menu2();
            else
                menu3();
            system("cls");

            printf("Creation d' un polynome :\n");
            do
            {
                menu();
                affichMat(matPoly, i);

                printf("Enter un coefficient :");
                scanf("%f", &coef);

                printf("Enter un degree :");
                scanf("%d", &deg);

                insertion(matPoly[i], coef, deg);
                system("cls");

            } while (coef != 0 || deg != 0);

            break;
        case 2:
            if (i == 0 && matPoly[i]->taille != 0)
            {
                system("cls");
                menu();
                affichMat(matPoly, i);
                printf("Entrer le degree du monome a supprimer :");
                scanf("%d", &deg);

                /*----Gestion de la mémoire apres suppression------*/
                if (degExiste(matPoly[i], deg) == 1 && matPoly[i]->taille == 1)
                {
                    supprimer(matPoly[i], deg);
                    destruction(matPoly[i]);
                    i = -1;
                }
                else
                    supprimer(matPoly[i], deg);

                system("cls");
            }
            else
            {
                system("cls");
                menu();

                affichMat(matPoly, i);
                printf("Entrer le numero du polynome :");
                scanf("%d", &choixPoly);

                if (choixPoly <= i + 1 && choixPoly != 0)
                {
                    printf("Entrer le degree du monome a supprimer :");
                    scanf("%d", &deg);

                    if (degExiste(matPoly[choixPoly - 1], deg) == 1 && matPoly[choixPoly - 1]->taille == 1)
                    {
                        supprimer(matPoly[choixPoly - 1], deg);
                        matPoly[choixPoly - 1] = matPoly[choixPoly];
                        i--;
                    }
                    else
                        supprimer(matPoly[choixPoly - 1], deg);
                }

                system("cls");
            }

            break;
        case 3:
            if (i == 0)
            {
                printf("Derrivee Polynome =\n");
                affichageDec(derivee(matPoly[i]));
                system("pause");
                system("cls");
            }
            else
            {
                printf("Entrer le numero du polynome :");
                scanf("%d", &choixPoly);
                if (choixPoly <= i + 1)
                {
                    printf("Derrivee Polynome %d =\n", choixPoly);
                    affichageDec(derivee(matPoly[choixPoly - 1]));
                    system("pause");
                }
                system("cls");
            }

            break;
        case 4:
            if (i == 0)
            {
                printf("Primitive Polynome =\n");
                affichageDec(primitive(matPoly[i]));
                system("pause");
                system("cls");
            }
            else
            {
                printf("Entrer le numero du polynome :");
                scanf("%d", &choixPoly);
                if (choixPoly <= i + 1)
                {
                    printf("Primitive Polynome %d =\n", choixPoly);
                    affichageDec(primitive(matPoly[choixPoly - 1]));
                    system("pause");
                }
                system("cls");
            }

            break;

        case 5:
            if (i == 0)
            {
                printf("Entrer l'entier : =");
                scanf("%d", &entierImg);

                printf("L'image de %d par ce pomynome est : %.2f", entierImg, image(matPoly[i], entierImg));
                system("pause");
                system("cls");
            }
            else
            {
                printf("Entrer le numero du polynome :");
                scanf("%d", &choixPoly);
                if (choixPoly <= i + 1)
                {
                    printf("Entrer l'entier : =");
                    scanf("%d", &entierImg);

                    printf("L'image de %d par ce pomynome est : %.2f", entierImg, image(matPoly[choixPoly - 1], entierImg));
                    system("pause");
                    system("cls");
                }
                system("cls");
            }

            break;

        case 6:
            if (i == 0)
            {

                printf("L'intégrale est : %f", integrale(matPoly[i], -2, 2));
                system("pause");
                system("cls");
            }
            else
            {
                printf("Entrer le numero du polynome :");
                scanf("%d", &choixPoly);
                if (choixPoly <= i + 1)
                {
                    printf("L'integrale est : %f", integrale(matPoly[i], -2, 2));
                    system("pause");
                    system("cls");
                }
                system("cls");
            }

            break;

        default:
            printf("Touche inconnue... Recommencez\n");
            system("pause");
            system("cls");
            break;
        }
    } while (choix != 0);

    while (i >= 0)
    {
        destruction(matPoly[i]);
        i--;
    }

    free(*matPoly);

    system("pause");
    return 0;
}

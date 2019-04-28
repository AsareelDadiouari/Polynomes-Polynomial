#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "../header/header.h"

enum TYPE_OPERATION toCheckSub; // varriable globale utilsée pour vérifier l'opérationn
/*---------------------------------------------------*/

void insertion(Polynome *poly, float coef, int deg)
{
    if (poly->taille == 0)
        insertionAvide(poly, coef, deg);
    else if (poly->taille == 1)
    {
        if (poly->first->deg > deg && nbrDeg(poly, deg) == 0 && toCheckSub == ADDITION)
            push_last(poly, coef, deg);
        else if (poly->first->deg < deg && nbrDeg(poly, deg) == 0 && toCheckSub == ADDITION)
            push_first(poly, coef, deg);
        else
        {
            Monome *ptr;

            if (toCheckSub == ADDITION)
            {
                for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
                {
                    if (ptr->deg == deg)
                        ptr->coef += coef;
                }
            }
            else if (toCheckSub == SOUSTRACTION)
            {
                for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
                {
                    if (ptr->deg == deg)
                        ptr->coef -= coef;
                }
            }
        }
    }
    else
    {
        if (nbrDeg(poly, deg) == 0 && toCheckSub == ADDITION)
            push_position(poly, coef, deg);
        else
        {
            Monome *ptr;

            if (toCheckSub == ADDITION)
            {
                for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
                {
                    if (ptr->deg == deg)
                        ptr->coef += coef;
                }
            }
            else if (toCheckSub == SOUSTRACTION)
            {
                for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
                {
                    if (ptr->deg == deg)
                        ptr->coef -= coef;
                }
            }
        }
    }
}

/*---------------------------------------------------*/

void supprimer(Polynome *poly, float deg)
{
    Monome *ptr, *temp;

    if (poly->first->deg != deg && poly->taille == 1)
        return;

    for (ptr = poly->first; ptr != NULL && ptr->deg != deg; ptr = ptr->next)
        ;

    if (ptr == NULL)
        return;

    temp = ptr;

    if (poly->taille == 1)
    {
        free(ptr);
        free(temp);
        poly->first = NULL;
        poly->last = NULL;
        poly->taille = 0;
    }
    else if (temp == poly->first && ptr->deg == deg)
    {
        pop_first(poly);
    }
    else if (temp == poly->last && ptr->deg == deg)
    {
        pop_last(poly);
    }
    else if (temp->next != NULL)
    {
        temp = temp->next;
        ptr->prec->next = temp;
        temp->prec = ptr->prec;
        free(ptr);
        if (poly->taille != 0)
            poly->taille--;
    }
}

/*---------------------------------------------------*/
/* NOTE : les coeffcients et les degree ne doivent pas deppasée 3 caractere 
sinon il y aura un défaut d'affichage.
*/
void affichageDec(const Polynome *poly)
{
    const Monome *ptr;

    if (poly->taille == 0)
    {
        printf("Polynome Vide\n");
    }
    else
    {
        int j = 0, k = 0, cmp;

        for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
        {
            while (j <= nbrCarac(ptr->coef))
            {
                printf(" ");
                j++;
            }
            j = 0;

            if (ptr->deg != 1 && ptr->deg != 0 && ptr->coef != 0)
            {
                printf("%d\t", ptr->deg);
            }
            else if (ptr->deg == 0)
                printf(" ");

            for (cmp = 0; cmp < 100; cmp++)
            {
                if (nbrCarac(ptr->coef == cmp))
                {
                    while (k <= nbrCarac(ptr->coef) + cmp + 5)
                    {
                        printf(" ");
                        k++;
                    }
                }
                break;
            }
            k = 0;
        }
        printf("\n");

        for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
        {
            if (ptr->deg != 0 && ptr->coef > 1)
                printf("%.0fX\t", ptr->coef);
            else if (ptr->deg != 0 && ptr->coef < 0)
                printf("(%.0fX)\t", ptr->coef);
            else if (ptr->deg == 0 && ptr->coef == -1)
                printf("(%.0f)\t", ptr->coef);
            else if (ptr->deg == 0 && ptr->coef == 1)
                printf("%.0f\t", ptr->coef);
            else if (ptr->coef == 1)
                printf("X\t");
            else if (ptr->coef != 0 && ptr->deg == 0)
                printf("%.0f\t", ptr->coef);

            if (ptr->next != NULL && ptr->next->deg != 0 && ptr->next->coef != 0)
                printf("+");

            if (ptr->next != NULL && ptr->next->deg == 0 && ptr->next->coef != 0)
                printf("+");

            printf("\t");
        }
        printf("\n");
    }
}

/*---------------------------------------------------*/
void affichageCroi(const Polynome *poly) //En cours
{
    const Monome *ptr;
    printf("\n");
    for (ptr = poly->last; ptr != NULL; ptr = ptr->prec)
    {
        if (ptr->deg != 0 && ptr->coef > 1)
            printf("%.0fX\t", ptr->coef);
        else if (ptr->deg != 0 && ptr->coef < 0)
            printf("(%.0fX)\t", ptr->coef);
        else if (ptr->deg == 0 && ptr->coef == -1)
            printf("(%.0f)\t", ptr->coef);
        else if (ptr->deg == 0 && ptr->coef == 1)
            printf("%.0f\t", ptr->coef);
        else if (ptr->coef == 1)
            printf("X\t");
        else if (ptr->coef != 0 && ptr->deg == 0)
            printf("%.0f\t", ptr->coef);

        if (ptr->prec != NULL && ptr->prec->deg != 0 && ptr->prec->coef != 0)
            printf("+");

        if (ptr->prec != NULL && ptr->prec->deg == 0 && ptr->prec->coef != 0)
            printf("+");

        printf("\t");
    }
    printf("\n");
}

/*---------------------------------------------------*/
void destruction(Polynome *poly)
{
    Monome *temp, *ptr;

    ptr = poly->first;

    while (ptr != NULL)
    {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
        poly->taille--;
    }
}
/*---------------------------------------------------*/
Polynome *multiplication_scalaire(const Polynome *poly, int scal)
{
    const Monome *temp;
    Polynome *polynome = initialisation();

    for (temp = poly->first; temp != NULL; temp = temp->next)
    {
        insertion(polynome, temp->coef * scal, temp->deg);
    }

    return polynome;
}

/*---------------------------------------------------*/
Polynome *multiplication_monome(const Polynome *poly, float coef, int deg)
{
    const Monome *temp;
    Polynome *polynome = initialisation();

    for (temp = poly->first; temp != NULL; temp = temp->next)
    {
        insertion(polynome, temp->coef * coef, temp->deg + deg);
    }
    return polynome;
}
/*---------------------------------------------------*/
Polynome *somme(const Polynome *poly1, const Polynome *poly2)
{

    Polynome *polynome = initialisation();

    const Monome *ptr;

    toCheckSub = ADDITION;

    for (ptr = poly1->first; ptr != NULL; ptr = ptr->next)
    {
        insertion(polynome, ptr->coef, ptr->deg);
    }

    for (ptr = poly2->first; ptr != NULL; ptr = ptr->next)
    {
        insertion(polynome, ptr->coef, ptr->deg);
    }

    return polynome;
}
/*---------------------------------------------------*/
Polynome *soustraction(const Polynome *poly1, const Polynome *poly2)
{
    Polynome *polynome = initialisation();

    Monome *ptr;
    toCheckSub = SOUSTRACTION;

    for (ptr = poly1->first; ptr != NULL; ptr = ptr->next)
    {
        insertion(polynome, ptr->coef, ptr->deg);
    }

    for (ptr = poly2->first; ptr != NULL; ptr = ptr->next)
    {
        insertion(polynome, ptr->coef, ptr->deg);
    }

    return polynome;
}
/*---------------------------------------------------*/
Polynome *produit(const Polynome *poly1, const Polynome *poly2)
{
    Polynome *polynome = initialisation();
    const Monome *ptr, *qtr;
    float prodCoef;
    int prodDeg;

    for (ptr = poly1->first; ptr != NULL; ptr = ptr->next)
    {
        for (qtr = poly2->first; qtr != NULL; qtr = qtr->next)
        {
            prodCoef = ptr->coef * qtr->coef;
            prodDeg = ptr->deg + qtr->deg;
            insertion(polynome, prodCoef, prodDeg);
        }
    }

    return polynome;
}
/*---------------------------------------------------*/
Polynome *derivee(const Polynome *poly)
{
    Polynome *polynome = initialisation();
    const Monome *ptr;
    float derCoef;
    int derDeg;

    for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
    {
        derCoef = ptr->coef * ptr->deg;
        derDeg = ptr->deg - 1;
        insertion(polynome, derCoef, derDeg);
    }

    return polynome;
}
/*---------------------------------------------------*/
Polynome *primitive(const Polynome *poly)
{
    Polynome *polynome = initialisation();
    const Monome *ptr;
    float priCoef;
    int priDeg;

    for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
    {
        priCoef = ptr->coef * (1 / (ptr->deg + 1));
        priDeg = ptr->deg + 1;
        insertion(polynome, priCoef, priDeg);
    }

    return polynome;
}
/*---------------------------------------------------*/

float image(const Polynome *poly, int entier)
{
    float image;
    const Monome *ptr;

    for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
    {
        image += ptr->coef * (pow(entier, ptr->deg));
    }
    return image;
}

/*---------------------------------------------------*/
float integrale(const Polynome *poly, int lim1, int lim2)
{
    
}
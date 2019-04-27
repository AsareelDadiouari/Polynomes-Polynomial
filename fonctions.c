#include <stdio.h>
#include <stdlib.h>
#include "../header/header.h"

int toCheckSub;
/*---------------------------------------------------*/

void insertion(Polynome *poly, float coef, int deg)
{
    if (poly->taille == 0)
        insertionAvide(poly, coef, deg);
    else if (poly->taille == 1)
    {
        if (poly->first->deg > deg && nbrDeg(poly, deg) == 0)
            push_last(poly, coef, deg);
        else if (poly->first->deg < deg && nbrDeg(poly, deg) == 0)
            push_first(poly, coef, deg);
        else
        {
            Monome *ptr;

            if (toCheckSub == 0)
            {
                for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
                {
                    if (ptr->deg == deg)
                        ptr->coef += coef;
                }
            }
            else
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
        if (nbrDeg(poly, deg) == 0)
            push_position(poly, coef, deg);
        else
        {
            Monome *ptr;

            if (toCheckSub == 0)
            {
                for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
                {
                    if (ptr->deg == deg)
                        ptr->coef += coef;
                }
            }
            else
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

void affichageDec(const Polynome *poly)
{
    const Monome *ptr;

    if (poly->taille == 0)
    {
        printf("Vide\n");
    }
    else
    {
        for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
            printf("[%p][%.0f][%d][%p]->", ptr->prec, ptr->coef, ptr->deg, ptr->next);
        printf("\n");
    }
}

/*---------------------------------------------------*/
void affichageCroi(const Polynome *poly) //En cours
{
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
void multiplication_scalaire(Polynome *poly, int scal)
{
    Monome *temp;

    for (temp = poly->first; temp != NULL; temp = temp->next)
    {
        temp->coef *= scal;
    }
}

/*---------------------------------------------------*/
void multiplication_monome(Polynome *poly, float coef, int deg)
{
    Monome *temp;

    for (temp = poly->first; temp != NULL; temp = temp->next)
    {
        temp->coef *= coef;
        temp->deg += deg;
    }
}
/*---------------------------------------------------*/
Polynome *somme(const Polynome *poly1, const Polynome *poly2)
{

    Polynome *polynome = initialisation();

    const Monome *ptr;

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
    toCheckSub = 1;

    for (ptr = poly1->first; ptr != NULL; ptr = ptr->next)
    {
        insertion(polynome, ptr->coef, ptr->deg);
    }

    for (ptr = poly2->first; ptr != NULL; ptr = ptr->next)
    {
        insertion(polynome, ptr->coef, ptr->deg);
    }

    toCheckSub = 0;

    return polynome;
}
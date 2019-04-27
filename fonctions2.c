#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/header.h"

/*---------------------------------------------------*/

Polynome *initialisation()
{
    Polynome *poly = (Polynome *)malloc(sizeof(Polynome));

    poly->first = NULL;
    poly->last = NULL;
    poly->taille = 0;

    return poly;
}

/*---------------------------------------------------*/
void insertionAvide(Polynome *poly, float coef, int deg)
{
    Monome *mono = (Monome *)malloc(sizeof(Monome));

    if (mono == NULL)
        printf("Erreur d'allocation dynamique\n");
    else
    {
        mono->coef = coef;
        mono->deg = deg;
        mono->next = NULL;
        mono->prec = NULL;

        poly->first = mono;
        poly->last = mono;
        poly->taille++;
    }
}

/*---------------------------------------------------*/
void push_first(Polynome *poly, float coef, int deg)
{
    Monome *mono = (Monome *)malloc(sizeof(Monome));

    if (mono == NULL)
        printf("Erreur d'allocation dynamique\n");
    else
    {
        mono->coef = coef;
        mono->deg = deg;
        mono->next = poly->first;
        mono->prec = NULL;

        poly->first->prec = mono;
        poly->first = mono;
        poly->taille++;
    }
}
/*---------------------------------------------------*/

void push_last(Polynome *poly, float coef, int deg)
{
    Monome *mono = (Monome *)malloc(sizeof(Monome));

    if (mono == NULL)
        printf("Erreur d'allocation dynamique\n");
    else
    {
        mono->coef = coef;
        mono->deg = deg;
        mono->next = NULL;
        mono->prec = poly->last;

        poly->last->next = mono;
        poly->last = mono;
        poly->taille++;
    }
}
/*---------------------------------------------------*/

void push_position(Polynome *poly, float coef, int deg)
{
    Monome *mono = (Monome *)malloc(sizeof(Monome));
    Monome *ptr, *qtr;
    int pos, i = 1;

    if (mono == NULL)
        printf("Erreur d'allocation dynamique\n");
    else
    {
        if (poly->first->deg < deg)
        {
            push_first(poly, coef, deg);
            return;
        }
        else if (poly->last->deg > deg)
        {
            push_last(poly, coef, deg);
            return;
        }

        for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
        {

            if (ptr->deg < deg)
            {
                pos = i;
                break;
            }

            i++;
        }

        for (ptr = poly->first, i = 1; i < pos - 1; i++, ptr = ptr->next)
        {
        };

        for (qtr = poly->last, i = poly->taille + 1; i > pos + 1; i--, qtr = qtr->prec)
        {
        };

        mono->coef = coef;
        mono->deg = deg;
        mono->next = qtr;
        mono->prec = ptr;

        ptr->next = mono;
        qtr->prec = mono;

        poly->taille++;
    }
}
/*---------------------------------------------------*/
void pop_first(Polynome *poly)
{
    Monome *ptr;

    if (poly->first == NULL)
    {
        printf("probleme d'allocation de memoire\n");
    }
    else
    {
        ptr = poly->first;
        poly->first = poly->first->next;
        poly->first->prec = NULL;
        free(ptr);
        poly->taille--;
    }
}
/*---------------------------------------------------*/
void pop_last(Polynome *poly)
{
    Monome *ptr;

    if (poly->last == NULL)
    {
        printf("probleme d'allocation de memoire\n");
    }
    else
    {
        ptr = poly->last;
        poly->last = poly->last->prec;
        poly->last->next = NULL;
        free(ptr);
        poly->taille--;
    }
}
/*---------------------------------------------------*/
void sommer_monome(Polynome *poly, float coef, int deg)
{
    Monome *ptr;

    for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->deg == deg)
            ptr->coef += coef;
    }
}
/*---------------------------------------------------*/
int nbrDeg(Polynome *poly, int deg)
{
    Monome *ptr;
    int i = 0;

    for (ptr = poly->first; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->deg == deg)
            i++;
    }

    return i;
}
/*---------------------------------------------------*/

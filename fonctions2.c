#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/*-------------------------------------------------*/
void initialisation(Polynome* poly)
{
    poly->first=NULL;
    poly->last=NULL;
    poly->taille=0;
}
/*-------------------------------------------------*/
int compare_float(Polynome* poly,float val1)
{
    Monome* ptr;
    int i=1;

    for(ptr=poly->first; ptr!=NULL; ptr=ptr->next)
    {
        if(ptr->deg<val1)
            return i;
        i++;
    }

    return i;
}

/*-------------------------------------------------*/
void insertionAvide(Polynome* poly, float coef, float deg)
{
    Monome *mono=malloc(sizeof(*mono));

    if(mono==NULL)
    {
        fprintf(stderr, "Erreur d'allocation memoire\n");
        return;
    }

    mono->coef=coef;
    mono->deg=deg;
    mono->next=NULL;
    mono->prec=NULL;
    poly->first=mono;
    poly->last=mono;
    poly->taille++;
}
/*-------------------------------------------------*/
void push_first(Polynome* poly, float coef, float deg)
{
    Monome *mono=malloc(sizeof(*mono));
    Monome *ptr;

    if(mono==NULL)
    {
        fprintf(stderr, "Erreur d'allocation memoire\n");
        return;
    }

    ptr=poly->first;

    mono->coef=coef;
    mono->deg=deg;
    mono->next=poly->first;
    mono->prec=NULL;

    ptr->prec=mono;

    poly->first=mono;
    poly->taille++;
}
/*-------------------------------------------------*/
void push_last(Polynome* poly, float coef, float deg)
{

    Monome *mono=malloc(sizeof(*mono));
    Monome* ptr;

    if(mono==NULL)
    {
        fprintf(stderr, "Erreur d'allocation memoire\n");
        return;
    }

    ptr=poly->last;

    mono->coef=coef;
    mono->deg=deg;
    mono->next=NULL;
    mono->prec=poly->last;

    ptr->next=mono;
    poly->last=mono;
    poly->taille++;

}
/*-------------------------------------------------*/
void push_position(Polynome* poly, float coef, float deg, int pos)
{
    Monome* mono=malloc(sizeof(*mono));
    Monome *ptr, *qtr;
    int i;

    if(mono==NULL)
    {
        fprintf(stderr, "Erreur d'allocation memoire\n");
        return;
    }

    if(compare_float(poly, deg)==1)
    {
        push_first(poly, coef, deg);

    }
    else if(compare_float(poly, deg)-1==poly->taille)
    {
        push_last(poly, coef, deg);

    }
    else
    {
        mono->coef=coef;
        mono->deg=deg;

        for(ptr=poly->first,i=1; i<pos-1; i++,ptr=ptr->next);
        for(qtr=poly->last,i=poly->taille+1; i>pos+1; i--,qtr=qtr->prec);

        mono->next=qtr;
        mono->prec=ptr;

        ptr->next=mono;
        qtr->prec=mono;

        poly->taille++;
    }
}
/*-------------------------------------------------*/
void pop_first(Polynome* poly)
{
    if(poly->first==NULL || poly->last==NULL)
    {
        printf("Il n'y a rien a supprimer\n");
        return;
    }

    if(poly->taille>1)
    {
        Monome* ptr=poly->first->next;
        free(poly->first);
        ptr->prec=NULL;
        poly->first=ptr;
        poly->taille--;
    }
    else
        initialisation(poly);

}
/*-------------------------------------------------*/
void pop_last(Polynome* poly)
{
    if(poly->first==NULL && poly->last==NULL)
    {
        printf("Il n'y a rien a supprimer\n");
        return;
    }

    if(poly->taille>1)
    {
        Monome* ptr=poly->last->prec;
        free(poly->last);
        ptr->next=NULL;
        poly->last=ptr;
        poly->taille--;
    }
    else
        initialisation(poly);
}
/*-------------------------------------------------*/
void pop_position(Polynome* poly, int pos)
{
    if(poly->first==NULL && poly->last==NULL)
    {
        return;
    }

    int i;

    if(poly->taille==1 || pos==1)
    {
        pop_first(poly);
        return;
    }

    if(pos>=poly->taille)
        pop_last(poly);
    else if(pos<=0)
        pop_first(poly);
    else
    {
        Monome* ptr=poly->first;
        Monome* qtr;

        for(i=1; i<pos-1 && ptr->next!=NULL; i++)
        {
            ptr=ptr->next;
        }

        if(ptr->next->next!=NULL && pos!=poly->taille-1)
        {
            qtr=ptr->next;
            free(qtr);
            ptr->next=ptr->next->next;
            ptr->next->next->prec=ptr;
            poly->taille--;
        }
        else
        {
            qtr=ptr->next;
            free(qtr);
            ptr->next=ptr->next->next;
            ptr->next->prec=ptr;
            poly->taille--;
        }
    }
}
/*-------------------------------------------------*/
int nbr_carac(int nbr)
{
    int i=0;

    do
    {
        nbr=nbr/10;
        i++;
    }
    while(nbr!=0);

    return i;
}
/*-------------------------------------------------*/
Polynome copie(Polynome poly)
{
    Monome *qtr;
    Polynome polynome;
    initialisation(&polynome);

    for(qtr=poly.first; qtr!=NULL; qtr=qtr->next)
        insertion(&polynome, qtr->coef, qtr->deg);

    return polynome;
}
/*-------------------------------------------------*/
Polynome concat(Polynome poly1, Polynome poly2)
{
    Monome* ptr;
    Polynome polynome;

    if(poly1.first!=NULL)
    {
        for(ptr=poly2.first; ptr!=NULL; ptr=ptr->next)
            insertion(&poly1, ptr->coef, ptr->deg);

        polynome=copie(poly1);
    }
    else
        polynome=copie(poly2);

    return polynome;
}
/*-------------------------------------------------*/
int retourneNbrMemeDegre(Polynome poly, float deg)
{
    Monome *ptr, *qtr;
    int i=0;

    for(ptr=poly.first; ptr!=NULL; ptr=ptr->next)
    {
        for(qtr=ptr->next; qtr!=NULL; qtr=qtr->next)
        {
            if(ptr->deg==qtr->deg)
                i++;
        }
    }

    return i;
}
/*-------------------------------------------------*/
int retNbrRPT(Polynome poly)
{
    Monome* ptr, *qtr;

    for(ptr=poly.first, qtr=ptr->next; qtr!=NULL; ptr=ptr->next, qtr=ptr->next)
    {
        if(ptr->deg==qtr->deg)
            return 1;
    }
    return 0;
}
/*-------------------------------------------------*/
Monome* retPos(Polynome poly, float coef, float deg)
{
    Monome* ptr;
    Monome* adr;

    for(ptr=poly.first; ptr!=NULL; ptr=ptr->next)
    {
        if(ptr->coef==coef && ptr->deg==deg)
        {
            adr=ptr;
            return adr;
        }
    }

    return NULL;
}
/*-------------------------------------------------*/
void afficheAdr(Polynome poly)
{
    Monome* ptr;

    for(ptr=poly.first; ptr!=NULL; ptr=ptr->next)
    {
        printf("[%p] %.0f [%p]   |  ", ptr->prec, ptr->coef,ptr->next);
    }
    printf("\n");
}
/*-------------------------------------------------*/

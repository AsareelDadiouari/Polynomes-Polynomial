#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/*-------------------------------------------------*/
void insertion(Polynome* poly, float coef, float deg)
{
    if(coef==0 && deg==0)
        return;
    else if(coef==0 && deg!=0)
        return;

    if(poly->first==NULL || poly->last==NULL)
    {
        insertionAvide(poly, coef, deg);
        return;
    }

    if(poly->taille==1)
    {
        if(poly->first->deg>deg)
            push_last(poly, coef, deg);
        else
            push_first(poly, coef, deg);
        return;
    }
    push_position(poly, coef, deg, compare_float(poly, deg));
}

/*-------------------------------------------------*/
void suppression(Polynome* poly, float deg)
{
    if(poly->first==NULL || poly->last==NULL)
    {
        printf("Il n'ya rien a supprimer\n");
        return;
    }

    Monome* ptr;
    int pos=1, check=0;

    if(poly->taille==1)
        pop_last(poly);

    for(ptr=poly->first; ptr!=NULL; ptr=ptr->next)
    {
        if(ptr->deg==deg)
        {
            check=1;
            pop_position(poly, pos);
        }
        if(check!=1)
            pos++;
    }
}

/*-------------------------------------------------*/
void affichage_decroissant(Polynome poly)
{
    if(poly.first==NULL || poly.last==NULL || poly.taille==0)
    {
        printf("Aucun monome dans le polynome\n");
        return;
    }

    printf("Affichage Decroissant\n");
    int **ptr1=malloc(sizeof(**ptr1)*30);
    int i, j=0;
    Monome* ptr;

    for(ptr=poly.first, i=0; ptr!=NULL; i++,ptr=ptr->next)
    {
        *(ptr1+i)=malloc(sizeof(*ptr1)*2);
        *(*(ptr1+i))=ptr->coef;
        *(*(ptr1+i)+1)=ptr->deg;
    }

    for(ptr=poly.first, i=0; ptr!=NULL; i++,ptr=ptr->next)
    {
        while(j<=nbr_carac(ptr->coef)+1)
        {
            if(j==nbr_carac(ptr->coef)+1 && ptr->coef<0)
                printf("   ");

            if(j<nbr_carac(ptr->coef)+1)
                printf(" ");
            j++;
        }

        if(ptr->deg!=1 && ptr->deg!=0 && ptr->coef!=0)
            printf("%d\t\t", *(*(ptr1+i)+1));
        else if(ptr->deg==0)
            printf(" ");


        j=0;
    }
    printf("\n");

    for(ptr=poly.first, i=0; ptr!=NULL; i++,ptr=ptr->next)
    {
        if(ptr->deg!=0 && ptr->coef>1)
            printf("%dX\t", *(*(ptr1+i)));
        else if(ptr->deg!=0 && ptr->coef<0)
            printf("(%dX)\t",*(*(ptr1+i)));
        else if(ptr->deg==0 && ptr->coef==-1)
            printf("(%d)\t", *(*(ptr1+i)));
        else if(ptr->deg==0 && ptr->coef==1)
            printf("%d\t", *(*(ptr1+i)));
        else if(ptr->coef==1)
            printf("X\t");
        else if(ptr->coef!=0 && ptr->deg==0)
            printf("%d\t", *(*(ptr1+i)));

        if(ptr->next!=NULL && ptr->next->deg!=0 && ptr->next->coef!=0)
            printf("+");

        if(ptr->next!=NULL && ptr->next->deg==0 && ptr->next->coef!=0)
            printf("+");

        printf("\t");
    }
    printf("\n");
}
/*-------------------------------------------------*/
void affichage_croissant(Polynome poly)
{
    if(poly.first==NULL || poly.last==NULL || poly.taille==0)
    {
        printf("Aucun monome dans le polynome\n");
        return;
    }

    printf("Affichage Croissant\n");
    int **ptr1=malloc(sizeof(**ptr1)*30);
    int i, j=0;
    Monome* ptr;

    for(ptr=poly.last, i=poly.taille; ptr!=NULL; i--,ptr=ptr->prec)
    {
        *(ptr1+i)=malloc(sizeof(*ptr1)*2);
        *(*(ptr1+i))=ptr->coef;
        *(*(ptr1+i)+1)=ptr->deg;
    }

    for(ptr=poly.last, i=poly.taille; ptr!=NULL; i--,ptr=ptr->prec)
    {
        while(j<=nbr_carac(ptr->coef)+1)
        {
            if(j==nbr_carac(ptr->coef)+1 && ptr->coef<0)
                printf("   ");

            if(j<nbr_carac(ptr->coef)+1)
                printf(" ");
            j++;
        }

        if(ptr->deg!=1 && ptr->deg!=0 && ptr->coef!=0)
            printf("%d\t\t", *(*(ptr1+i)+1));

        j=0;
    }
    printf("\n");

    for(ptr=poly.last, i=poly.taille; ptr!=NULL; i--,ptr=ptr->prec)
    {
        if(ptr->deg!=0 && ptr->coef>1)
            printf("%dX\t", *(*(ptr1+i)));
        else if(ptr->deg!=0 && ptr->coef<0)
            printf("(%dX)\t",*(*(ptr1+i)));
        else if(ptr->coef==1)
            printf("X\t");
        else if(ptr->coef!=0 && ptr->deg==0)
            printf("%d\t", *(*(ptr1+i)));

        if(ptr->prec!=NULL && ptr->prec->deg!=0 && ptr->prec->coef!=0)
            printf("+");

        if(ptr->prec!=NULL && ptr->prec->deg==0 && ptr->prec->coef!=0)
            printf("+");

        printf("\t");

    }
    printf("\n");
}
/*-------------------------------------------------*/
void destruction(Polynome* poly)
{
    Monome* ptr;

    ptr=poly->first;

    while(ptr!=NULL)
    {
        pop_first(poly);
        ptr=ptr->next;
    }
}
/*-------------------------------------------------*/
void multiplication_scalaire(Polynome* poly, int scal)
{
    if(poly->first==NULL || poly->last==NULL || poly->taille==0)
    {
        printf("Aucun monome dans le polynome\n");
        return;
    }

    Monome* ptr;

    for(ptr=poly->first; ptr!=NULL; ptr=ptr->next)
    {
        ptr->coef=scal*ptr->coef;
    }
}
/*-------------------------------------------------*/
void multiplication_monome(Polynome* poly, float coef, float deg)
{
    if(poly->first==NULL || poly->last==NULL || poly->taille==0)
    {
        printf("Aucun monome dans le polynome\n");
        return;
    }

    Monome* ptr;

    for(ptr=poly->first; ptr!=NULL; ptr=ptr->next)
    {
        ptr->coef=coef*ptr->coef;
        ptr->deg=deg+ptr->deg;
    }
}
/*-------------------------------------------------*/
Polynome somme(Polynome poly1,Polynome poly2)
{
    Polynome polynome;
    initialisation(&polynome);

    int cmppos=1;//Compteur pour la dans le polynome
    int cmpverif=0;
    int taillepoly=poly1.taille+poly2.taille;
    float somcoef, degcoef;
    Monome* ptr, *qtr;

    polynome=concat(poly1, poly2);
    for(ptr=polynome.first; ptr->next!=NULL; ptr=ptr->next)
    {
        if(ptr->deg==ptr->next->deg)
            cmpverif++;
    }

    if(poly1.first==NULL || poly1.last==NULL)
    {
        printf("Aucun monome dans le polynome\n");
    }
    else
    {
        ptr=polynome.first;
        qtr=ptr->next;

        affichage_decroissant(polynome);

        if(cmpverif==taillepoly-1)
        {
            do
            {
                if(ptr->deg==qtr->deg)
                {
                    somcoef=ptr->coef+qtr->coef;
                    degcoef=ptr->deg;

                    pop_position(&polynome, cmppos);
                    pop_position(&polynome, cmppos);

                    if(somcoef!=0)
                    {
                        insertion(&polynome, somcoef, degcoef);
                        ptr=polynome.first;
                        qtr=ptr->next;
                        cmppos++;

                        if(ptr->next==NULL)
                            return polynome;
                    }
                }
                else
                {
                    somcoef=0;
                    degcoef=0;
                    cmppos=1;
                }

                if(qtr->next!=NULL)
                {
                    ptr=ptr->next;
                    qtr=ptr->next;
                }
            }
            while(qtr!=NULL);
        }
        else
        {
            do
            {
                if(ptr->deg==qtr->deg)
                {
                    somcoef=ptr->coef+qtr->coef;
                    degcoef=ptr->deg;

                    pop_position(&polynome, cmppos);
                    pop_position(&polynome, cmppos);

                    if(somcoef!=0)
                    {
                        insertion(&polynome, somcoef, degcoef);
                        affichage_decroissant(polynome);
                        printf("cmp=%d\n", cmppos);
                        if(polynome.taille==2)
                        {
                            ptr=polynome.first;
                            qtr=ptr->next;

                            if(ptr->deg!=qtr->deg)
                                return polynome;
                        }
                    }
                }
                else
                {
                    somcoef=0;
                    degcoef=0;
                }

                cmppos++;
                ptr=ptr->next;
                qtr=ptr->next;

            }
            while(qtr!=NULL);
        }
    }

    if(retNbrRPT(polynome)==1)
    {
        ptr=polynome.first;
        qtr=ptr->next;
        cmppos=0;

        do
        {
            if(ptr->deg==qtr->deg)
            {
                somcoef=ptr->coef+qtr->coef;
                degcoef=ptr->deg;

                pop_position(&polynome, cmppos);
                pop_position(&polynome, cmppos);

                if(somcoef!=0)
                {
                    insertion(&polynome, somcoef, degcoef);
                }
            }

            cmppos++;
            ptr=ptr->next;
            qtr=ptr->next;

        }
        while(qtr!=NULL);
    }
    return polynome;
}
/*-------------------------------------------------*/
Polynome multiplication_polynome(Polynome poly1, Polynome poly2)
{
    // Monome* ptr;
    Polynome polynome;
    initialisation(&polynome);
    polynome=copie(poly2);

    return polynome;
}


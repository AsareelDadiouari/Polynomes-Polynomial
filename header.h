#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

typedef struct Monome
{
    float coef, deg;
    struct Monome* next;
    struct Monome* prec;
}Monome;

typedef struct Polynome
{
    Monome* first, *last;
    int taille;
}Polynome;

/*********************Fonctions secondaires "fonctions2.c"*********/
int nbr_carac(int nbr); //Retourne le nombre d'entiers d'un nombre
void initialisation(Polynome* poly); // Initialise de la liste
int retourneNbrMemeDegre(Polynome poly, float deg);//Retourne le nombre de monome possedant le meme degree dans le polynome
int retNbrRPT(Polynome poly); // Retourne 1 s'il existe deux monomes de meme degree
void insertionAvide(Polynome* poly, float coef, float deg);// Insertion dans une liste vide
int compare_float(Polynome* poly ,float val1);// comparaison entre val1 et un element du polynome
void push_first(Polynome* poly, float coef, float deg);
void push_last(Polynome* poly, float coef, float );
void pop_first(Polynome* poly);
void pop_last(Polynome* poly);
void push_position(Polynome* poly, float coef, float, int pos);
void pop_position(Polynome* poly, int pos);
Polynome concat(Polynome poly1, Polynome poly2);
Polynome copie(Polynome poly);
Monome* retPos(Polynome poly, float coef, float deg);//retourne l'addresse de la position d'un monome rechercher
void popAdr(Polynome* poly, Monome* mono);
void afficheAdr(Polynome poly);//Affiche l'es adresse next et prec de tout les éléments de la liste

/********************Fonctions principales "fonctions.c"****/
void insertion(Polynome* poly, float coef, float deg); /**Stable**/
void suppression(Polynome* poly, float deg); /**Stable**/
void affichage_decroissant(Polynome poly); /**Instable**/ //Niveau d'instabilité : Moyen
void affichage_croissant(Polynome poly); /**Instable**/ //Niveau d'instabilité : Moyen
void destruction(Polynome* poly); /**Stable**/
void multiplication_scalaire(Polynome* poly, int scal); /**Stable**/
void multiplication_monome(Polynome* poly, float coef, float deg); /**Stable**/
Polynome somme(Polynome poly1, Polynome poly2); /**Instable**/
Polynome multiplication_polynome(Polynome poly1, Polynome poly2); /**Instable**/
/*******************************************************/

#endif // HEADER_H_INCLUDED

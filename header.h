#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

typedef struct Monome
{
    float coef;
    int deg;
    struct Monome *next;
    struct Monome *prec;
} Monome;

typedef struct Polynome
{
    Monome *first, *last;
    int taille;
} Polynome;

#endif // HEADER_H_INCLUDED

extern int toCheckSub; // varriable globale utilsée pour vérifier s'il s'agit d'une multiplication

//Fonctions secondaires
Polynome *initialisation();
void push_first(Polynome *poly, float coef, int deg);
void push_last(Polynome *poly, float coef, int deg);
void push_position(Polynome *poly, float coef, int deg);
void pop_first(Polynome *poly);
void pop_last(Polynome *poly);
void insertionAvide(Polynome *poly, float coef, int deg);
void sommer_monome(Polynome *poly, float coef, int deg);
int nbrDeg(Polynome *poly, int deg);

//Fontions proncipales
void insertion(Polynome *poly, float coef, int deg);             // Terminée
void supprimer(Polynome *poly, float deg);                       //Terminée
void affichageDec(const Polynome *poly);                         //En cours
void affichageCroi(const Polynome *poly);                        //En cours
void destruction(Polynome *poly);                                // Terminée
void multiplication_scalaire(Polynome *poly, int scal);          // Terminée
void multiplication_monome(Polynome *poly, float coef, int deg); // Terminée
Polynome *somme(const Polynome *poly1, const Polynome *poly2);   // Terminée
Polynome *soustraction(const Polynome *poly1, const Polynome *poly2);

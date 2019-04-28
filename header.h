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

enum TYPE_OPERATION
{
    ADDITION, //PAR DEFAUT
    SOUSTRACTION,
};

#endif // HEADER_H_INCLUDED

extern enum TYPE_OPERATION toCheckSub; // varriable globale utilsée pour vérifier l'opération

//Fonctions secondaires
Polynome *initialisation();                               // Terminée
void push_first(Polynome *poly, float coef, int deg);     // Terminée
void push_last(Polynome *poly, float coef, int deg);      // Terminée
void push_position(Polynome *poly, float coef, int deg);  // Terminée
void pop_first(Polynome *poly);                           // Terminée
void pop_last(Polynome *poly);                            // Terminée
void insertionAvide(Polynome *poly, float coef, int deg); // Terminée
void sommer_monome(Polynome *poly, float coef, int deg);  // Terminée
int nbrDeg(Polynome *poly, int deg);                      // Terminée
int nbrCarac(int nbr);                                    // Terminée
void afficheAdr(const Polynome *poly);                    // Terminée

//Fontions proncipales
void insertion(Polynome *poly, float coef, int deg);                        // Terminée
void supprimer(Polynome *poly, float deg);                                  // Terminée
void affichageDec(const Polynome *poly);                                    // Terminée Note: Marche modérement
void affichageCroi(const Polynome *poly);                                   // En cours
void destruction(Polynome *poly);                                           // Terminée
Polynome *multiplication_scalaire(const Polynome *poly, int scal);          // Terminée
Polynome *multiplication_monome(const Polynome *poly, float coef, int deg); // Terminée
Polynome *somme(const Polynome *poly1, const Polynome *poly2);              // Terminée
Polynome *soustraction(const Polynome *poly1, const Polynome *poly2);       // Terminée
Polynome *produit(const Polynome *poly1, const Polynome *poly2);            // Terminée
Polynome *derivee(const Polynome *poly);                                    // Terminée
Polynome *primitive(const Polynome *poly);                                  // Terminée
float image(const Polynome *poly, int entier);                              // Terminée
float integrale(const Polynome *poly, int lim1, int lim2);                  // En cours

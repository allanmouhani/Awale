#ifndef __JEU_HEADERFILE__
#define __JEU_HEADERFILE__

#include <stdio.h>
#include <stdlib.h>
#include "FichierConstante.h"
#include "Place.h"


/**
* Modélisation abstraite des objets(éléments) intervenants
* lors d'une séance de jeu.
* (structure du jeu)
*
* -le support du jeu (Tablier ou plateau):
*      Tableau[lignes][colonnes] =  Tableau[rangés][trous]
* -le résultat des joueurs : 
*      Tableau[resultat Jr1][resultat Jr2]
* -le type de jeu
*
* -pseudo du joueur 1
* -pseudo du joueur 2
* -l'état critique (famine) des joueurs (jr1 et jr2)
* -indice du joueur actif
*
* -la place (trou) visé 
* -la place (trou) occupé 
* -test si c'est le premier lancer 
*/
typedef struct jeu
{
    int typeJeu;
    
    int tablier[2][6]; 
    int resultat[2];

    char nomJ1[10];
    char nomJ2[10];
    BOOL etat_critique[2];
    int joueur;

    Place place_vise;
    Place place_occupe;
    BOOL lancer_intial;

} Jeu;

/**
 * elle permet de créer une nouvelle séance de jeu.
 *
 * Elle prend en paramètre :
 *      le type de jeu, le pseudo du joueur1, le pseudo du joueur2
 * Elle rétourne :
 *      le séance de jeu créer
 */
Jeu creer_jeu(int typeJeu, char *nomJ1 , char *nomJ2);

/**
 * elle permet de tester si le joueur pris en parametre est en situation de jeu critique (etat de famine).
 *
 * Elle prend en paramètre :
 *      la séance de jeu encours , l'indice du joueur 
 * Elle rétourne :
 *      une valeur booléenne en fonctions du cas
 */
BOOL enEtatCritique(Jeu jeu, int joueur);



#endif

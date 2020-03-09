#ifndef __MOTEUR_HEADERFILE__
#define __MOTEUR_HEADERFILE__

#include "Place.h"
#include "Jeu.h"

/**
 * elle permet de passer la main au joueur adverse.
 * 
 * Elle prend en paramètre :
 *		le numéro du joueur actif
 * Elle rétourne :
 *      le numéro du joueur adverse.
 */
int passer_le_tour(int jr);

/**
 * elle permet de l'état d'un joueur afin de savoir son apptitude 
 * à continuer le jeu en vérifiant si ces trous sur le tablier ne sont pas vides.
 *  (situation de famine ou non)
 * 
 * Elle prend en paramètre :
 *		le tablier et le numéro du joueur .
 * Elle rétourne :
 *      une valeur booléenne en fonctions du cas
 */
BOOL estJrCritique(int tablier[2][6], int jr);

/**
 * elle permet de tester si un joueur peut récolter des graines dans un trou donné.
 * 
 * Elle prend en paramètre :
 *		le tablier,le numéro du joueur et le trou .
 * Elle rétourne :
 *      une valeur booléenne en fonctions du cas
 */
BOOL estPlaceActive(int tablier[2][6], Place emp, int jr);

/**
 * elle permet à un joueur de récolter des graines dans un trou du tablier.
 * 
 * Elle prend en paramètre :
 *		le tablier,le numéro du joueur et le trou .
 * Elle rétourne :
 *     le nombre de graines récolter.
 */
int prendre_bille(int tablier[2][6], Place p, int jr);

/**
 * elle permet à un joueur récolter et semer des graines d'un trou vers un autre. 
 * 
 * Elle prend en paramètre :
 *		le tablier, le trou de récolte des graines .
 * Elle rétourne :
 *      le trou où les graines ont été semées
 */
Place deplace_billes(int tablier[2][6], Place p);

/**
 * elle permet tester si un joueur à la capacité réquise pour semer dans les trous
 * du joueur adverse dans des cas particuliers. 
 * 
 * Elle prend en paramètre :
 *		le tablier, le numéro du joueur.
 * Elle rétourne :
 *      une valeur booléenne en fonctions du cas
 */
BOOL peutServir(int tablier[2][6], int jr);

/**
 * elle éffectue certaines tâches de fin de jeu comme l'attribution des résultats 
 * aux joueurs etc d'autres ( fcts a version basique)
 * 
 * Elle prend en paramètre :
 *		la séance de jeu, le numéro du joueur et son résultat de la séance de jeu.
 * Elle rétourne :
 *      rien
 */
//void finJeu(Jeu jeu, int jr, int resultat[2]);

int max_billes_ramassable(int tablier[2][6], Place p, int joueur);
BOOL applique_coup(Jeu *jeu,Place p);
BOOL applique_coup_IA(Jeu *jeu);
Place choix_place_IA(Jeu *jeu);


#endif

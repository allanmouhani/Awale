#ifndef __TABLIER_HEADERFILE__
#define __TABLIER_HEADERFILE__

#include "Types.h"
#include "Place.h"


/**
 * elle permet de créer et d'initialiser le tablier
 * 
 * Elle prend en paramètre :
 *		un tableau à dimension (x, y)
 */
void intialiser_tablier(int tablier[2][6]);

/**
 * elle permet de vérifier si les trous sur une ligne du tablier sont vides ( sans graines)
 * 
 * Elle prend en paramètre :
 *		le tablier de jeu, la valeur de l'ordonné du tablier qui précise le numéro de la ligne.
 * Elle rétourne :
 *      une valeur booléenne en fonctions du cas
 */
BOOL estLigneVide(int tablier[2][6], int num);



BOOL estPlaceVide(int tablier[2][6], Place p);

/**
 * elle permet de vérifier un trou donné est valide, c'est à dire si ces coordonnées 
 * sur le tablier existe bien. ( respect des contraites pesant sur le tablier)
 * 
 * Elle prend en paramètre :
 *		le trou ou la place sur le tablier 
 * Elle rétourne :
 *      une valeur booléenne en fonctions du cas
 */
BOOL estPlaceValide(Place p);

/**
 * elle permet d'obtenir le nombre de graine(s) existant(s) dans un trou .
 * 
 * Elle prend en paramètre :
 *		le tablier et le trou
 * Elle rétourne :
 *      -1 si les coordonnées de la place n'appartiennent pas au tablier 
 *       sinon , elle retourne le nombre de graines.
 */
int billes(int tablier[2][6], Place p);

/**
 * elle permet d'enlever un nombre de graine(s) dans un trou du tablier (récolte) .
 * 
 * Elle prend en paramètre :
 *		le tablier, le trou et le nombre de graines à enlever.
 * Elle rétourne :
 *       une valeur booléenne en fonctions du cas (s'il existe ou non des graines dans le trou)
 */
BOOL supprimeBilles(int tablier[2][6], Place p, int bille);

/**
 * elle permet d'ajouter un nombre de graine(s) dans un trou du tablier (semer) .
 * 
 * Elle prend en paramètre :
 *		le tablier, le trou et le nombre de graines à ajouter.
 * Elle rétourne :
 *       une valeur booléenne en fonctions du cas (s'il existe ou non des graines dans le trou)
 */
BOOL ajoutBilles(int tablier[2][6], Place p, int bille);


#endif

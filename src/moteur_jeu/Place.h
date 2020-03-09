#ifndef __PLACE_HEADERFILE__
#define __PLACE_HEADERFILE__

#include "Types.h"

/**
* Modélisation abstraite des trous qu'on nommera "place" par la suite.
*
* -le trou ou la place dans un (Tablier ou plateau):
*      Place[x][y] =  Trou[x][y]
* l'abcisse x et l'ordonnée y forme le couple de coordonnée (x,y)
* qui situe un trou sur le tablier.
*/
typedef struct Place
{

    int x;
    int y;

} Place;

/**
 * elle permet de créer et d'initialiser un trou (place)
 *
 * Elle prend en paramètre :
 *		le trou A et le trou B
 * Elle rétourne :
 * 		le trou précedent sur le tablier
 */
Place place_intiale(int x, int y);

/**
 * elle prend un trou et retourne le chemin selon la verticale
 * à partir du trou actuel.
 *
 * Elle prend en paramètre : un  trou
 * Elle rétourne un entier suivant l'ordonné .
 * 		
 */
int chemin(Place place_occupe);

/**
 * elle prend un trou et renvoie son précédent sur le tablier
 *
 * Elle prend en paramètre :
 *		le trou A et le trou B
 * Elle rétourne :
 * 		le trou précedent sur le tablier
 */
Place place_precedente(Place place_occupe);

/**
 * elle prend un trou et renvoie son suivant sur le tablier
 *
 * Elle prend en paramètre :
 *		le trou A et le trou B
 * Elle rétourne :
 * 		le trou suivant sur le tablier
 */
Place place_suivante(Place place_occupe);

/**
 * elle permet de tester l'égalité de deux trous
 *
 * Elle prend en paramètre :
 *		le trou A et le trou B
 * Elle rétourne :
 * 		true ou false en fonction de chaque cas
 */
BOOL estEgal(Place placeA, Place placeB);



#endif

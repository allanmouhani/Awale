#include "Place.h"
#include "Moteur.h"

Place place_intiale(int x, int y)
{
    return (Place) {x, y};
}

int chemin(Place place_occupe)
{
    return place_occupe.y == 0 ? -1 : 1;
}

Place place_precedente(Place place_occupe)
{

  if(place_occupe.x == 5 && place_occupe.y == 0)
    return place_intiale(5, 1);
  else if(place_occupe.x == 0 && place_occupe.y == 1)
    return place_intiale(0, 0);
  
  place_occupe.x += -1 * chemin(place_occupe);
  
  return place_occupe;
}

Place place_suivante(Place place_occupe)
{

  if(place_occupe.x == 0 && place_occupe.y == 0)
    return place_intiale(0, 1);
  else if(place_occupe.x == 5 && place_occupe.y == 1)
    return place_intiale(5, 0);
  
  place_occupe.x += chemin(place_occupe);
  
  return place_occupe;
}

BOOL estEgal(const Place placeA, const Place placeB)
{
    return (placeA.x == placeB.x) && (placeA.y == placeB.y);
}







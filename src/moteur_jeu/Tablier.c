#include "Tablier.h"


void intialiser_tablier(int tablier[2][6])
{
    for(int y = 0; y < 2; y++)
        for(int x = 0; x < 6; x++)
            tablier[y][x] = 3; 
}


BOOL estLigneVide(int tablier[2][6], int num)
{
    return tablier[num][0] == 0 && tablier[num][1] == 0 && tablier[num][2] == 0 && tablier[num][3] == 0 && tablier[num][4] == 0 && tablier[num][5] == 0;
}


BOOL estPlaceValide(Place p)
{
    return (p.x >= 0 && p.x <= 5) && (p.y >= 0 && p.y <= 1);
}


BOOL estPlaceVide(int tablier[2][6], Place p)
{
	return (tablier[p.y][p.x] == 0);
	
}

int billes(int tablier[2][6], Place p)
{
    if(!estPlaceValide(p))
        return -1;

    return tablier[p.y][p.x];
}

BOOL supprimeBilles(int tablier[2][6], Place p, int val)
{
    if(!estPlaceValide(p))
        return FALSE;
        
    if(tablier[p.y][p.x] < val)
        return FALSE;

    tablier[p.y][p.x]-=val;
    
    return TRUE;
}

BOOL ajoutBilles(int tablier[2][6], Place p, int val)
{
    if(!estPlaceValide(p))
        return FALSE;

    tablier[p.y][p.x]+=val;
    return TRUE;
}


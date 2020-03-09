#include "Jeu.h"
#include "Tablier.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>


Jeu creer_jeu(int typeJeu, char *nomJ1 , char *nomJ2)
{

    Jeu jeu;

    intialiser_tablier(jeu.tablier);
    
    if(typeJeu != ETAT_JOUER_VS_IA)
		jeu.joueur = rand() % 2;
	else
		jeu.joueur = 1;
    jeu.resultat[0] = jeu.resultat[1] = 0;
    jeu.lancer_intial = TRUE;
    jeu.etat_critique[0] = jeu.etat_critique[1] = FALSE;
    jeu.typeJeu = typeJeu;
    
 
    snprintf(jeu.nomJ1,10, "%s",nomJ1);
    snprintf(jeu.nomJ2,10, "%s",nomJ2);
	    
    return jeu;
}


BOOL enEtatCritique(Jeu jeu, int joueur)
{
    return jeu.etat_critique[joueur];
}

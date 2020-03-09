#include "Moteur.h"

#include "FichierConstante.h"
#include "Tablier.h"
#include "Jeu.h"
#include <stdio.h>


int passer_le_tour(int jr)
{
    return (jr + 1) % 2;
}


BOOL estJrCritique(int tablier[2][6], int jr)
{
    return estLigneVide(tablier, jr);
}


BOOL estPlaceActive(int tablier[2][6], Place p, int jr)
{
    return p.y != jr && (tablier[p.y][p.x] == 2 || tablier[p.y][p.x] == 3);
}

int prendre_bille(int tablier[2][6], Place p, int jr)
{
    int nb_bille_res = 0;
    while(estPlaceActive(tablier, p, jr))
        {
            int nb_bille = billes(tablier, p);
            supprimeBilles(tablier, p, nb_bille);
            nb_bille_res+= nb_bille;
            p = place_precedente(p);
        }
    return nb_bille_res;
}


Place deplace_billes(int tablier[2][6], Place p)
{
    Place p1 = p;
    int nb_bille = billes(tablier, p);

    while((nb_bille--) > 0)
    {
        p1 = place_suivante(p1);
        
        if(estEgal(p1, p))
            p1 = place_suivante(p1);

        ajoutBilles(tablier, p1, 1);
        supprimeBilles(tablier, p, 1);
    }

    return p1;
}


BOOL peutServir(int tablier[2][6], int jr)
{
    if(jr == JOUEUR_1)
    {
        for(int i = 0; i < 6; i++)
            if((i - tablier[jr][i] < 0))
                return TRUE;
    }
    else if(jr == JOUEUR_2)
    {
        for(int i = 0; i < 6; i++)
            if(i + tablier[jr][i] > 5)
                return TRUE;
    }

    return FALSE;
}

int max_billes_ramassable(int tablier[2][6], Place p, int joueur)
{
	int max = 0;
	
	while(estPlaceActive(tablier,p,joueur))
	{
		max++;
		p = place_precedente(p);
	}
	
	return max;
	
}


BOOL applique_coup(Jeu *jeu,Place p)
{
    BOOL quitter = FALSE;
          
    if(enEtatCritique(*jeu, jeu->joueur))
    {
     	passer_le_tour(jeu->joueur);
        quitter = TRUE;
    }
                
    else if(enEtatCritique(*jeu, passer_le_tour(jeu->joueur)) && !peutServir(jeu->tablier, jeu->joueur))
		quitter = TRUE;

    if(jeu->tablier[p.y][p.x] != 0){

	    jeu->place_vise = p;
	    jeu->place_occupe = jeu->place_vise;
	    jeu->place_vise = deplace_billes(jeu->tablier, jeu->place_vise);

	    jeu->etat_critique[jeu->joueur] = estJrCritique(jeu->tablier, jeu->joueur);
	            
	    jeu->resultat[jeu->joueur] = jeu->resultat[jeu->joueur] + prendre_bille(jeu->tablier, jeu->place_vise, jeu->joueur);
	    jeu->etat_critique[passer_le_tour(jeu->joueur)] = estJrCritique(jeu->tablier, passer_le_tour(jeu->joueur));

	    if(jeu->resultat[jeu->joueur] >= 19)
	           quitter = TRUE;

		jeu->joueur = passer_le_tour(jeu->joueur);
	    
	    if(jeu->lancer_intial)
	       jeu->lancer_intial = FALSE;
	}

    return quitter;      
}

BOOL applique_coup_IA(Jeu *jeu)
{
    BOOL quitter = FALSE;
      
    Place p = choix_place_IA(jeu);
          
    if(enEtatCritique(*jeu, jeu->joueur))
    {
     	passer_le_tour(jeu->joueur);
        quitter = TRUE;
    }
                
    else if(enEtatCritique(*jeu, passer_le_tour(jeu->joueur)) && !peutServir(jeu->tablier, jeu->joueur))
		quitter = TRUE;

    if(jeu->tablier[p.y][p.x] != 0){

	    jeu->place_vise = p;
	    jeu->place_occupe = jeu->place_vise;
	    jeu->place_vise = deplace_billes(jeu->tablier, jeu->place_vise);

	    jeu->etat_critique[jeu->joueur] = estJrCritique(jeu->tablier, jeu->joueur);
	            
	    jeu->resultat[jeu->joueur] = jeu->resultat[jeu->joueur] + prendre_bille(jeu->tablier, jeu->place_vise, jeu->joueur);
	    jeu->etat_critique[passer_le_tour(jeu->joueur)] = estJrCritique(jeu->tablier, passer_le_tour(jeu->joueur));

	    if(jeu->resultat[jeu->joueur] >= 19)
	           quitter = TRUE;

		jeu->joueur = passer_le_tour(jeu->joueur);
	    
	    if(jeu->lancer_intial)
	       jeu->lancer_intial = FALSE;
	}

    return quitter;      
}


Place choix_place_IA(Jeu *jeu)
{
	int max_bille = 0;
    int tmp = -1;
    Place p;
    int i;
    
    for(i = 0; i < 6; i++)
    {
                    
		p = place_intiale(i, JOUEUR_IA);
        int nb_bille = billes(jeu->tablier, place_intiale(i, JOUEUR_IA));
        
        if(nb_bille > 0)
        {
			for(;nb_bille > 0; nb_bille--)
                p = place_suivante(p);
                
            int nb_bille_deplacer = max_billes_ramassable(jeu->tablier, p, JOUEUR_IA);
            
            if(nb_bille_deplacer > max_bille)
            {
                 tmp = i;
                 max_bille = nb_bille_deplacer;
             }
          }
	  }

      if(max_bille > 0)
         return place_intiale(tmp, JOUEUR_IA);

       do {
                p = place_intiale(rand() % 6, JOUEUR_IA);
            }            
            while(estPlaceVide(jeu->tablier, p));

        return p;	
}


/*void finJeu(Jeu jeu, int jr, int resultat[2])
{

    char res[2][STRING_MAX_CHAR];
    sprintf(res[0], "Le jr 1 a reçu %d billes", resultat[0]);
    sprintf(res[1], "Le jr 2 a reçu %d billes", resultat[1]);

    char victoire[STRING_MAX_CHAR];
    sprintf(victoire, "Le jr %d", jr+1);

}*/


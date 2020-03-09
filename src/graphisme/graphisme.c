                                                            /*********************************************************************/
                                                           /*   Ce fichier contient les fonctions permettant de gérer l'aspect  */
                                                          /*    graphique du Jeu.                                              */
                                                         /*                                                                   */
                                                        /*      Pour plus d'informations sur la description des  fonctions,  */
                                                       /*       se référer au fichier graphisme.h                           */
                                                      /*                                                                   */
                                                     /*********************************************************************/

#include "graphisme.h"


boolean init_graphics(SDL_Window **fenetre, SDL_Surface **surface_fenetre, SDL_Surface **image_icone)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr," L'initialisation de la SDL a échoué  \n Message d'erreur : %s \n\n\n", SDL_GetError());
		return FAUX;
	}
	if(!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)))
	{
		printf(" L'initialisation de la SDL_image a échoué \n Message d'erreur : %s \n\n\n", IMG_GetError());
		return FAUX;
	}
	if(TTF_Init() == -1)
	{
		printf(" L'initialisation de la SDL_ttf a échoué \n Message d'erreur : %s \n\n\n", TTF_GetError());
		return FAUX;
	}


	if((*fenetre = SDL_CreateWindow(" Awalé - Menu principal ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN)) == NULL)
	{
		printf(" Le chargement de la fenêtre SDL a échoué  \n Message d'erreur : %s  \n\n\n", SDL_GetError());
		return FAUX;
	}
	
	if((*image_icone = IMG_Load("images/icon.png")) != NULL)
		SDL_SetWindowIcon(*fenetre,*image_icone);
	else
	    	printf(" Le chargement de l'icône a échoué : %s\n", SDL_GetError());
	

	if((*surface_fenetre = SDL_GetWindowSurface(*fenetre)) == NULL)
	{
		printf(" Le chargement de surface de la fenêtre a échoué \n Message d'erreur : %s  \n\n\n", SDL_GetError());
		return FAUX;
	}

		
	return VRAI;

}




void exit_graphics(SDL_Window **fenetre , SDL_Surface **image_fond_MP, SDL_Surface **image_icone)
{
	for(int i=0; i<256; i++)
		TTF_CloseFont(police[i]),police[i] = NULL;

	SDL_FreeSurface(*image_fond_MP);
	*image_fond_MP = NULL;

	SDL_FreeSurface(*image_icone);
	*image_icone = NULL;

	SDL_DestroyWindow(*fenetre);
	*fenetre = NULL;
	
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}






SDL_Surface* charger_image(char* chemin, SDL_Surface * surface_fenetre)
{
	SDL_Surface *image = IMG_Load(chemin);
	SDL_Surface *image_optimale = NULL;

	if(image == NULL)
	{
		printf(" Le chargement de \" %s \" a échoué \n Message d'erreur : %s\n", chemin, IMG_GetError());
		return NULL;
	}

	if((image_optimale = SDL_ConvertSurface(image, surface_fenetre->format, 0)) == NULL)
		return image;
	else
	{
		SDL_FreeSurface(image);
		return image_optimale;
	}
}






SDL_Surface **charger_images_graines(SDL_Surface *surface_fenetre)
{
	SDL_Surface **image_graines = NULL;
	char nom_images[17] = {'\0'};
	int i = 0,j = 1;

	if((image_graines = malloc(NB_IMAGES_GRAINES * sizeof(SDL_Surface *))) == NULL)
		return NULL;

	while(i < NB_IMAGES_GRAINES)
		if(j <= 8)
		{
			snprintf(nom_images, (size_t)17, "images/seed%d.bmp",j);

			if((image_graines[i] = charger_image(nom_images,surface_fenetre)) == NULL)
				break;

			SDL_SetColorKey(image_graines[i], SDL_TRUE, blanc);
			i += 1;
			j += 1;

		}

	if((i < NB_IMAGES_GRAINES) && (image_graines[i] == NULL))
	{
		for(i=0; i<NB_IMAGES_GRAINES; i++)
			SDL_FreeSurface(image_graines[i]) , image_graines[i] = NULL;

		free(image_graines);
		image_graines = NULL;
	}
	
	
	return image_graines;

}





void exit_jeu(SDL_Surface **image_graines , SDL_Surface **image_main_joueur, SDL_Surface **image_main_joueur2)
{

	int i;

	for(i=0; i<NB_IMAGES_GRAINES; i++)
		SDL_FreeSurface(image_graines[i]) , image_graines[i] = NULL;

	free(image_graines);
	image_graines = NULL;

	SDL_FreeSurface(*image_main_joueur);
	*image_main_joueur = NULL;

	if(image_main_joueur2 != NULL)
	{
		SDL_FreeSurface(*image_main_joueur2);
		*image_main_joueur2 = NULL;
	}

}






Place converti_point_en_trou(POINT P , int id_joueur)
{
	Place t;
	
	if(id_joueur == 1)
	{
		t.y = 1;
		
		if(P.x > 210 && P.x < 306)	
			t.x = 0;
		else if(P.x > 320 && P.x < 417)	
			t.x = 1;
		else if(P.x > 429 && P.x < 522)
			t.x = 2;
		else if(P.x > 538 && P.x < 634)
			t.x = 3;
		else if(P.x > 650 && P.x < 743)	
			t.x = 4;
		else
			t.x = 5;
	}
	else
	{
		t.y = 0;
		
		if(P.x > 746 && P.x < 841)	
			t.x = 5;
		else if(P.x > 634 && P.x < 727)	
			t.x = 4;
		else if(P.x > 524 && P.x < 618)
			t.x = 3;
		else if(P.x > 414 && P.x < 509)
			t.x = 2;
		else if(P.x > 305 && P.x < 399)	
			t.x = 1;
		else
			t.x = 0;
	}

	return t;
	
	
}






POINT converti_trou_en_point(Place p , int id_joueur)
{
	POINT point;

	if(id_joueur == 1)
	{
		point.y = 471;
		
		if(p.x == 0)
			point.x = 228;
		else if(p.x == 1)	
			point.x = 337;
		else if(p.x == 2)
			point.x = 445;
		else if(p.x == 3)
			point.x = 548;
		else if(p.x == 4)
			point.x = 680;
		else
			point.x = 769;
	}
	else
	{
		point.y = 323;

		if(p.x == 5)
			point.x = 754;
		else if(p.x == 4)
			point.x = 648;
		else if(p.x == 3)
			point.x = 540;
		else if(p.x == 2)
			point.x = 424;
		else if(p.x == 1)
			point.x = 315;
		else
			point.x = 212;
	}

	return point;
}




boolean est_coup_valide(POINT clic , int id_joueur)
{	
	if(id_joueur == 1)
	{
			if((clic.x > 210 && clic.x < 846) && (clic.y > 438 && clic.y < 549))
				return VRAI;
			else
				return FAUX;
	}
	else
	{
			if((clic.x > 197 && clic.x < 843) && (clic.y > 290 && clic.y < 407))
				return VRAI;
			else
				return FAUX;
	}
	
}




void afficher_nombre_de_graines(SDL_Surface **image_jeu,int nombre_graines,int joueur, POINT P)
{
	char texte[5] = {'\0'};
	snprintf(texte, 5, "%d",nombre_graines);
	
	if(joueur == 0)
		P.y = 472; 
	else
		P.y = 150;
	
	affiche_texte(image_jeu ,texte, 25, P, blanc);
	
}

void afficher_graines_capturees(SDL_Surface **image_jeu,SDL_Surface **image_graines,int nombre_graines,int joueur)
{
	SDL_Rect rect;
		
	if(joueur == 0)
		rect.x = 904 ,rect.y = 189;
	else
		rect.x = 910 ,rect.y = 558;
	
	if(nombre_graines >= 8)
		SDL_BlitSurface(image_graines[7],NULL,*image_jeu,&rect);
	else if(nombre_graines > 0)
		SDL_BlitSurface(image_graines[nombre_graines - 1],NULL,*image_jeu,&rect);
	
}



void affiche_etat_tablier(Place p, Jeu *jeu, SDL_Surface **image_graines, SDL_Surface *image_jeu)
{
	int i,j;
	SDL_Rect position;
	POINT P;
	
	for(i=0; i<2; i++)
	{	
		for(j=0; j<6; j++)
		{	
									
			p.x = j, p.y = i;
			P = converti_trou_en_point(p ,i);
			position.x = P.x , position.y = P.y;

			if(jeu->tablier[i][j] == 0);
			else if(jeu->tablier[i][j] >= 8)
			{
					SDL_BlitSurface(image_graines[7],NULL,image_jeu,&position);
					afficher_nombre_de_graines(&image_jeu,jeu->tablier[i][j],i,P);
			}		
			else
				SDL_BlitSurface(image_graines[jeu->tablier[i][j] - 1],NULL,image_jeu,&position);

		}
	

	}



}

void affiche_fin_jeu(SDL_Window **fenetre ,SDL_Surface *surface_fenetre ,Jeu *jeu)
{
	
	SDL_Event event;
	boolean quitter = FAUX;
	SDL_Surface *image_fin_jeu = NULL;
	SDL_Surface *image_animation = NULL;
	char message_fin[50] = {'\0'};
	POINT P1,P2,clic;
	SDL_Rect pos;
	int i=0;
	
	
	P1.x = 0,P1.y = 477;
	P2.x = 100, P2.y = 377;
	
	if((image_animation = charger_image("images/fireworks.bmp",surface_fenetre)) != NULL)	
	{
		SDL_SetColorKey(image_animation, SDL_TRUE, noir);
		
		if(jeu->resultat[1] > jeu->resultat[0])
			snprintf(message_fin,(size_t) 50,"%s a gagne avec %d graines recoltees ",jeu->nomJ1,jeu->resultat[1]);
		else if(jeu->resultat[1] < jeu->resultat[0])
			snprintf(message_fin,(size_t) 50,"%s a gagne avec %d graines recoltees ",jeu->nomJ2,jeu->resultat[0]);
			
		while(!quitter)
		{
			
			if((image_fin_jeu = charger_image("images/ecran_fin_jeu.png",surface_fenetre)) != NULL)
			{
				SDL_Delay(500);
				
				for(i=0; i<5; i++)
				{
					pos.x = (rand() % (1080 - 1 + 1)) + 1;
					pos.y = (rand() % (500 - 1 + 1)) + 1;
					SDL_BlitSurface(image_animation,NULL,image_fin_jeu,&pos);
				}
				
				P1.x += 100;
					
				if(P1.x > LARGEUR)
					P1.x = -200;
								
				if(jeu->resultat[1] == jeu->resultat[0])
					affiche_texte(&image_fin_jeu ,"Match Nul", 45, P1, blanc);
				else
				{			
					affiche_texte(&image_fin_jeu ,"Felicitations !!!", 45, P1, blanc);
					affiche_texte(&image_fin_jeu ,message_fin, 35, P2, blanc);

				}	
						
				while( SDL_PollEvent( &event ) != 0 )
				{
					
					if(event.type == SDL_QUIT)
						quitter = VRAI;	
					else if((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
					{
						SDL_GetMouseState(&clic.x,&clic.y);

						if((clic.x > 416 && clic.x < 694) && (clic.y > 622 && clic.y < 687))
							quitter = VRAI;
						
					}
				}


				SDL_BlitSurface(image_fin_jeu,NULL,surface_fenetre,NULL);
				SDL_UpdateWindowSurface(*fenetre);

			}
			
			SDL_FreeSurface(image_fin_jeu);
		}
			
		SDL_FreeSurface(image_animation);
	}
	
}

void affiche_jeu_joueur1_joueur2(SDL_Window **fenetre ,SDL_Surface *surface_fenetre ,Jeu *jeu)
{

	SDL_Surface *image_jeu = NULL;
	SDL_Surface *image_main_joueur = NULL;
	SDL_Surface *image_main_joueur2 = NULL;
	SDL_Surface **image_graines = NULL;
	boolean fin = FAUX;
	boolean partie_sauv = FAUX;
	SDL_Event event;
	POINT P1,P2,P3,P4,clic;
	P1.x = 22 , P1.y = 50;
	P2.x = 22 , P2.y = 545;
	P3.x = 1015 , P3.y = 150;
	P4.x = 1011 , P4.y = 530;
	char recolteJ1[5];
	char recolteJ2[5];
	SDL_Rect position_main_joueur;
	Place p;
		
	if(((image_graines = charger_images_graines(surface_fenetre)) != NULL)	&& ((image_main_joueur = charger_image("images/pickup_hand.png",surface_fenetre)) != NULL) && ((image_main_joueur2 = charger_image("images/pickup_hand2.png",surface_fenetre)) != NULL))
	{

		SDL_SetColorKey(image_main_joueur, SDL_TRUE, blanc);
		SDL_SetColorKey(image_main_joueur2, SDL_TRUE, blanc);
			
		while(!fin)
		{
			SDL_SetWindowTitle(*fenetre,"Awalé - Jeu");
			SDL_ShowCursor(SDL_DISABLE);
			
			if((image_jeu = charger_image("images/planche.bmp",surface_fenetre)) != NULL)
			{

				affiche_texte(&image_jeu ,jeu->nomJ1, 25, P1, noir);
				affiche_texte(&image_jeu ,jeu->nomJ2, 25, P2, noir);

				snprintf(recolteJ1, 5, "%d",jeu->resultat[1]);
				snprintf(recolteJ2, 5, "%d",jeu->resultat[0]);

				affiche_texte(&image_jeu ,recolteJ1, 25, P3, noir);
				affiche_texte(&image_jeu ,recolteJ2, 25, P4, noir);
				
				afficher_graines_capturees(&image_jeu,image_graines,jeu->resultat[0],0);
				afficher_graines_capturees(&image_jeu,image_graines,jeu->resultat[1],1);
				
				
				affiche_etat_tablier(p, jeu,image_graines,image_jeu);


				SDL_WaitEvent( &event );

				if(event.type == SDL_QUIT)
					fin = VRAI;
				else if((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
				{
					SDL_GetMouseState(&clic.x,&clic.y);

					if(est_coup_valide(clic , jeu->joueur))
					{
						p = converti_point_en_trou(clic,jeu->joueur);
						fin = applique_coup(jeu,p);		
						
						if(fin)
							partie_sauv = FAUX;
							
					}
					else if((clic.x > 18 && clic.x < 85) && (clic.y > 19 && clic.y < 85))
						affiche_regles(surface_fenetre,fenetre);
					else if((clic.x > 986 && clic.x < 1052) && (clic.y > 20 && clic.y < 86))
						fin = affiche_menu_pause(surface_fenetre,fenetre,jeu);
							
				}
				else if(event.type == SDL_MOUSEMOTION)
				{
					
					SDL_GetMouseState(&position_main_joueur.x,&position_main_joueur.y);
					
					if(jeu->joueur == 1)
					{
						position_main_joueur.x -= image_main_joueur->w/2;
						position_main_joueur.y -= image_main_joueur->h/2;

						SDL_BlitSurface(image_main_joueur,NULL,image_jeu,&position_main_joueur);
					}
					else
					{
						position_main_joueur.x -= image_main_joueur2->w/2;
						position_main_joueur.y -= image_main_joueur2->h/2;

						SDL_BlitSurface(image_main_joueur2,NULL,image_jeu,&position_main_joueur);
					}	
					
				}
				
				SDL_BlitSurface(image_jeu,NULL,surface_fenetre,NULL);
				SDL_UpdateWindowSurface(*fenetre);
				SDL_FreeSurface(image_jeu);
					
								
			}

	  	 }

		 SDL_ShowCursor(SDL_ENABLE);
		 
		 if(!partie_sauv)
			affiche_fin_jeu(fenetre ,surface_fenetre ,jeu);
	}

	exit_jeu(image_graines,&image_main_joueur,&image_main_joueur2);

}



void affiche_jeu_joueur_IA(SDL_Window **fenetre ,SDL_Surface *surface_fenetre ,Jeu *jeu)
{

	SDL_Surface *image_jeu = NULL;
	SDL_Surface *image_main_joueur = NULL;
	SDL_Surface **image_graines = NULL;
	boolean fin = FAUX;
	boolean partie_sauv = FAUX;
	SDL_Event event;
	POINT P1,P2,P3,P4,P5,P6,clic;
	P1.x = 22 , P1.y = 50;
	P2.x = 22 , P2.y = 545;
	P3.x = 1015 , P3.y = 150;
	P4.x = 1011 , P4.y = 530;
	P5.x = 450 , P5.y = 500;
	P6.x = 430 , P6.y = P5.y;
	char recolteJ1[5];
	char recolteJ2[5];
	SDL_Rect position_main_joueur;
	Place p;
		
	if(((image_graines = charger_images_graines(surface_fenetre)) != NULL)	&& ((image_main_joueur = charger_image("images/pickup_hand.png",surface_fenetre)) != NULL))
	{

		SDL_SetColorKey(image_main_joueur, SDL_TRUE, blanc);
			
		while(!fin)
		{
			SDL_SetWindowTitle(*fenetre,"Awalé - Jeu");
			SDL_ShowCursor(SDL_DISABLE);
			
			if((image_jeu = charger_image("images/planche.bmp",surface_fenetre)) != NULL)
			{

				affiche_texte(&image_jeu ,jeu->nomJ1, 25, P1, noir);
				affiche_texte(&image_jeu ,jeu->nomJ2, 25, P2, noir);

				snprintf(recolteJ1, 5, "%d",jeu->resultat[1]);
				snprintf(recolteJ2, 5, "%d",jeu->resultat[0]);

				affiche_texte(&image_jeu ,recolteJ1, 25, P3, noir);
				affiche_texte(&image_jeu ,recolteJ2, 25, P4, noir);
				
				afficher_graines_capturees(&image_jeu,image_graines,jeu->resultat[0],0);
				afficher_graines_capturees(&image_jeu,image_graines,jeu->resultat[1],1);
				
				                 
                if(jeu->typeJeu == ETAT_JOUER_VS_IA && jeu->joueur == JOUEUR_IA)
				{
					affiche_texte(&image_jeu ,"Attendez votre tour", 25, P6, rouge);	
					affiche_etat_tablier(p, jeu,image_graines,image_jeu);
					SDL_BlitSurface(image_jeu,NULL,surface_fenetre,NULL);
					SDL_UpdateWindowSurface(*fenetre);
					
					SDL_Delay(4000);
					fin = applique_coup_IA(jeu);
					
					SDL_FreeSurface(image_jeu);
				}
				else
				{
					affiche_texte(&image_jeu ,"A vous ", 25, P5, blanc);
					
					if(jeu->typeJeu == ETAT_JOUER_VS_IA && jeu->joueur == JOUEUR_2)
						affiche_etat_tablier(p, jeu,image_graines,image_jeu);
						
					SDL_WaitEvent( &event );

					if(event.type == SDL_QUIT)
						fin = VRAI;
					else if((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
					{
						SDL_GetMouseState(&clic.x,&clic.y);

						if(est_coup_valide(clic , jeu->joueur))
						{
							p = converti_point_en_trou(clic,jeu->joueur);
							fin = applique_coup(jeu,p);	
							
							if(fin)
								partie_sauv = FAUX;
								
						}
						else if((clic.x > 18 && clic.x < 85) && (clic.y > 19 && clic.y < 85))
							affiche_regles(surface_fenetre,fenetre);
						else if((clic.x > 986 && clic.x < 1052) && (clic.y > 20 && clic.y < 86))
							partie_sauv = fin = affiche_menu_pause(surface_fenetre,fenetre,jeu);
							
								
					}
					else if(event.type == SDL_MOUSEMOTION)
					{
						
						SDL_GetMouseState(&position_main_joueur.x,&position_main_joueur.y);
						
						if(jeu->typeJeu == ETAT_JOUER_VS_IA || jeu->joueur == 1)
						{
							position_main_joueur.x -= image_main_joueur->w/2;
							position_main_joueur.y -= image_main_joueur->h/2;

							SDL_BlitSurface(image_main_joueur,NULL,image_jeu,&position_main_joueur);
						}
						
					}
					
					SDL_BlitSurface(image_jeu,NULL,surface_fenetre,NULL);
					SDL_UpdateWindowSurface(*fenetre);
					SDL_FreeSurface(image_jeu);
				}	
				
				
			}
			
	  	 }
		
		 SDL_ShowCursor(SDL_ENABLE);
	
		 if(!partie_sauv)
			affiche_fin_jeu(fenetre ,surface_fenetre ,jeu);
	}

	exit_jeu(image_graines,&image_main_joueur,NULL);

}


boolean affiche_menu_pause(SDL_Surface * surface_fenetre,SDL_Window **fenetre, Jeu *jeu)
{
	SDL_SetWindowTitle(*fenetre,"Awalé - Pause");

	SDL_ShowCursor(SDL_ENABLE);

	SDL_Surface *image_menu_pause = NULL;
	char *nom_fichier = NULL; 
	SDL_Event event;
	boolean quitter = FAUX;
	boolean quit = FAUX;
	POINT P;

	if((image_menu_pause = charger_image("images/menu_jeu.jpg",surface_fenetre)) != NULL)
	{

		SDL_BlitSurface(image_menu_pause,NULL,surface_fenetre,NULL);
		SDL_UpdateWindowSurface(*fenetre);

		while(!quitter)
		{

			SDL_WaitEvent( &event );

			if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
			{
				SDL_GetMouseState(&P.x,&P.y);
				
				if((P.x > 372 && P.x < 686) && (P.y > 292 && P.y < 373))
				{
	
					if(!(nom_fichier = calloc(TAILLE_MAX_NOM,sizeof(char))))
						quitter = VRAI;
					else if(traite_saisi_utilisateur(surface_fenetre ,fenetre,"nom du fichier", &nom_fichier) == NON_DEFINI)
						quitter = VRAI;
					else
					{
						sauvergarder_jeu(nom_fichier,jeu);
						quitter = VRAI;

					}
					
					free(nom_fichier);		
					
				}	
				else if((P.x > 374 && P.x < 685) && (P.y > 421 && P.y < 504))
					quitter = VRAI;
				else if((P.x > 381 && P.x < 693) && (P.y > 585 && P.y < 669))
					quit = quitter = VRAI;
				
			}
			
			
		}

		SDL_FreeSurface(image_menu_pause);
	
	}
	
	
	return quit;

}


void affiche_regles(SDL_Surface * surface_fenetre,SDL_Window **fenetre)
{
	SDL_SetWindowTitle(*fenetre,"Awalé - Règles du Jeu");

	SDL_ShowCursor(SDL_ENABLE);

	SDL_Surface *image_regle_jeu = NULL; 
	SDL_Event event;
	boolean quitter = FAUX;
	POINT P;

	if((image_regle_jeu = charger_image("images/regles_jeu.jpg",surface_fenetre)) != NULL)
	{

		SDL_BlitSurface(image_regle_jeu,NULL,surface_fenetre,NULL);
		SDL_UpdateWindowSurface(*fenetre);

		while(!quitter)
		{

			SDL_WaitEvent( &event );

			if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
			{
				SDL_GetMouseState(&P.x,&P.y);
				
				if((P.x > 329 && P.x < 656) && (P.y > 642 && P.y < 708))
					quitter = VRAI;
				
			}
			
			
		}

		SDL_FreeSurface(image_regle_jeu);


	}


}


void affiche_regle_jeu(SDL_Surface * surface_fenetre,SDL_Window **fenetre)
{
	SDL_SetWindowTitle(*fenetre,"Awalé - Règles du Jeu");

	SDL_Surface *image_regle_jeu = NULL; 
	SDL_Event event;
	boolean quitter = FAUX;
	POINT P;

	if((image_regle_jeu = charger_image("images/regles.jpg",surface_fenetre)) != NULL)
	{

		SDL_BlitSurface(image_regle_jeu,NULL,surface_fenetre,NULL);
		SDL_UpdateWindowSurface(*fenetre);

		while(!quitter)
		{

			SDL_WaitEvent( &event );

			if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
			{
				SDL_GetMouseState(&P.x,&P.y);
				
				if((P.x > 394 && P.x < 687) && (P.y > 536 && P.y < 702))
					quitter = VRAI;
				
			}
			
			
		}

		SDL_FreeSurface(image_regle_jeu);


	}


}


boolean affiche_fichiers_sauvegardes(SDL_Surface * surface_fenetre , SDL_Window **fenetre, char **texte, char **nom,POINT P1,int taille_texte)
{
	SDL_Event event;
	boolean quitter = FAUX;
	SDL_Surface *image_saisi_nom = NULL;
	char c[20] = {'\0'};
	int nb_total_lettre = 0 , i;
	POINT P2;
	P2.x = 303 , P2.y = 280;
	
	while(!quitter)
	{
		
		if((image_saisi_nom = charger_image("images/saisi_utilisateur.jpg",surface_fenetre)) != NULL)
		{

			if(nom != NULL)
			{
				P1.x = 425;
				P1.y = 550;
				for(i=0; i<7; i++)
				{
					memset(c,0,(size_t)20);
					snprintf(c,(size_t)20,"%d-%s",i,texte[i]);
					
					P1.y -= 32;
					affiche_texte(&image_saisi_nom ,c, taille_texte, P1,vert);					
				}	
				if(nb_total_lettre > 0)
					affiche_texte(&image_saisi_nom , *nom, 40, P2, noir);
					
				while( SDL_PollEvent( &event ) != 0 )
				{

					if(event.type == SDL_QUIT)
						quitter = NON_DEFINI;	
					else if(event.type == SDL_KEYDOWN)
					{
						if(event.key.keysym.sym == SDLK_RETURN  && nb_total_lettre > 0)
							quitter = VRAI;
						else if(event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z)
						{
							if(nb_total_lettre < TAILLE_MAX_NOM - 1)
							{	(*nom)[nb_total_lettre] = event.key.keysym.sym;
								nb_total_lettre += 1;
							} 
						}		
						else if((event.key.keysym.sym == SDLK_BACKSPACE) && (nb_total_lettre > 0))
						{	(*nom)[nb_total_lettre - 1] = '\0' ;
							nb_total_lettre -= 1;
						}	
						
					}
				
				}	
					
			}
			else
			{
				SDL_WaitEvent(&event);
				
				if(event.type == SDL_QUIT)
					quitter = NON_DEFINI;
				
				affiche_texte(&image_saisi_nom , *texte, taille_texte, P1, blanc);	
				affiche_texte(&image_saisi_nom ,"Cliquez sur la croix pour retourner au menu", 20, P2, noir);	
			}			

			SDL_BlitSurface(image_saisi_nom,NULL,surface_fenetre,NULL);
			SDL_UpdateWindowSurface(*fenetre);

		}
		
		SDL_FreeSurface(image_saisi_nom);
	}	
	
	return quitter;
}

boolean charger_jeu(SDL_Surface * surface_fenetre , SDL_Window **fenetre, Jeu *jeu)
{

	char **nom_fichiers = NULL;
	char *nom_fichier_choisi = NULL;
	int c = 0;
	int char_lu = 0;
	boolean quitter = FAUX;
	POINT P;
	FILE *fichier_temp = NULL;
	int i;
	int nombre_de_fichiers = 0;
	char chemin_complet_fichier[50];
	
	if(!(nom_fichier_choisi = calloc(20,sizeof(char))))
		return FAUX;
	if(!(nom_fichiers = calloc(7,sizeof(char*))))
	{
		free(nom_fichier_choisi);
		return FAUX;
	}
	else
		for(i=0; i<7; i++)
			if(!(nom_fichiers[i] = calloc(TAILLE_MAX_NOM,sizeof(char))))
				break;
				
	if(i<7)
	{
		for(i=0; i<7; i++)
			free(nom_fichiers[i]);
		free(nom_fichiers);
		free(nom_fichier_choisi);
		
		return quitter;
	}		
	if(!(fichier_temp = fopen("./Fichiers_sauvegardes/fichier_temp","a+")))
		return quitter;
	
	for(i=0; i<7; i++)
	{
		while((c = fgetc(fichier_temp)) != '\n' && c != EOF && char_lu < TAILLE_MAX_NOM)
		{
			nom_fichiers[i][char_lu] = c;
			char_lu += 1;
		}	
		
		if(c == '\n')
			nombre_de_fichiers += 1;
		char_lu = 0;
		c = 0;
	}		
	
	fclose(fichier_temp);
	
	if(nombre_de_fichiers == 0)
	{
		P.x = 425;
		P.y = 460;
		
		snprintf(nom_fichier_choisi,(size_t)20, "Rien a afficher");
		quitter = affiche_fichiers_sauvegardes(surface_fenetre ,fenetre,&nom_fichier_choisi,NULL,P,30); 
			
	}
	else
	{
		quitter = affiche_fichiers_sauvegardes(surface_fenetre ,fenetre,nom_fichiers,&nom_fichier_choisi,P,20);
		
		if(quitter == VRAI)
		{
			memset(chemin_complet_fichier,0,(size_t)50);		
			snprintf(chemin_complet_fichier,(size_t)50,"./Fichiers_sauvegardes/%s",nom_fichier_choisi);
			
			if(!(fichier_temp = fopen(chemin_complet_fichier,"rb")))
				quitter = NON_DEFINI;
			else	
			{
			
				c = fread(jeu,sizeof(*jeu),1,fichier_temp);
				
			//if( c == 0 && feof(fichier_temp))
				//quitter = VRAI;
			//else
				//quitter = NON_DEFINI;
				
				fclose(fichier_temp);
			}	
		
		 }	
		
	}	

	for(i=0; i<7; i++)
		free(nom_fichiers[i]);
	free(nom_fichiers);
	free(nom_fichier_choisi);		
	
	return quitter;
}


boolean sauvergarder_jeu(char *nom_fichier, Jeu *jeu)
{
	FILE *fichier = NULL;
	FILE *fichier_temp = NULL;
	char nom_complet[50];
	
	snprintf(nom_complet,(size_t)50, "./Fichiers_sauvegardes/%s",nom_fichier);
	
	if(!(fichier = fopen((const char*)nom_complet,"wb+")))
		return FAUX;
	if(!(fichier_temp = fopen("./Fichiers_sauvegardes/fichier_temp","a+")))
	{
		fclose(fichier);
		return FAUX;
	}			
	if(fwrite(jeu,sizeof(*jeu),1,fichier) == 0)
	{
		fclose(fichier_temp);
		fclose(fichier);
		return FAUX;
	}
	else
	{
		fprintf(fichier_temp,"%s \n",nom_fichier);
		
		fclose(fichier_temp);
		fclose(fichier);
		return VRAI;
	}			
		
}	

boolean traite_saisi_utilisateur(SDL_Surface * surface_fenetre , SDL_Window **fenetre, char *texte, char **nom)
{
	SDL_Event event;
	boolean quitter = FAUX;
	SDL_Surface *image_saisi_nom = NULL;
	int nb_total_lettre = 0;
	POINT P1 , P2;
	P1.x = 420 , P1.y = 500;
	P2.x = 303 , P2.y = 280;
	
	while(!quitter)
	{
		
		if((image_saisi_nom = charger_image("images/saisi_utilisateur.jpg",surface_fenetre)) != NULL)
		{

			affiche_texte(&image_saisi_nom , texte, 45, P1, blanc);

			if(nb_total_lettre > 0)
				affiche_texte(&image_saisi_nom , *nom, 40, P2, noir);
					
			while( SDL_PollEvent( &event ) != 0 )
			{

				if(event.type == SDL_QUIT)
					quitter = NON_DEFINI;	
				else if(event.type == SDL_KEYDOWN)
				{
					if(event.key.keysym.sym == SDLK_RETURN  && nb_total_lettre > 0)
						quitter = VRAI;
					else if(event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z)
					{
						if(nb_total_lettre < TAILLE_MAX_NOM - 1)
						{	(*nom)[nb_total_lettre] = event.key.keysym.sym;
							 nb_total_lettre += 1;
						} 
					}	
					else if((event.key.keysym.sym == SDLK_BACKSPACE) && (nb_total_lettre > 0))
					{	(*nom)[nb_total_lettre - 1] = '\0' ;
						nb_total_lettre -= 1;
					}	
						
				}
				
			}


			SDL_BlitSurface(image_saisi_nom,NULL,surface_fenetre,NULL);
			SDL_UpdateWindowSurface(*fenetre);

		}
		
		SDL_FreeSurface(image_saisi_nom);
	}	
	
	return quitter;
}



void affiche_mode_joueur1_IA(SDL_Surface * surface_fenetre , SDL_Window **fenetre)
{
	
	SDL_SetWindowTitle(*fenetre,"Awalé - Mode Joueur vs IA");
	
	Jeu jeu;
	char *nom_joueur1 = NULL;
	char *nom_joueur2 = "IA";
	
	if(!(nom_joueur1 = calloc(TAILLE_MAX_NOM,sizeof(char))))
		return;
	
	if(traite_saisi_utilisateur(surface_fenetre ,fenetre, "JOUEUR 1", &nom_joueur1) == NON_DEFINI)
		return;
	
	jeu = creer_jeu(ETAT_JOUER_VS_IA,nom_joueur1 ,nom_joueur2);
	affiche_jeu_joueur_IA(fenetre ,surface_fenetre ,&jeu);
	
	free(nom_joueur1);

}



void affiche_mode_joueur1_joueur2(SDL_Surface * surface_fenetre , SDL_Window **fenetre)
{
	
	SDL_SetWindowTitle(*fenetre,"Awalé - Mode Joueur vs Joueur");
	
	Jeu jeu;
	char *nom_joueur1 = NULL;
	char *nom_joueur2 = NULL;
	
	if(!(nom_joueur1 = calloc(TAILLE_MAX_NOM,sizeof(char))))
		return;
	
	if(!(nom_joueur2 = calloc(TAILLE_MAX_NOM,sizeof(char))))
	{
		free(nom_joueur1);
		return;
	}
	

	if(traite_saisi_utilisateur(surface_fenetre ,fenetre, "JOUEUR 1", &nom_joueur1) == NON_DEFINI)
		return;
	if(traite_saisi_utilisateur(surface_fenetre ,fenetre, "JOUEUR 2", &nom_joueur2) == NON_DEFINI)
		return;	
	
	jeu = creer_jeu(ETAT_JOUER_CVSC,nom_joueur1 ,nom_joueur2);
	affiche_jeu_joueur1_joueur2(fenetre ,surface_fenetre ,&jeu);
	
	free(nom_joueur1);
	free(nom_joueur2);

}





void traite_action_menu_principal(POINT P ,SDL_Surface * surface_fenetre ,SDL_Window **fenetre)
{
	int ret;
	
	if((P.x > 399 && P.x < 694) && (P.y > 595 && P.y < 673))
	{
		Jeu jeu;
			
		memset(&jeu,0,sizeof(jeu));
		ret = charger_jeu(surface_fenetre,fenetre, &jeu);
		
		if(ret == FAUX || ret == NON_DEFINI)
			return;
		if(jeu.typeJeu == ETAT_JOUER_CVSC)
			affiche_jeu_joueur1_joueur2(fenetre,surface_fenetre,&jeu);
		else
			affiche_jeu_joueur_IA(fenetre,surface_fenetre,&jeu);
	}		
	if((P.x > 1012 && P.x < 1060) && (P.y > 661 && P.y < 704))
		affiche_regle_jeu(surface_fenetre,fenetre);
	else if((P.x > 392 && P.x < 689) && (P.y > 432 && P.y < 525))
		affiche_mode_joueur1_joueur2(surface_fenetre,fenetre);
	else if((P.x > 387 && P.x < 693) && (P.y > 302 && P.y < 385))
		affiche_mode_joueur1_IA(surface_fenetre,fenetre);		

}





void afficher_menu_principale(SDL_Window **fenetre , SDL_Surface **image_fond_MP , SDL_Surface **surface_fenetre)
{

	SDL_Event event;
	boolean quitter = FAUX;
	POINT P;

	while(!quitter)
	{
		SDL_SetWindowTitle(*fenetre,"Awalé - Menu Principal");

		SDL_WaitEvent(&event);

		if(event.type == SDL_QUIT)
			quitter = VRAI;
		else if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
		{
			SDL_GetMouseState(&P.x,&P.y);
			traite_action_menu_principal(P, *surface_fenetre ,fenetre);
		}
					
		SDL_BlitSurface(*image_fond_MP,NULL,*surface_fenetre,NULL);
		SDL_UpdateWindowSurface(*fenetre);

	}
	
}

void charger_police(int taille)
{

	if (taille < 256 && police[taille] == NULL)
	{
		police[taille] = TTF_OpenFont(POLICE_NAME,taille);
		if (police[taille] == NULL) 
			fprintf(stderr," L'ouverture du fichier de police %s a échoué (taille = %d)\n Message d'erreur : %s \n\n\n",POLICE_NAME,taille,TTF_GetError()),exit(1);
	}
	
}


int largeur_texte(char *texte, int taille)
{
	int l, h;
	charger_police(taille);
	TTF_SizeText(police[taille],texte,&l,&h);
	return l;
}

int hauteur_texte(char *texte, int taille)
{
	int l, h;
	charger_police(taille);
	TTF_SizeText(police[taille],texte,&l,&h);
	return h;
}

void affiche_texte(SDL_Surface **image_fond , char *texte, int taille, POINT P, COULEUR coul)
{

	
	if (texte == NULL || strlen(texte) == 0) return;


	charger_police(taille);
	
	SDL_Color color;
	SDL_GetRGB(coul,(*image_fond)->format,&(color.r),&(color.g),&(color.b));

	
	SDL_Surface *surface = NULL;
	surface = TTF_RenderText_Blended(police[taille], texte, color);

	if (!surface) 
	{
		 fprintf(stderr,"Erreur Affichage Texte ---> TTF_RenderText_Blended() : %s \n\n\n",TTF_GetError()); 
		 return;
 	}


	SDL_Rect position;
	position.x = P.x;
	position.y = HAUTEUR - P.y;
	SDL_BlitSurface(surface, NULL, *image_fond, &position);
	SDL_FreeSurface(surface);

}

	
void affiche_texte_centre(SDL_Surface **image_fond, char *texte, int taille, POINT P, COULEUR coul)
{
	
	P.x -= largeur_texte(texte,taille)/2;
	P.y += hauteur_texte(texte,taille)/2;
	affiche_texte(image_fond,texte,taille,P,coul);
}




int main(int argc, char *argv[])
{
	srand(time(NULL));
	
	SDL_Window *fenetre = NULL;
	SDL_Surface *surface_fenetre = NULL;
	SDL_Surface *image_fond_MP = NULL;
	SDL_Surface *image_icone = NULL;


	if(init_graphics(&fenetre, &surface_fenetre, &image_icone))
	{
		if((image_fond_MP = charger_image("images/menu_pp.jpg",surface_fenetre)))
		{
			afficher_menu_principale(&fenetre , &image_fond_MP , &surface_fenetre);
		
		}
	}

	exit_graphics(&fenetre , &image_fond_MP, &image_icone);

	return 0;
}

                                                            /*************************************************************************/
                                                           /*   Ce fichier contient les prototypes de fonctions définis dans        */
                                                          /*    graphisme.c                                                        */
                                                         /*                                                                       */
                                                        /*      Pour plus d'informations sur l'implémentation de ces fonctions,  */
                                                       /*       se référer au fichier graphisme.c                               */
                                                      /*                                                                       */
                                                     /*************************************************************************/




#ifndef GRAPHISME 
#define GRAPHISME

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "couleur.h"
#include <time.h>
#include "../moteur_jeu/Jeu.h"
#include "../moteur_jeu/Moteur.h"


#define LARGEUR 1080
#define HAUTEUR 720
#define NB_IMAGES_GRAINES 8
#define POLICE_NAME "Ed_Wood_Movies.ttf"    //Nom du fichier de police utilisé pour l'affichage de texte.


TTF_Font *police[256] = {NULL};            //Variable globale de type TTF_Font dans laquelle est initialisée les différentes tailles de polices < 256.

#define NB_RANGEES 2                     //Nombre de rangées du tablier.
#define NB_TROUS_PAR_RANGEE 6           //Nombre de trous par rangée.
#define TAILLE_MAX_NOM 10              //Constante définissant la longueur maximum du nom d'un joueur.


// Enumération représentant un type booléen.
typedef enum
{
     FAUX,VRAI,NON_DEFINI
}boolean;


// Structure permettant de gérer les coordonnées de la souris.
typedef struct
{
	int x;
	int y;
}POINT;


typedef Uint32 COULEUR;






/* init_graphics : cette fonction est comme son nom l'indique, la fonction permettant d'initialiser l'environnement graphique SDL.
                   Elle prend en paramètre :
                                            SDL_Window **fenetre               :  correspondant à la fenêtre SDL avec laquelle l'utilisateur intéragit.
                                            SDL_Surface **surface_fenetre      :  correspondant à la surface de la fenêtre dans laquelle s'effectue les opérations graphiques.
                                            SDL_Surface **image_icone          :  correspondant à l'image d'icône du jeu. 

                   Elle retourne un booléen , en fonction du résultat globale de l'initialisation.               */

boolean init_graphics(SDL_Window **fenetre, SDL_Surface **surface_fenetre, SDL_Surface **image_icone);




/* exit_graphics : cette fonction permet de libérer les ressources allouées pour l'environnement graphique SDL.
                   Elle prend en paramètre :
                                            SDL_Window  **fenetre            :  correspondant à la fenêtre SDL avec laquelle l'utilisateur intéragit.
                                            SDL_Surface **image_fond_MP      :  correspondant à l'image faisant office de menu principal.
                                            SDL_Surface **image_icone        :  correspondant à l'image d'icône du jeu. */

void exit_graphics(SDL_Window **fenetre , SDL_Surface **image_fond_MP, SDL_Surface **image_icone);





/* charger_image : cette fonction permet de charger une image.
                   Elle prend en paramètre :
                                            char* chemin                      :  chemin menant indiquant l'emplacement du fichier.
                                            SDL_Surface *surface_fenetre      :  correspondant à la surface de la fenêtre dans laquelle s'effectue les opérations graphiques.

                   Elle retourne , un pointeur vers une variable de type SDL_Surface* représentant l'image , en cas de succès ou NULL en cas d'erreur. */

SDL_Surface* charger_image(char* chemin, SDL_Surface * surface_fenetre);




/* charger_images_graines : cette fonction permet de charger les images représentant les gaines du jeu.
                            Elle prend en paramètre :
                                                      SDL_Surface *surface_fenetre      :  correspondant à la surface de la fenêtre dans laquelle s'effectue les opérations graphiques.

                            Elle retourne , un pointeur vers une variable de type SDL_Surface** représentant les images , en cas de succès ou NULL en cas d'erreur. */

SDL_Surface **charger_images_graines(SDL_Surface *surface_fenetre);





/* exit_jeu : cette fonction permet de libérer les ressources allouées pour la partie de jeu en cours .
              Elle prend en paramètre :
                                        SDL_Surface **image_graines      :  correspondant aux images représentant les graines du jeu.
                                        SDL_Surface **image_main_joueur  :  correspondnat à l'image représentant la main du joueur 1.
                                        SDL_Surface **image_main_joueur2 :  correspondnat à l'image représentant la main du joueur 2.*/

void exit_jeu(SDL_Surface **image_graines , SDL_Surface **image_main_joueur, SDL_Surface **image_main_joueur2);





/* converti_point_en_trou : cette fonction permet de convertir un POINT (clic du Joueur) en Trou du tablier.
                            Elle prend en paramètre :
                                                      POINT P       : représentant les coordonées graphiques du trou sélectionné par l'utilisateur.
                                                      int id_joueur : représentant l'identifiant du joueur.

                            Elle retourne une variable de type Place représentant les coordonnées matricielles du trou sélectionné */

Place converti_point_en_trou(POINT P , int id_joueur);





/* converti_trou_en_point : cette fonction permet de convertir un Trou du tablier en POINT.
                            Elle prend en paramètre :
                                                      Place p       : représentant les coordonnées matricielles du trou sélectionné par l'utilisateur.
                                                      int id_joueur : représentant l'identifiant du joueur.

                            Elle retourne une variable de type POINT représentant les coordonées graphiques du trou sélectionné */

POINT converti_trou_en_point(Place p , int id_joueur);






/* applique_coup : cette fonction met à jour le tablier en fonction de l'action entreprit par les joueurs.
                   Elle prend en paramètre :
                                              Jeu *jeu : l'instance du jeu en cours.
                                              Place p  : représentant les coordonnées matricielles du trou sélectionné par l'utilisateur.

                   Elle retourne une variable de type boolean , ayant pour valeur VRAI si le jeu est terminé ou FAUX s'il ne l'est pas encore. */

//boolean applique_coup(Jeu *jeu,Place p);





/* est_coup_valide : cette fonction teste la validité du coup d'un joueur .
                     Elle prend en paramètre :
                                              POINT clic     : représentant les coordonnées graphiques du clic de la souris.
                                              int id_joueur  : représentant l'identifiant du joueur.

                     Elle retourne une variable de type boolean , ayant pour valeur VRAI si le clic est valide oet FAUX sinon. */

boolean est_coup_valide(POINT clic , int id_joueur);




void afficher_nombre_de_graines(SDL_Surface **image_jeu,int nombre_graines,int joueur, POINT P);

/* affiche_jeu : cette fonction affiche la partie de jeu en cours.
                 Elle prend en paramètre :
                                           SDL_Window **fenetre          : correspondant à la fenêtre SDL avec laquelle l'utilisateur intéragit.
                                           SDL_Surface *surface_fenetre  : correspondant à la surface de la fenêtre dans laquelle s'effectue les opérations graphiques.
                                           int typeJeu                   : correspondant au mode du jeu (Joeur contre Joueur | Joueur contre IA).
                                           char *nomJ1                   : correspondant au nom du joueur 1.
                                           char *nomJ2                   : correspondant au nom du joueur 2.

 */

void affiche_jeu(SDL_Window **fenetre ,SDL_Surface *surface_fenetre ,Jeu *jeu);






/* affiche_menu_pause : cette fonction affiche le menu pause de la partie de jeu en cours.
                        Elle prend en paramètre :
                                                  SDL_Window **fenetre          : correspondant à la fenêtre SDL avec laquelle l'utilisateur intéragit.
                                                  SDL_Surface *surface_fenetre  : correspondant à la surface de la fenêtre dans laquelle s'effectue les opérations graphiques.
                                           
                        Elle retourne une variable de type boolean, indiquant l'action de l'utilisateur.


 */

boolean affiche_menu_pause(SDL_Surface * surface_fenetre,SDL_Window **fenetre, Jeu *jeu);









/* affiche_regles : cette fonction affiche les règles du Jeu depuis la partie en cours.
                    Elle prend en paramètre :
                                                  SDL_Window **fenetre          : correspondant à la fenêtre SDL avec laquelle l'utilisateur intéragit.
                                                  SDL_Surface *surface_fenetre  : correspondant à la surface de la fenêtre dans laquelle s'effectue les opérations graphiques.

 */

void affiche_regles(SDL_Surface * surface_fenetre,SDL_Window **fenetre);




/* affiche_regle_jeu : cette fonction affiche les règles du Jeu depuis le menu principal.
                       Elle prend en paramètre :
                                                  SDL_Window **fenetre          : correspondant à la fenêtre SDL avec laquelle l'utilisateur intéragit.
                                                  SDL_Surface *surface_fenetre  : correspondant à la surface de la fenêtre dans laquelle s'effectue les opérations graphiques.

 */

void affiche_regle_jeu(SDL_Surface * surface_fenetre,SDL_Window **fenetre);


boolean sauvergarder_jeu(char *nom_fichier, Jeu *jeu);
boolean traite_saisi_utilisateur(SDL_Surface * surface_fenetre , SDL_Window **fenetre, char *texte, char **nom);
boolean affiche_fichiers_sauvegardes(SDL_Surface * surface_fenetre , SDL_Window **fenetre, char **texte, char **nom,POINT P1,int taille_texte);


/* affiche_mode_joueur1_joueur2 : cette fonction affiche les règles du Jeu depuis le menu principal.
                                  Elle prend en paramètre :
                                                           SDL_Window **fenetre          : correspondant à la fenêtre SDL avec laquelle l'utilisateur intéragit.
                                                           SDL_Surface *surface_fenetre  : correspondant à la surface de la fenêtre dans laquelle s'effectue les opérations graphiques.

 */

void affiche_mode_joueur1_joueur2(SDL_Surface * surface_fenetre , SDL_Window **fenetre);






/* traite_action_menu_principal : cette fonction gère les interactions avec l'utilisateur depuis le menu principal.
                                  Elle prend en paramètre :
                                                            POINT P                       : 
                                                            SDL_Surface *surface_fenetre  : correspondant à la surface de la fenêtre dans laquelle s'effectue les opérations graphiques.
                                                            SDL_Window **fenetre          : correspondant à la fenêtre SDL avec laquelle l'utilisateur intéragit.
                                                           
 */

void traite_action_menu_principal(POINT P, SDL_Surface * surface_fenetre ,SDL_Window **fenetre);




/* afficher_menu_principale : cette fonction affiche le menu principal.
                              Elle prend en paramètre :
                                                        SDL_Window  **fenetre            :  correspondant à la fenêtre SDL avec laquelle l'utilisateur intéragit.
                                                        SDL_Surface **image_fond_MP      :  correspondant à l'image faisant office de menu principal.
                                                        SDL_Surface **image_icone        :  correspondant à l'image d'icône du jeu. */

void afficher_menu_principale(SDL_Window **fenetre , SDL_Surface **image_fond_MP , SDL_Surface **surface_fenetre);




/* charger_police : cette fonction initialise la variable globale TTF_Font *police pour la taille de police demandé.
                              Elle prend en paramètre :
                                                        int taille :  correspondant à la taille de police.
 */

void charger_police(int taille);



/* largeur_texte : cette fonction calcul la largeur en pixel d'un texte pour une taille de police donné.
                   Elle prend en paramètre :
                                             char *texte :  correspondant au texte dont on calcul la largeur.
                                             int taille  :  correspondant à la taille de police.
 
                   Elle retourne une variable de type int , représentant la largeur ainsi calculée.
 */

int largeur_texte(char *texte, int taille);



/* hauteur_texte : cette fonction calcul la hauteur en pixel d'un texte pour une taille de police donné.
                   Elle prend en paramètre :
                                              char *texte :  correspondant au texte dont on calcul la hauteur.
                                              int taille  :  correspondant à la taille de police.

                   Elle retourne une variabe de type int représentant la hauteur ainsi calculée.
 */

int hauteur_texte(char *texte, int taille);




/* affiche_texte : cette fonction affiche du texte pour une taille de police donné.
                   Elle prend en paramètre :
                                             SDL_Surface **image_fond :  correspondant à l'image sur laquelle le texte doit être affiché.
                                             char *texte              :  correspondant au texte à afficher.
                                             int taille               :  correspondant à la taille de police.
                                             POINT P                  :  correspondant aux coordonnées du texte sur l'image.
                                             COULEUR coul             :  correspondant à la couleur souhaité pour le texte.

*/

void affiche_texte(SDL_Surface **image_fond , char *texte, int taille, POINT P, COULEUR coul);




/* affiche_texte_centre : cette fonction affiche du texte centré par rapport à la fenêtre pour une taille de police donné.
                          Elle prend en paramètre :
                                             SDL_Surface **image_fond :  correspondant à l'image sur laquelle le texte doit être affiché.
                                             char *texte              :  correspondant au texte à afficher.
                                             int taille               :  correspondant à la taille de police.
                                             POINT P                  :  correspondant aux coordonnées du texte sur l'image.
                                             COULEUR coul             :  correspondant à la couleur souhaité pour le texte.

*/


void affiche_texte_centre(SDL_Surface **image_fond, char *texte, int taille, POINT P, COULEUR coul);



#endif

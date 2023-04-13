/* CopyRight CRAC IUT CACHAN 
Rémi WAN */
#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <mbed.h>
#include <FATFileSystem.h>


bool mount_sd();
void listage(FATFileSystem fs);
void lcd_init();
int timer_read_ms(Timer timer);
int timer_read_s(Timer timer);
/*====================================================================|
                                CAN
|====================================================================*/

void canProcessRx();
int check_id(int CARD);

void CAN_ISR();

/*====================================================================|
                            MENU A 2 CHOIX
|====================================================================*/

void lcd_confirmation_menu(char * choix);
/**

 @param choix : str du choix précédement effectué pour l'afficher

**/
bool ts_confirmation_menu();
/**

Menu à 2 boutons

**/

bool choix_equipe();
/**

Menu à 2 boutons du cas CHOIX_COULEUR

**/
char choix_strategie();
/**

Menu du choix de la stratégie

**/

/*====================================================================|
                                BOUTONS
|====================================================================*/

void lcd_bouton(short marge_X, short marge_Y, short largeur_X, short hauteur_Y,int couleur_interne, int couleur_contour, int couleur_texte);
/**

Affichage du bouton :
*    @param marge_X : écart avec le bord gauche de l'écran (px)
*    @param marge_ : écart avec le bord droit de l'écran (px)
*    @param largeur_X : largeur (px)
*    @param hauteur_Y : hauteur (px)

*    @param couleur_interne : couleur du remplissage (ARGB)
*    @param couleur_contour : couleur de la bordure du bouton (ARGB)
*    @param couleur_texte : couleur du... (attention petit suspense) texte (ARGB)


--------------------------------------------------------------
Les couleurs sont enregistré sous le format ARGB Ex: #ff0055AA
Bits 7-8: niveau de transparence 
*    5-6: niveau de rouge 
*    3-4: niveau de vert 
*    1-2: niveau de bleu 
--------------------------------------------------------------
**/


bool bouton_hitbox(short marge_X, short marge_Y,short largeur_X,short hauteur_Y);
/**

Hitbox du bouton :
*    @param marge_X : écart avec le bord gauche de l'écran (px)
*    @param marge_ : écart avec le bord droit de l'écran (px)
*    @param largeur_X : largeur (px)
*    @param hauteur_Y : hauteur (px)

**/

/* A éviter */
bool bouton(short marge_X, short marge_Y, short largeur_X, short hauteur_Y,int couleur_interne, int couleur_contour, int couleur_texte);

void continuer(bool affiche_bouton);
/*
    pour que touchez l'écran fasse passer a l'étape suivante (attention tout l'écran n'est pas pris en compte)
*/

/*====================================================================|
                              AFFICHAGE
|====================================================================*/

void affichage_sd(bool sd_here);
/*
    Dois afficher si la carte SD est présente
*/

bool affichage_cartes();
/*
    Dois afficher les cartes connecté à l'IHM
*/

//Déco pendant que le programme tourne
void decoration();
void amogus();

//boutons particuliers:

void aff_entete();

#endif
/* CopyRight CRAC IUT CACHAN 
Rémi WAN */
#ifndef FONCTIONS_H
#define FONCTIONS_H

void lcd_init();

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


void affichage_sd(bool sd_here);
/*
    Dois afficher si la carte SD est présente
*/

void affichage_cartes();
/*
    Dois afficher les cartes connecté à l'IHM
*/


//boutons particuliers:

void aff_entête();
#endif
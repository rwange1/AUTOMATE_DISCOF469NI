#ifndef FONCTIONS_H
#define FONCTIONS_H

void lcd_init();

bool ts_confirmation_menu();

//Fonction d'affichage
void lcd_confirmation_menu(char * choix);

void lcd_bouton(short marge_X, short marge_Y, short largeur_X, short hauteur_Y,int couleur_interne, int couleur_contour, int couleur_texte);
bool bouton_hitbox(short marge_X, short marge_Y,short largeur_X,short hauteur_Y);
bool bouton(short marge_X, short marge_Y, short largeur_X, short hauteur_Y,int couleur_interne, int couleur_contour, int couleur_texte);

bool choix_equipe();
void affichage_sd(bool sd_here);
void affichage_cartes();


#endif
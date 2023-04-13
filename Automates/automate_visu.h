#ifndef AUTOMATE_VISU_H
#define AUTOMATE_VISU_H

//Liste des différents états de l'automate

typedef enum{
LAUNCH,         //Lancement
CHECK_CARTES,    //Check & Affichage des noms des cartes connectés
CHECK_SD,       //Check de la connection de la cartes SD
LECT_SD,   //Affiche le contenu de la carte SD avant le match
PROG_TEST,      
CHOIX_COULEUR,  //Choix du coté du terrain / Couleur de l'équipe
CHOIX_STRAT,    
LECTURE_FICHIER,
PROBLEM_FICHIER
} Auto_visuel_etat;


void automate_visuel();

#endif
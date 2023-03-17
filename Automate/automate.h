#ifndef AUTOMATE_H
#define AUTOMATE_H

//Liste des différents états de l'automate

typedef enum{
LAUNCH,         //Lancement
CHECK_CARTES,    //Check & Affichage des noms des cartes connectés
CHECK_SD,       //Check de la connection de la cartes SD
PRINT_SD,   //Affiche le contenu de la carte SD
PROG_TEST,      
CHOIX_COULEUR,  //Choix du coté du terrain / Couleur de l'équipe
CHOIX_STRAT,    
ATTENTE_JACK,
LECTURE_FICHIER,
PROBLEM_FICHIER
} Auto_etat;


void automate();

#endif
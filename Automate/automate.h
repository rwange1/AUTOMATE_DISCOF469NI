#ifndef AUTOMATE_H
#define AUTOMATE_H

//Liste des différents états de l'automate

typedef enum{
LAUNCH,         //Lancement
CHECK_CARTES,   //Check de la connections des cartes via CAN
AFFICHER_CARTES,    //Affiches les noms des cartes fonctionnelles
CHECK_SD,       //Check de la connection via cartes SD
PRINT_SD, //Affiche le contenu de la carte SD
PROG_TEST,      
PROG_MATCH,
CHOIX_COULEUR,  //Choix du coté du terrain / COuleur de l'équipe
CHOIX_STRAT,    
ATTENTE_JACK,
LECTURE_FICHIER,
PROBLEM_FICHIER
} Auto_etat;


void automate();

#endif
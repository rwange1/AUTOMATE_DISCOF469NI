#ifndef AUTO_MATCH_H
#define AUTO_MATCH_H

//Liste des différents états d'actions de l'automate

typedef enum{
    WAITING_JACK, //Attente du lancement du match
    GAME_START, //Lancement de la partie et des fonctions associés

    INSTRUCTION_LOADING,  //Chargement des actions du robot (l'idéal serait de créer un buffer stockant les in)
    INSTRUCTION_RUNNING,  
    INSTRUCTION_FREE, //Action terminée

    GAME_END,
    SCORE_SHOW, //Affichage du nombre de point

} Auto_match_etat;

void auto_match();



#endif
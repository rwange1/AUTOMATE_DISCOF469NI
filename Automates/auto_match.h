#ifndef AUTO_MATCH_H
#define AUTO_MATCH_H

//Liste des différents états d'actions de l'automate

typedef enum{
    CHECK_CARTES, //Même objectif que dans l'automate visuel (réalisation différentes)
    CHECK_CARTES_WAIT_ACK,

    TIMER_START, //Lancement du timer du match


    ETAT_CHECK_CARTES, //Envoie check toutes les carte 2
    ETAT_CHECK_CARTES_WAIT_ACK, //Time out de 1s 3
    ETAT_WAIT_FORCE,//Attente du forçage du lancement 4
    ETAT_CONFIG, //attente reception du choix du mode( debug ou game) 5
    ETAT_GAME_INIT,//Mise en mémoire du fichier de stratégie 6
    ETAT_GAME_WAIT_FOR_JACK,//Attente du retrait du jack 7
    ETAT_GAME_START,//Lancement du timer 100s 8
    ETAT_GAME_LOAD_NEXT_INSTRUCTION, // 9
    ETAT_GAME_PROCESS_INSTRUCTION, // A
    ETAT_GAME_WAIT_ACK, // B
    ETAT_GAME_JUMP_TIME,
    ETAT_GAME_JUMP_CONFIG,
    ETAT_GAME_JUMP_POSITION,
    ETAT_GAME_WAIT_END_INSTRUCTION,
    ETAT_END,
    ETAT_END_LOOP,
} auto_match_etat;

#endif
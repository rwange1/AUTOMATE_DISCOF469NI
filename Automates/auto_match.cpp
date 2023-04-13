#include "all_includes.h"

Timer timer;
Timer timout;

Auto_match_etat automatch_etat = WAITING_JACK;

void auto_match() {

  /* Initialisations de différents flag
  (voir la listes des ID pour plus d'info) */
  static bool jack = false;
  char buf[30];
  char num;
  char *equipe, *donnee_fichier;

  // Lancement de l'automate
  switch (automatch_etat) {
  case WAITING_JACK:
    if (jack == true) {
      automatch_etat = GAME_START;
    }
    break;

  case GAME_START:
    timer.start();
    // recalage?
    automatch_etat = INSTRUCTION_LOADING;
    break;

    case INSTRUCTION_LOADING:
        automatch_etat = INSTRUCTION_RUNNING;
    break;
    
      case INSTRUCTION_RUNNING:
        automatch_etat = INSTRUCTION_FREE;
    break;
    
    case INSTRUCTION_FREE:
        automatch_etat = INSTRUCTION_LOADING;
    break;
      case GAME_END:
      //Se met sur une assiette, funny action
        automatch_etat = SCORE_SHOW;

   case SCORE_SHOW:

    break;

    if(timer_read_s(timer)>90){
        automatch_etat = GAME_END;
    }
  }
}
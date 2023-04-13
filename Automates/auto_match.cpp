#include "all_includes.h"

Timer timer;
Timer timout;

Auto_match_etat automate_etat = WAITING_JACK;

void auto_match() {

  /* Initialisations de différents flag
  (voir la listes des ID pour plus d'info) */
  static bool jack = false;
  char buf[30];
  char num;
  char *equipe, *donnee_fichier;

  // Lancement de l'automate
  switch (automate_etat) {
  case WAITING_JACK:
    if (jack == true) {
      automate_etat = GAME_START;
    }
    break;

  case GAME_START:
    timer.start();
    // recalage?
    automate_etat = INSTRUCTION_LOADING;
    break;

    case INSTRUCTION_LOADING:
        automate_etat = INSTRUCTION_RUNNING;
    break;
    
      case INSTRUCTION_RUNNING:
        automate_etat = INSTRUCTION_FREE;
    break;
    
    case INSTRUCTION_FREE:

    break;
      case GAME_END:
        automate_etat = SCORE_SHOW;

   case SCORE_SHOW:

    break;
  }
}
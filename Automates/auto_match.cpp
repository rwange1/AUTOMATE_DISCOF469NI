#include "all_includes.h"

Timer timer;
Timer timout;
CANMessage msg;

Auto_match_etat automatch_etat = WAITING_JACK;
struct S_Instruction instruction;
unsigned char actual_instruction;

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
    switch (instruction.order) {
    case MV_BEZIER:
      break;
    case MV_COURBURE:
      break;
    case MV_LINE:
      break;
    case MV_TURN:
      break;
    case MV_XYT:
      break;
    case MV_RECALAGE:
      break;
    case ACTION:
      switch (instruction.arg1) {
      case 15: // Evitement
        break;
      case 16: // Set odo
        break;
      case 17: // wait
        break;
      case 18: // wait other bot
        break;
      case 19: // check pos adversaire
        break;
      case 20: // Fin de match
        break;
      case 21: // Ajouter point
        break;

      case 22: // Prise gateau
        msg.id = 0x201; //ASCENCEUR_PINCE
        msg.len = 0x01;
        msg.data[0]=0x01; //attraper
        busCAN.write(msg);
        break;

      case 23: // Relacher gateau
        msg.id = 0x201; //ASCENCEUR_PINCE
        msg.len = 0x01;
        msg.data[0]=0x01; //attraper
        busCAN.write(msg);
        break;
      case 24: // Monter gateau
        break;
      case 25: // pose cérise gateau
        break;
      case 26: // Attrape cérise
        break;
      case 27: // Tir cérise
        break;
      case 28: // déguisement
        break;
      }

      break;
    case POSITION_DEBUT:
      break;

    case UNKNOWN: // default
      break;
      //
    }
    break;

  case INSTRUCTION_RUNNING:

    automatch_etat = INSTRUCTION_FREE;
    break;

  case INSTRUCTION_FREE:
    automatch_etat = INSTRUCTION_LOADING;

    actual_instruction = instruction.nextLineOK;

    break;
  case GAME_END:
    // Se met sur une assiette, funny action
    automatch_etat = SCORE_SHOW;

  case SCORE_SHOW:

    break;

    if (timer_read_s(timer) > 90) {
      automatch_etat = GAME_END;
    }
  }
}
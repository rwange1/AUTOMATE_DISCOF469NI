#include "all_includes.h"

void auto_match() {
  Timer timer;
  Timer timout;
  
  Auto_match_etat automatch_etat = WAITING_JACK;
  struct S_Instruction instruction;
  unsigned char actual_instruction;
  CANMessage msg;

  /* Initialisations de différents flag
  (voir la listes des ID pour plus d'info) */
  static bool jack = false;
  int sens = 0;
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
      if (instruction.direction == LEFT) {
        // ?
      } else {
        //?
      }
            waiting_ack(0x101);
      break;
    case MV_LINE:
      if (instruction.direction == FORWARD) {
        sens = 1;
      } else {
        sens = -1;
      }
            waiting_ack(0x101);

      // id pour bouger
      break;
    case MV_TURN:
      if (instruction.direction == RELATIVE) {
        // Rotation (angle relatif) busCAN.msg()
      }
      if (instruction.direction == ABSOLUTE) {
        // Rotation (angle absolu) réelbusCAN.msg
      }
            waiting_ack(0x101);

      break;
    case MV_XYT:
      if (instruction.direction == FORWARD) {
        sens = 1;
      } else {
        sens = -1;
      }
      msg.id = 0x020;
      msg.len = 0x06;
      // Ces variables sont stocké sur des short
      short_to_char(instruction.arg1, &msg.data[0]); // x
      short_to_char(instruction.arg2, &msg.data[2]); // y
      short_to_char(instruction.arg3, &msg.data[4]); // z
      // theta
      busCAN.write(msg);
          waiting_ack(0x101);

      break;

    case MV_RECALAGE:
      if (instruction.direction == FORWARD) {
        sens = 1;
      } else {
        sens = -1;
      }
            waiting_ack(0x101);
      break;

    case ACTION:
      // 1er paramètre numérique
      switch (instruction.arg1) {
      case 15: // Evitement
        break;
      case 16: // Set odo
      waiting_ack(0x101);
        break;
      case 17: // wait
        ThisThread::sleep_for(500ms);
        break;
      case 18: // wait other bot
        break;
      case 19: // check pos adversaire
        break;
      case 20: // Fin de match
        break;
      case 21: // Ajouter point
        break;

        //**************** ACTION 2022 - 2023 ***************

      case 22:          // Prise gateau
        msg.id = 0x201; // ASCENCEUR_PINCE
        msg.len = 0x01;
        msg.data[0] = 0x01; // attraper

        busCAN.write(msg);
        waiting_ack(0x103);
        break;

      case 23:          // Relacher gateau
        msg.id = 0x201; // ASCENCEUR_PINCE
        msg.len = 0x01;
        msg.data[0] = 0x00; // relacher
        
        busCAN.write(msg);
        waiting_ack(0x103);

        break;

      case 24:          // Monter gateau
        msg.id = 0x201; // ASCENCEUR_ETAGE
        msg.len = 0x01;
        // paramètre d'Etage
        switch (instruction.arg2) {
        case 0:
          msg.data[0] = 0x00; // RDC
          break;
        case 1:
          msg.data[0] = 0x01; // E1
          break;
        case 2:
          msg.data[0] = 0x02; // E2
          break;
        case 3:
          msg.data[0] = 0x03; // E3
          break;
        }
        busCAN.write(msg);
        waiting_ack(0x103);

        break;
      case 25: // pose cerise gateau
        break;
        msg.id = 0x220;
      case 26: // Attrape cérise
        break;
        msg.id = 0x221;
      case 27: // Tir cérise
        msg.id = 0x222;
        break;
      case 28: // déguisement
        msg.id = 0x555;
        break;
      }

      break;
    case POSITION_DEBUT:
      break;

    case UNKNOWN: // default
      break;
      //
    }
    automatch_etat = INSTRUCTION_RUNNING;
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
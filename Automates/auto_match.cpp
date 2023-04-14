#include "all_includes.h"

CANMessage msg;
Timer timer;
Timer timout;
Auto_match_etat automatch_etat = WAITING_JACK;

struct S_Instruction instruction;
unsigned char actual_instruction;
struct S_Instruction strat_instructions[100];

void auto_match(char *prog) {

  /* Initialisations de différents flag
  (voir la listes des ID pour plus d'info) */
  static bool jack = true /*mettre a false*/, first_entry = true;
  static int sens = 0, nb_instructions = 0;
  static char buf[30];
  static char num;
  static char *equipe, *donnee_fichier;
  static char line_buffer[100];

  if (first_entry) {
    // CHARGEMENT DES INSTRUCTIONS
    instruction = strat_instructions[actual_instruction];

    // lecture_fichier(prog);
    nb_instructions = 0;
    FILE *testFile = fopen(prog, "rt");
    while (fgets(line_buffer, 100, testFile) != NULL) {
      instruction = stringToInstruction(line_buffer);
      strat_instructions[nb_instructions] = instruction;
      // printf(LineBuffer);
      // debug_Instruction(instruction);
      nb_instructions++;
      printf("%s,", line_buffer);
    }
    first_entry = false;
  }

  // Lancement de l'automate
  switch (automatch_etat) {
  case WAITING_JACK:
    if (jack == true) {
      automatch_etat = GAME_START;
    }
    break;

  case GAME_START:
    printf("TIMER START\n");
    timer.start();
    // recalage?
    automatch_etat = INSTRUCTION_LOADING;
    break;

  case INSTRUCTION_LOADING:
    printf("INSTRUCTION LOADING\n");
    switch (instruction.order) {
    case MV_BEZIER:
      break;
    case MV_COURBURE:
      printf("COURBE\n");

      if (instruction.direction == LEFT) {
        // ?
      } else {
        //?
      }
      if (waiting_ack(0x101)) {
        automatch_etat = INSTRUCTION_RUNNING;
      }
      break;
    case MV_LINE:
      printf("LINE\n");
      if (instruction.direction == FORWARD) {
        sens = 1;
      } else {
        sens = -1;
      }
      if (waiting_ack(0x101)) {
        automatch_etat = INSTRUCTION_RUNNING;
      }
      // id pour bouger
      break;
    case MV_TURN:
      printf("TURN\n");

      if (instruction.direction == RELATIVE) {
        // Rotation (angle relatif) busCAN.msg()
      }
      if (instruction.direction == ABSOLUTE) {
        // Rotation (angle absolu) réelbusCAN.msg
      }
      if (waiting_ack(0x101)) {
        automatch_etat = INSTRUCTION_RUNNING;
      }
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
      if (waiting_ack(0x101)) {
        automatch_etat = INSTRUCTION_RUNNING;
      }
      break;

    case MV_RECALAGE:
      if (instruction.direction == FORWARD) {
        sens = 1;
      } else {
        sens = -1;
      }
      if (waiting_ack(0x101)) {
        automatch_etat = INSTRUCTION_RUNNING;
      }
      break;

    case ACTION:
      // 1er paramètre numérique
      switch (instruction.arg1) {
      case 15: // Evitement
        break;
      case 16: // Set odo
        if (waiting_ack(0x101)) {
          automatch_etat = INSTRUCTION_RUNNING;
        }
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
        if (waiting_ack(0x103)) {
          automatch_etat = INSTRUCTION_RUNNING;
        }
        break;

      case 23:          // Relacher gateau
        msg.id = 0x201; // ASCENCEUR_PINCE
        msg.len = 0x01;
        msg.data[0] = 0x00; // relacher

        busCAN.write(msg);
        if (waiting_ack(0x103)) {
          automatch_etat = INSTRUCTION_RUNNING;
        }
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
        if (waiting_ack(0x103)) {
          automatch_etat = INSTRUCTION_RUNNING;
        }
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
    break;

  case INSTRUCTION_RUNNING:
    printf("INSTRCUTION RUNNING\n");

    automatch_etat = INSTRUCTION_FREE;
    break;

  case INSTRUCTION_FREE:
    printf("INSTRCUTION FREE\n");
    actual_instruction = instruction.nextLineOK;

    automatch_etat = INSTRUCTION_LOADING;

    break;
  case GAME_END:
    printf("END MATCH\n");
    send_id(0x555);

    // Se met sur une assiette, funny action
    automatch_etat = SCORE_SHOW;

  case SCORE_SHOW:

    break;
  }
  if (timer_read_s(timer) > 20) {
    automatch_etat = GAME_END;
  }
}
#include "automate.h"

Auto_etat automate_etat = LAUNCH;

void automate() {

  // Initialisations de différents flag (en booléen)
  bool sd_here, test, match, vert, bleu = false;


  // Lancement de l'automate
  switch (automate_etat) {
  // INITIALISATIONS
  case LAUNCH:

    automate_etat = CHECK_CARTES;
    break;

  // VERIFICATION DE L'ETAT DES CARTES
  case CHECK_CARTES:

    automate_etat = AFFICHER_CARTES;
    break;

  // AFFICHAGES DE L'ETAT DES CARTES
  case AFFICHER_CARTES:

    automate_etat = CHECK_SD;
    break;

  // VERIFICATION DE LA PRESENCE DE LA CARTE SD
  case CHECK_SD:
    if("CARTE SD TROUVE")
    {
        sd_here = 1;
    }
    automate_etat = PRINT_SD;
    break;

  // AFFICHAGE DE SI LA CARTE SD EST PRESENTE + DES FICHIERS EN INTERNES
  case PRINT_SD:

    // CAS programme test sélectionné
    if (test) {
      automate_etat = PROG_TEST;
    }
    // CAS carte SD présente
    if (sd_here) {
      // CAS programme MAtch sélectionné
      if (match) {
        automate_etat = PROG_MATCH;
      }
    }
    break;

  // LANCEMENT DU PROGRAMME TEST
  case PROG_TEST:
    break;

  // LANCEMENT DU PROGRAMME MATCH
  case PROG_MATCH: // Utile?
    break;

  // CHOIX CAMPS DU TERRAINf
  case CHOIX_COULEUR:
    vert = printf("INUPUT DU TOUCH SCREEN");
    if (vert) {
        bleu = 0;
        
        automate_etat = CHOIX_STRAT;

    }
    else if(bleu){
        vert = 0;
        automate_etat = CHOIX_STRAT;
    }
    break;

  // CHOIX SRATEGIE A APPLIQUER
  case CHOIX_STRAT:

    automate_etat = ATTENTE_JACK;
    break;

  // ATTENTE DU JACK
  case ATTENTE_JACK:

    automate_etat = LECTURE_FICHIER;
    break;

  // LECTURE FICHIER
  case LECTURE_FICHIER:
    automate_etat = PROBLEM_FICHIER;
    break;

  // DETECTION ERREUR
  case PROBLEM_FICHIER:
    break;
  }
}
#include "all_includes.h"

#define WAIT_TIME_MS 500ms

// Listes des ID (Cette carte aurras l'ID 0x01)

// Si l'état initiale est différent de LAUNCH c'est qu'il a été forcé pour debug
Auto_etat automate_etat = LAUNCH;

void automate() {


  /* Initialisations de différents flag
  (voir la listes des ID pour plus d'info) */
  static bool sd_here, test, match, check_equipe,sd = false;

  // Lancement de l'automate
  switch (automate_etat) {

  // INITIALISATIONS
  case LAUNCH:
    lcd_init();

    automate_etat = CHECK_CARTES;
    break;

  // VERIFICATION DE L'ETAT DES CARTES
  case CHECK_CARTES:
    // Fonction de détection des cartes nécessaire (peut etre tout a changer)
    // peut etre a mettre dans afficher_cartes

    automate_etat = AFFICHER_CARTES;
    break;

  // AFFICHAGES DE L'ETAT DES CARTES
  case AFFICHER_CARTES:
    affichage_cartes();

    automate_etat = CHECK_SD;

    break;

  // VERIFICATION DE LA PRESENCE DE LA CARTE SD
  case CHECK_SD:
  //Besoin du file système
    if (sd == 1) {
      sd_here = 1;

    } else {

      sd_here = 0;
    }
    automate_etat = PRINT_SD;

    break;

  // AFFICHAGE DE SI LA CARTE SD EST PRESENTE + DES FICHIERS EN INTERNES
  case PRINT_SD:

    affichage_sd(sd_here);

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
    automate_etat = CHOIX_COULEUR;

    break;

  // LANCEMENT DU PROGRAMME TEST
  case PROG_TEST:
    break;

  // LANCEMENT DU PROGRAMME MATCH
  case PROG_MATCH: // Utile?
    break;

    // CHOIX CAMPS DU TERRAIN

  case CHOIX_COULEUR:
    // Création d'une variable couleur
    bool couleur; //"vert" == 0 "bleu" == 1
    char *equipe;
    couleur = choix_equipe();

    // Gestion de l'affichage
    if (couleur == 0) {
      equipe = "Equipe verte";
    } else {
      equipe = "Equipe bleu";
    }

    // Vérication

    lcd_confirmation_menu(equipe);
    check_equipe = ts_confirmation_menu();

    if (check_equipe) {
      automate_etat = CHOIX_STRAT;
    }

    break;

  // CHOIX SRATEGIE A APPLIQUER
  case CHOIX_STRAT:

    automate_etat = ATTENTE_JACK;
    break;

  case ATTENTE_JACK:

    automate_etat = LECTURE_FICHIER;
    break;

  case LECTURE_FICHIER:
    automate_etat = PROBLEM_FICHIER;
    break;

  // DETECTION ERREUR
  case PROBLEM_FICHIER:

    lcd_bouton(250, 125, 300, 50, LCD_COLOR_WHITE, LCD_COLOR_BLACK,
               LCD_COLOR_BLACK);
    lcd.DisplayStringAt(0, LINE(7), (uint8_t *)"Fin du code", CENTER_MODE);

    break;
  }
  ts.GetState(&TS_State);
  wait_us(1000000);
}
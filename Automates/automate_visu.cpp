#include "all_includes.h"



// Si l'état initiale est différent de LAUNCH c'est qu'il a été forcé pour debug
Auto_visuel_etat automate_etat = LAUNCH;

void automate_visuel() {

  /* Initialisations de différents flag
  (voir la listes des ID pour plus d'info) */
  static bool sd_here,cartes_alive, test, match, check_equipe, check_num, sd = false;
  char buf[30];
  char num;
  char *equipe, *donnee_fichier;

  // Lancement de l'automate
  switch (automate_etat) {

  // INITIALISATION
  case LAUNCH:
    lcd_init();

    automate_etat = CHECK_CARTES;
    break;

  // VERIFICATION DE L'ETAT DES CARTES
  case CHECK_CARTES:
    // Fonction de détection des cartes nécessaire (peut etre tout a changer)
    // peut etre a mettre dans afficher_cartes
    
    cartes_alive = affichage_cartes();
    if(cartes_alive){
    automate_etat = CHECK_SD;
    }

    break;

  // VERIFICATION DE LA PRESENCE DE LA CARTE SD
  case CHECK_SD:
    // Besoin du file système
    if (sd == 1) {
      sd_here = 1;

    } else {

      sd_here = 0;
    }
    automate_etat = LECT_SD;

    break;

  // AFFICHAGE DE SI LA CARTE SD EST PRESENTE + DES FICHIERS EN INTERNES
  case LECT_SD:

    affichage_sd(sd_here);

    // CAS programme test sélectionné
    if (test) {
      automate_etat = PROG_TEST;
    }
    // CAS carte SD présente
    if (sd_here) {
      // CAS programme Match sélectionné
      if (match) {
        automate_etat = CHOIX_COULEUR;
      }
    }
    automate_etat = CHOIX_COULEUR;

    break;

  // LANCEMENT DU PROGRAMME TEST
  case PROG_TEST:
    break;

    // CHOIX CAMPS DU TERRAIN
  case CHOIX_COULEUR:
    /* Création d'une variable couleur tel que :
        "vert" == 0 "bleu" == 1*/
    bool couleur;
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

    num = choix_strategie();
    sprintf(buf, "%d", num);
    lcd_confirmation_menu(buf);
    check_num = ts_confirmation_menu();
    if (check_num) {
      automate_etat = ATTENTE_JACK;
    }
    break;

  case ATTENTE_JACK:   //CETTE FONCTION EST A INTEGRER DANS AUTO_MATCH
    jack = true; // a commenter
    aff_entete();
    lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"PRET AU", CENTER_MODE);
    lcd.DisplayStringAt(0, LINE(2), (uint8_t *)"DEMARAGE", CENTER_MODE);

    if (jack) {
      automate_etat = LECTURE_FICHIER;
    }
    break;

  case LECTURE_FICHIER: 
  
  while(1){
    aff_entete();
    lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"Fonctionnement", CENTER_MODE);
    lcd.DisplayStringAt(0, LINE(2), (uint8_t *)"en cours", CENTER_MODE);
    
    //FAIS UN AMONGUS EN DESSIN
    decoration();
  
    //auto_match(); //automate du controle du robot durant le match
  }
    // if (donnee_fichier == "") {
    //  automate_etat = PROBLEM_FICHIER;
    // }
    break;

  // DETECTION ERREUR
  case PROBLEM_FICHIER:

    lcd.DisplayStringAt(0, LINE(7), (uint8_t *)"Erreur", CENTER_MODE);

    break;
  }
  ts.GetState(&TS_State);
  wait_us(1000000);
}
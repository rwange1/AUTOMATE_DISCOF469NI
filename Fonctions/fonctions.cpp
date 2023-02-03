#include "all_includes.h"
#include "stm32469i_discovery_lcd.h"

#define WAIT_TIME_MS 500ms
#define MAIN_SLEEP_TIME 200 // ms

#define BC_COLOR                                                               \
  0xff151515 // correspond a une nuance de gris assez foncé qui va nous servir
             // d'arrièreplan

/*
|===============================================================================================|
| | |                                    INITIALISATION | | |
|===============================================================================================|
*/

//Y'en a pas lol

/*
|===============================================================================================|
| | |                                         BOUTONS | | |
|===============================================================================================|

 Fonctions pour créer des boutons
*/

// Exemple:
// lcd_bouton(10,10,100,40,LCD_COLOR_RED,0xffdd00dd,LCD)

/*====================================================================|
                        Visuelle des boutons
|====================================================================*/

void lcd_bouton(short marge_X, short marge_Y, short largeur_X, short hauteur_Y,
                int couleur_interne, int couleur_contour, int couleur_texte) {
  lcd.SetTextColor(couleur_interne);
  lcd.FillRect(marge_X, marge_Y, largeur_X, hauteur_Y);
  lcd.SetTextColor(couleur_contour);
  lcd.DrawRect(marge_X, marge_Y, largeur_X, hauteur_Y);
  // obligatoire pour avoir un fond unis
  lcd.SetBackColor(couleur_interne);
  lcd.SetTextColor(couleur_texte);
}

/*====================================================================|
                        Hitbox des boutons
|====================================================================*/

bool bouton_hitbox(short marge_X, short marge_Y, short largeur_X,
                   short hauteur_Y) {
  bool hitbox;

  ts.GetState(&TS_State);
  hitbox = ((TS_State.touchX[0] > marge_X) &&
            (TS_State.touchX[0] < (marge_X + largeur_X)) &&
            (TS_State.touchY[0] > marge_Y) &&
            (TS_State.touchY[0] < (marge_Y + hauteur_Y)));
  ThisThread::sleep_for(200ms); // pour éviter quelques bugs
  return hitbox;
}

/*====================================================================|
                        Définition complete
                    directe des boutons (a éviter)
|====================================================================*/

bool bouton(short marge_X, short marge_Y, short largeur_X, short hauteur_Y,
            int couleur_interne, int couleur_contour, int couleur_texte) {
  lcd_bouton(marge_X, marge_Y, largeur_X, hauteur_Y, couleur_interne,
             couleur_contour, couleur_texte);

  bool hitbox = bouton_hitbox(marge_X, marge_Y, largeur_X, hauteur_Y);
  return hitbox;
}

/*====================================================================|
                        Bouton "Continuer"
|====================================================================*/
void continuer() {

  lcd.DisplayStringAt(0, LINE(18), (uint8_t *)"Touchez pour continuer",
                      CENTER_MODE);

  ts.GetState(&TS_State);

  while (!bouton_hitbox(100, 100, 600, 240)) {
  }
}
/*
|===============================================================================================|
| | |                                         MENUS | | |
|===============================================================================================|
*/

/*====================================================================|
                    Visuelle du menu de confirmation
|====================================================================*/

void lcd_confirmation_menu(char *choix) {
  lcd.Clear(BC_COLOR);
  char buf[100];
  lcd_bouton(200, 25, 400, 100, LCD_COLOR_RED, LCD_COLOR_WHITE,
             LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(2), (uint8_t *)"Vous avez choisi", CENTER_MODE);
  sprintf(buf, "%s", choix);
  lcd.DisplayStringAt(0, LINE(3), (uint8_t *)buf, CENTER_MODE);
  lcd.DisplayStringAt(0, LINE(4), (uint8_t *)"Validez vous votre choix?",
                      CENTER_MODE);

  lcd_bouton(200, 160, 400, 50, 0xff575757, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(9), (uint8_t *)"Oui", CENTER_MODE);
  lcd_bouton(200, 280, 400, 50, 0xff575757, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(15), (uint8_t *)"Non", CENTER_MODE);
}

// Fonction de confirmation de sélection de ligne (configuré pour des choix
// afficher sur LINE(9) et LINE(15)

/*====================================================================|
                        Hitbox du menu de confirmation
|====================================================================*/

bool ts_confirmation_menu() {
  bool attente_choix = true;
  bool choix;
  while (attente_choix) {
    ts.GetState(&TS_State);
    if (TS_State.touchDetected) {
      // Création des zones tactiles de choix
      if (bouton_hitbox(200, 160, 400, 50)) {
        lcd.Clear(BC_COLOR);
        choix = 1;
        attente_choix = false;
      }

      // Détection sélection bas

      if (bouton_hitbox(200, 280, 400, 50)) {
        lcd.Clear(BC_COLOR);
        choix = 0;
        attente_choix = false;
      }
    }
  }
  // Temps d'attente nécessaire au bon fonctionnement du système
  return choix;
}

/*====================================================================|
                        Menu du choix d'équipe
|====================================================================*/

bool choix_equipe() {

  lcd.Clear(BC_COLOR);
  bool attente_choix = true;
  bool flag_equipe; //"vert" == 0; "bleu" == 1

  lcd_bouton(200, 20, 400, 50, LCD_COLOR_RED, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(2), (uint8_t *)"Choisissez une Equipe",
                      CENTER_MODE);

  lcd_bouton(200, 160, 400, 50, 0xff00688C, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(9), (uint8_t *)"Equipe Bleu", CENTER_MODE);

  lcd_bouton(200, 280, 400, 50, 0xff088C00, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(15), (uint8_t *)"Equipe Verte", CENTER_MODE);

  flag_equipe = ts_confirmation_menu();
  return flag_equipe;
}
/*
|===============================================================================================|
|                                           AFFICHAGE
|===============================================================================================|
*/

/*==========================================================================|
                            Affichage Init
|==========================================================================*/

void lcd_init() {

  bool milieu_touche = false;

  // Affichage des premiers lignes de texte de l'écran LCD
  lcd.Clear(BC_COLOR);

  // Allez voir la fonction associée
  lcd_bouton(250, 11, 300, 55, LCD_COLOR_RED, LCD_COLOR_WHITE, LCD_COLOR_WHITE);

  lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"START SD DEMO", CENTER_MODE);
  lcd.DisplayStringAt(0, LINE(2), (uint8_t *)"SD INIT", CENTER_MODE);

  // Création d'un carré tactile au milieu de l'écran
  // 0xff272727 --> Gris
  
  lcd_bouton(100, 160, 600, 100, 0xff63003C, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(10), (uint8_t *)"CRAC CACHAN", CENTER_MODE);

  lcd_bouton(200, 340, 400, 50, 0xff575757, LCD_COLOR_WHITE, LCD_COLOR_WHITE);

  continuer();

  lcd.Clear((uint32_t)BC_COLOR);
  lcd_bouton(100, 200, 600, 100, 0xff575757, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(12), (uint8_t *)"Automate lance", CENTER_MODE);

  /*  Fonction de debug
      while(1){
          ts.GetState(&TS_State);
          if ((TS_State.touchDetected) && (TS_State.touchX[0] > 700))
          {
            led1 = 1;
          }
          else
          {
            led1 = 0;
          }
      }
  */
}

/*====================================================================|
                          Affichage présence
                                cartes
|====================================================================*/

void affichage_cartes() {
  static short flags_cartes, flags_cartes_presentes = 0x0000;

  lcd.Clear(BC_COLOR);
  lcd_bouton(250, 11, 300, 55, LCD_COLOR_RED, LCD_COLOR_WHITE, LCD_COLOR_WHITE);

  lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"LISTE DES CARTES", CENTER_MODE);
  lcd.DisplayStringAt(0, LINE(2), (uint8_t *)"PRESENTES", CENTER_MODE);


  lcd_bouton(100, 100, 600, 300, 0xff575757, LCD_COLOR_WHITE, LCD_COLOR_WHITE);

  int i = 0; // Permet d'incrémenté la ligne a afficher en fonction des cartes
  if (flags_cartes_presentes & CARTE_MOTEUR) {
    lcd.DisplayStringAt(0, LINE(7 + i), (uint8_t *)"carte moteur", CENTER_MODE);
    i += 1;
  }
  if (flags_cartes_presentes & NUCLEO_GAUCHE) {
    lcd.DisplayStringAt(0, LINE(7 + i), (uint8_t *)"carte nucléo gauche",
                        CENTER_MODE);
    i += 1;
  }
  if (flags_cartes & NUCLEO_DROIT) {
    lcd.DisplayStringAt(0, LINE(7 + i), (uint8_t *)"carte nucléo droite",
                        CENTER_MODE);
    i += 1;
  }
  if (flags_cartes & ANTI_COLLISION) {
    lcd.DisplayStringAt(0, LINE(7 + i), (uint8_t *)"carte anti-collision",
                        CENTER_MODE);
    i += 1;
  }
  if (flags_cartes & HERCULEX_1) {
    lcd.DisplayStringAt(0, LINE(7 + i), (uint8_t *)"herkulex 1", CENTER_MODE);
    i += 1;
  }
  if (flags_cartes & HERCULEX_2) {
    lcd.DisplayStringAt(0, LINE(7 + i), (uint8_t *)"herkulex 2", CENTER_MODE);
    i += 1;
  }

  continuer();
}

/*====================================================================|
                          Affichage présence
                                carte SD
|====================================================================*/

void affichage_sd(bool sd_here) {
  lcd.Clear(BC_COLOR);
  if(sd_here) {
    lcd_bouton(100, 200, 600, 100, 0xff575757, LCD_COLOR_WHITE,
               LCD_COLOR_WHITE);
    lcd.DisplayStringAt(0, LINE(12), (uint8_t *)"Carte SD presente",
                        CENTER_MODE);
  } else {
    lcd_bouton(100, 200, 600, 100, 0xff575757, LCD_COLOR_WHITE,
    
               LCD_COLOR_WHITE);
    lcd.DisplayStringAt(0, LINE(12), (uint8_t *)"Aucune carte SD", CENTER_MODE);
  }

  lcd_bouton(100, 200, 600, 100, 0xff575757, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  continuer();
}

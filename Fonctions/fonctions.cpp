#include "all_includes.h"

#define BC_COLOR                                                               \
  0xff151515 // correspond a une nuance de gris assez foncé qui va nous servir
             // d'arrièreplan

// CAN FIFO

// A modifier si possible
signed char FIFO_lecture = 0;
unsigned char FIFO_ecriture = 0;

/*
|===============================================================================================|
| | |                                    INITIALISATION | | |
|===============================================================================================|
*/

// Y'en a pas lol

/*
|===============================================================================================|
| | |                               FONCTIONS LIEES AU CAN | | |
|===============================================================================================|
*/

int check_id(int id) {
  int CAN_id;

  CANMessage msgTx = CANMessage();
  msgTx.id = id;
  msgTx.len = 0;
  busCAN.write(msgTx);
  wait_us(100);
  // canProcessRx();
  CAN_id = Rx_Msg.id;
  printf("ID: %04x\n", CAN_id);

  return CAN_id;
}

void SendAck(unsigned short id, unsigned short from) {
  CANMessage msgTx = CANMessage();
  msgTx.id = id;
  msgTx.len = 2;
  //    msgTx.format=CANStandard;
  msgTx.type = CANData;
  // from sur 2 octets
  msgTx.data[0] = (unsigned char)from;
  msgTx.data[1] = (unsigned char)(from >> 8);

  busCAN.write(msgTx);
}

// A expliquer
void canProcessRx() {
  // Taille du Fifo en fonction du temps
  static signed char FIFO_occupation = 0, FIFO_max_occupation = 0;

  //(Je comprend pas pk)
  FIFO_occupation = FIFO_ecriture - FIFO_lecture;

  if (FIFO_occupation < 0)
    FIFO_occupation = FIFO_occupation + SIZE_FIFO;

  // Si la taille max ayant été occupé est dépassé cette valeur change (A quoi
  // ça sert???)
  if (FIFO_max_occupation < FIFO_occupation) {
    FIFO_max_occupation = FIFO_occupation;
    // SendRawId(
  }

  // si la taille du message n'est pas nulle
  if (FIFO_occupation != 0) {
    // CAN_id = Rx_Msg[SIZE_FIFO].id;
    FIFO_lecture = (FIFO_lecture + 1) % SIZE_FIFO;
  }
}

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
  if (hitbox) {
    ThisThread::sleep_for(100ms); // pour éviter quelques bugs
  }
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

/*==========================================================================|
                    Affichage Boutons Particuliés
|==========================================================================*/
/*A mettre idéalement dans une classe */

// Carré en haut de l'écran
void aff_entete() {
  lcd_bouton(200, 11, 400, 70, LCD_COLOR_RED, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
}

void continuer(bool affiche_bouton) {
  bool end = false;
  if (affiche_bouton) {
    lcd_bouton(200, 380, 400, 70, 0xff575757, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  }
  lcd.DisplayStringAt(0, LINE(17), (uint8_t *)"Touchez pour continuer",
                      CENTER_MODE);
  // Le bouton "continuer" n'est pas forcément dans une case (question
  // d'estétisme)

  while (!end) {
    // SI mis dans un thread a par, toute les fonctions bloquantes ne le serons
    // plus
    ts.GetState(&TS_State);

    if (TS_State.touchDetected) {
      if (bouton_hitbox(100, 100, 600, 280)) {
        end = true;
      }
    }
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
  aff_entete();
  lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"Vous avez choisi", CENTER_MODE);
  sprintf(buf, "%s", choix);
  lcd.DisplayStringAt(0, LINE(2), (uint8_t *)buf, CENTER_MODE);
  lcd.SetBackColor(BC_COLOR);
  lcd.DisplayStringAt(0, LINE(4), (uint8_t *)"Validez vous votre choix?",
                      CENTER_MODE);
  lcd_bouton(200, 170, 400, 70, 0xff575757, LCD_COLOR_WHITE, LCD_COLOR_WHITE);

  lcd.DisplayStringAt(0, LINE(8), (uint8_t *)"Oui", CENTER_MODE);
  lcd_bouton(200, 310, 400, 70, 0xff575757, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(14), (uint8_t *)"Non", CENTER_MODE);
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
      if (bouton_hitbox(200, 170, 400, 70)) {
        lcd.Clear(BC_COLOR);
        choix = 1;
        attente_choix = false;
      }

      // Détection sélection bas

      if (bouton_hitbox(200, 310, 400, 70)) {
        lcd.Clear(BC_COLOR);
        choix = 0;
        attente_choix = false;
      }
    }
  }
  wait_us(200000);
  // Temps d'attente nécessaire au bon fonctionnement du système
  return choix;
}

/*====================================================================|
                        Menu du choix d'équipe
|====================================================================*/

bool choix_equipe() {

  lcd.Clear(BC_COLOR);
  bool flag_equipe; //"vert" == 0; "bleu" == 1

  aff_entete();
  lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"Choisissez une equipe",
                      CENTER_MODE);
  lcd.DisplayStringAt(0, LINE(2), (uint8_t *)"pour le match", CENTER_MODE);
  lcd_bouton(200, 170, 400, 70, 0xff00688C, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(8), (uint8_t *)"Equipe Bleu", CENTER_MODE);

  lcd_bouton(200, 310, 400, 70, 0xff088C00, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(14), (uint8_t *)"Equipe Verte", CENTER_MODE);

  flag_equipe = ts_confirmation_menu();
  return flag_equipe;
}

/*====================================================================|
                      Menu du choix de stratégie
|====================================================================*/

char choix_strategie() {
  char buf[30];
  char numero = 1;
  char flag_strat;
  bool attente_choix = true;

  lcd.Clear(BC_COLOR);

  aff_entete();
  lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"Selectionnez une ", CENTER_MODE);
  lcd.DisplayStringAt(0, LINE(2), (uint8_t *)"strategie", CENTER_MODE);

  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 2; i++) {

      lcd_bouton(25 + 380 * j, 130 + 140 * i /*marge qui s'ajuste*/, 300, 100,
                 0xff00688C, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
      sprintf(buf, "- strat %d", numero);
      lcd.DisplayStringAt(
          50 + 380 * j, LINE(7 + 6 * i), (uint8_t *)buf,
          LEFT_MODE); // surement les noms de programme plus tard (quand le
                      // file système fonctionnera)
      numero++;
    }
  }

  while (attente_choix) {
    numero = 0;
    ts.GetState(&TS_State);
    for (int j = 0; j < 2; j++) {
      for (int i = 0; i < 2; i++) {
        if (TS_State.touchDetected) {

          numero++;

          // Création des zones tactiles de choix
          if (bouton_hitbox(25 + 380 * j, 130 + 140 * i, 300, 100)) {
            flag_strat = numero;
            ThisThread::sleep_for(200ms);
            attente_choix = false;
          }
        }
      }
    }
  }
  return flag_strat;
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

  lcd.SetFont(&Font24);
  bool milieu_touche = false;
  // Affichage des premiers lignes de texte de l'écran LCD
  lcd.Clear(BC_COLOR);

  aff_entete();

  lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"START ECRAN LCD", CENTER_MODE);
  lcd.DisplayStringAt(0, LINE(2), (uint8_t *)" -- CRAC --", CENTER_MODE);

  ts.GetState(&TS_State);

  lcd.Clear(BC_COLOR);

  // Allez voir la fonction associée
  aff_entete();

  lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"ART CACHAN", CENTER_MODE);
  lcd.DisplayStringAt(0, LINE(2), (uint8_t *)"AMOGUS", CENTER_MODE);

  // Création d'un carré tactile au milieu de l'écran
  // 0xff272727 --> Gris

  lcd_bouton(100, 140, 600, 200, 0xff63003C, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(10), (uint8_t *)"CRAC CACHAN", CENTER_MODE);

  // Dans une case
  continuer(1);

  lcd.Clear((uint32_t)BC_COLOR);
  lcd_bouton(100, 200, 600, 100, 0xff575757, LCD_COLOR_WHITE, LCD_COLOR_WHITE);
  lcd.DisplayStringAt(0, LINE(10), (uint8_t *)"Automate lance", CENTER_MODE);

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

bool affichage_cartes() {
  bool skip = true; // passe la vérification des cartes
  int id_card = 0;
  lcd.Clear(BC_COLOR);
  aff_entete();

  lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"LISTE DES CARTES", CENTER_MODE);
  lcd.DisplayStringAt(0, LINE(2), (uint8_t *)"PRESENTES", CENTER_MODE);

  lcd_bouton(100, 100, 600, 350, 0xff575757, LCD_COLOR_WHITE, LCD_COLOR_WHITE);

  int l = 0; // Permet d'incrémenté la ligne a afficher en fonction du
             // nombre de cartes
  int check = 0;
  // ID: 0x61 - 0x6
  for (int i = 0; i < CAN_MSG_ARRAY_SIZE; i++) {

    id_card = can_msg_array[i].id;
    // id_card = check_id(CHECK_MOTEUR);
    printf("ID CARTE: %04x\n", id_card);

    if ((id_card == ALIVE_MOTEUR) & !(check & 0x01)) {
      lcd.DisplayStringAt(0, LINE(5 + l), (uint8_t *)"carte moteur",
                          CENTER_MODE);
      check = check + 0x01;
      l += 1;
    }
    ThisThread::sleep_for(10ms);
    // id_card = check_id(CHECK_NUCLEO_GAUCHE);
    if ((id_card == ALIVE_NUCLEO_GAUCHE) & !(check & 0x02)) {
      lcd.DisplayStringAt(0, LINE(5 + l), (uint8_t *)"carte nucleo gauche",
                          CENTER_MODE);
      check = check + 0x02;
      l += 1;
    }
    ThisThread::sleep_for(10ms);
    // id_card = check_id(CHECK_NUCLEO_DROIT);

    if ((id_card == ALIVE_NUCLEO_DROIT) & !(check & 0x04)) {
      lcd.DisplayStringAt(0, LINE(5 + l), (uint8_t *)"carte nucleo droite",
                          CENTER_MODE);
      check = check + 0x04;

      l += 1;
    }
    ThisThread::sleep_for(10ms);

    // id_card = check_id(CHECK_ASCENSEUR);

    if ((id_card == ALIVE_ASCENSEUR) & !(check & 0x08)) {
      lcd.DisplayStringAt(0, LINE(5 + l), (uint8_t *)"carte anti-collision",
                          CENTER_MODE);
      check = check + 0x08;

      l += 1;
    }
    ThisThread::sleep_for(10ms);

    // id_card = check_id(CHECK_HERKULEX_1);

    if ((id_card == ALIVE_HERKULEX_1) & !(check & 0x10)) {
      lcd.DisplayStringAt(0, LINE(5 + l), (uint8_t *)"herkulex 1", CENTER_MODE);
      check = check + 0x10;

      l += 1;
    }
    // id_card = check_id(CHECK_HERKULEX_2);

    if ((id_card == ALIVE_HERKULEX_2) & !(check & 0x20)) {
      lcd.DisplayStringAt(0, LINE(5 + l), (uint8_t *)"herkulex 2", CENTER_MODE);
      check = check + 0x20;
      l += 1;
    }
    if (check == 0x3F) {
      break;
    }
    printf("Check: %X", check);
  }

  // aucune intrémentation de i --> aucune carte détexté
  if (l == 0) {
    lcd.DisplayStringAt(0, LINE(8), (uint8_t *)"aucune carte connectee",
                        CENTER_MODE);
  }
  printf("Nombre de carte connecté: %d", l);

  // Hors d'une case
  continuer(0);

  if (l == 6) // Affichage de toute les cartes
  {
    return true;
  }
  if (skip) {
    return true;

  } else {
    return false;
  }
}

/*====================================================================|
                          Affichage présence
                                carte SD
|====================================================================*/

void affichage_sd(bool sd_here) {
  lcd.Clear(BC_COLOR);
  if (sd_here) {
    lcd_bouton(100, 190, 600, 110, 0xff575757, LCD_COLOR_WHITE,
               LCD_COLOR_WHITE);
    lcd.DisplayStringAt(0, LINE(10), (uint8_t *)"Carte SD presente",
                        CENTER_MODE);
  } else {
    lcd_bouton(100, 190, 600, 110, 0xff575757, LCD_COLOR_WHITE,

               LCD_COLOR_WHITE);
    lcd.DisplayStringAt(0, LINE(10), (uint8_t *)"Aucune carte SD", CENTER_MODE);
  }
  // Dans une case
  continuer(1);
}

/*====================================================================|
                                DECO
|====================================================================*/

// Deco afficher sur l'IHM pendant le match
void decoration() {
  unsigned int test;
  bool deco = false;
  while (1) {
    if (!deco) {
      amogus();
      //  deco = true;
      ThisThread::sleep_for(33ms);
    }
  }
}

void amogus() {
  static int i;
  lcd.Clear(BC_COLOR);

  lcd.SetTextColor(0xFFFF0000);
  lcd.FillRect((275 + i) % 800, 125, 250, 250);
  lcd.FillRect((275 + i) % 800, 275, 100, 150);
  lcd.FillRect((425 + i) % 800, 275, 100, 150);
  lcd.FillRect((475 + i) % 800, 175, 100, 175);

  lcd.SetTextColor(LCD_COLOR_DARKRED);
  lcd.FillRect((325 + i) % 800, 400, 50, 25);
  lcd.FillRect((375 + i) % 800, 275, 100, 25);
  lcd.FillRect((400 + i) % 800, 225, 75, 25);
  lcd.FillRect((450 + i) % 800, 400, 75, 25);
  lcd.FillRect((525 + i) % 800, 325, 50, 25);

  lcd.SetTextColor(LCD_COLOR_WHITE);
  lcd.FillRect((225 + i) % 800, 200, 250, 100);

  lcd.SetTextColor(LCD_COLOR_LIGHTGRAY);
  lcd.FillRect((350 + i) % 800, 275, 125, 25);

  lcd.SetTextColor(LCD_COLOR_LIGHTGRAY);
  lcd.FillRect((250 + i) % 800, 225, 50, 25);
  i = i + 770;
  if (i == 800) {
    i = 0;
  }
}
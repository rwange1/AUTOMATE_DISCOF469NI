#include "bouton.h"
/*

void Bouton::Visuel(short marge_X, short marge_Y, short largeur, short hauteur,
            int couleur_interne, int couleur_contour, int couleur_texte) {
  lcd.SetTextColor(couleur_interne);
  lcd.FillRect(marge_X, marge_Y, largeur, hauteur);
  lcd.SetTextColor(couleur_contour);
  lcd.DrawRect(marge_X, marge_Y, largeur, hauteur);
  // obligatoire pour avoir un fond unis
  lcd.SetBackColor(couleur_interne);
  lcd.SetTextColor(couleur_texte);
}

bool Bouton::Hitbox(short marge_X, short marge_Y, short largeur,
                    short hauteur) {
  bool hitbox;

  ts.GetState(&TS_State);
  hitbox = ((TS_State.touchX[0] > marge_X) &&
            (TS_State.touchX[0] < (marge_X + largeur)) &&
            (TS_State.touchY[0] > marge_Y) &&
            (TS_State.touchY[0] < (marge_Y + hauteur)));
  ThisThread::sleep_for(100ms); // pour éviter quelques bugs
  return hitbox;
}
*/
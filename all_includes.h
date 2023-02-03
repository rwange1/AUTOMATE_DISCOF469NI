#ifndef ALL_INCLUDES_H
#define ALL_INCLUDES_H

#include "mbed.h"
#include "LCD_DISCO_F469NI.h"
#include "TS_DISCO_F469NI.h"
#include "rtos.h"

// #include "automate.h"
// #include "fonctions.h"

#include "automate.h"
#include "fonctions.h"
#include <cstring>
#include "bouton.h"

#define CARTE_MOTEUR 0x02
#define NUCLEO_GAUCHE 0x04
#define NUCLEO_DROIT 0x08
#define ANTI_COLLISION 0x10
#define HERCULEX_1 0x20
#define HERCULEX_2 0x40

//Initialisé dans Le Main
extern LCD_DISCO_F469NI lcd;
extern TS_DISCO_F469NI ts;
extern TS_StateTypeDef TS_State;



#endif
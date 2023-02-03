/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */


//Pour voir comment fonctionne l'automate : Voir les fichiers automate.cpp et automate.h
#include "all_includes.h"

#define WAIT_TIME_MS 500ms
#define MAIN_SLEEP_TIME 200 // ms

DigitalOut led1(LED1);

//Initialisation du LCD
LCD_DISCO_F469NI lcd;
TS_DISCO_F469NI ts;
TS_StateTypeDef TS_State;

int main()
{
    while (true)
    {

        automate();
        ThisThread::sleep_for(WAIT_TIME_MS);
    }
}

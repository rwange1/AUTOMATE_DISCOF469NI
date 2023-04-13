/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

// Pour voir comment fonctionne l'automate : Voir les fichiers automate.cpp et
//  automate.h
#include "mbed.h"

#include "all_includes.h"



// #define WAIT_TIME_MS 500ms
// #define MAIN_SLEEP_TIME 200 // ms

// DigitalOut led1(LED1);

/* Définition du LCD */
LCD_DISCO_F469NI lcd;
TS_DISCO_F469NI ts;
TS_StateTypeDef TS_State;

// CAN DES PIN CN12
CAN busCAN(PB_5, PB_13, 1000000);
CANMessage Rx_Msg;
CANMessage rxMsg;
CANMessage
    can_msg_array[CAN_MSG_ARRAY_SIZE]; // Tableau pour stocker les messages CAN
int index = 0; // Index pour stocker les messages dans le tableau

/*----------------------
         ISR CAN
 -----------------------*/

void CAN_ISR() {
  if (busCAN.read(Rx_Msg)) // Si un message est reçu
  {
    if (index < CAN_MSG_ARRAY_SIZE) // Si le tableau n'est pas plein
    {
      can_msg_array[index] = Rx_Msg; // Stocker le message dans le tableau
      index++;                       // Augmenter l'index
    } else {
      // Si le tableau est plein, effacer le premier message et décaler tous les
      // autres vers la gauche
      for (int i = 0; i < CAN_MSG_ARRAY_SIZE - 1; i++) {
        can_msg_array[i] = can_msg_array[i + 1];
      }

      can_msg_array[CAN_MSG_ARRAY_SIZE - 1] =
          Rx_Msg; // Stocker le nouveau message à la fin du tableau
    }
  }
}

/*----------------------
           MAIN
 -----------------------*/

int main() {
  busCAN.attach(&CAN_ISR); // IrqType::RxIrq

 

  // Ouverture du fichier exemple.txt qui doit être présent sur la
  // carte SD
  File fichier;
  if (fichier.open(&m_fs, "exemple.txt")) {
    printf("Impossible d'ouvrir le fichier !\n");
    while (1)
      ;
  }
  while (1) {
    char c;
    if (fichier.read(&c, 1) != 1)
      break;
    printf("%c", c);
  }
  fichier.close();

  while (true) {

    automate_visuel();

    // if(busCAN.read(rxMsg)){
    //     printf("ID : %d\n", rxMsg.id);
    // }
    wait_us(10000); // Attendre un peu pour éviter de saturer le microcontrôleur
  }
}

#ifndef ALL_INCLUDES_H
#define ALL_INCLUDES_H

#include "mbed.h"
#include "LCD_DISCO_F469NI.h"
#include "TS_DISCO_F469NI.h"
#include "rtos.h"
#include "fonts.h"
#include "Thread.h"
#include "stm32469i_discovery_lcd.h"

//#include "SDFileSystem.h"

#include "automate_visu.h"
#include "auto_match.h"
#include "fonctions.h"
#include "instruction.h"
#include <FATFileSystem.h>
#include <SDIOBlockDevice.h>
#include "lecture_repertoire.h"
#include <cstring>
#include "bouton.h"

#include <stdio.h>
#include <stdlib.h>

#include "ident_crac.h"

#define CAN_MSG_ARRAY_SIZE 50
#define SIZE_FIFO 50

//Initialisé dans Le Main
extern LCD_DISCO_F469NI lcd;
extern TS_DISCO_F469NI ts;
extern TS_StateTypeDef TS_State;
extern FATFileSystem m_fs;


extern CAN busCAN;
extern CANMessage Rx_Msg;
extern CANMessage can_msg_array[CAN_MSG_ARRAY_SIZE]; // Tableau pour stocker les messages CAN
#endif
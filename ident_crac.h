/*----------------------------------------/
/---------* CRAC IUT DE CACHAN *----------/
/----------------------------------------*/

/*Liste complète des Identifiant utilisé par le CRAC en 2023 */

#ifndef CRAC_IDENTH
#define CRAC_IDENTH

//---------------------------------//
/*  PARTIE COMMUNE A CHAQUE ANNEE  */
//---------------------------------//

#define GLOBAL_END 0x002
#define GLOBAL_START 0x003
#define GLOBAL_STOP 0x004

#define GLOBAL_END_INIT_POSITION 0x005 // Position du robot avant le départ
#define GLOBAL_JACK 0x006
#define ACK_JACK 0x007
#define RECALAGE_START 0x008

#define ASSERVISSEMENT_STOP 0x001 // Stop moteur

//---------------------------------//
/*         ASSERVISSEMENT          */
//---------------------------------//

#define SCAN_REQUEST 0x020
#define POSITION_ROBOT 0x026
#define POSITION_ROBOT_ALLIE 0x027
#define POSITION_ENNEMIE 0x028


//---------------------------------//
/*              RESET              */
//---------------------------------//

#define RESET_LIDAR 0x030
#define RESET_MOTEUR 0x031
// #define RESET_IHM 0x032
#define RESET_ASCENSEUR 0x33
#define RESET_HERKULEX_1 0x034
#define RESET_HERKULEX_2 0x035
#define RESET_NUCLEO_GAUCHE 0x036
#define RESET_NUCLEO_DROIT 0x037
#define RESET_ANTI_COLLISION 0x038

#define RESET_STRAT 0x03A

//---------------------------------//
/*              CHECKS             */
//---------------------------------//
#define CHECK_LIDAR 0x060
#define CHECK_MOTEUR 0x061
// #define CHECK_IHM 0x062
#define CHECK_ASCENSEUR 0x63
#define CHECK_HERKULEX_1 0x064
#define CHECK_HERKULEX_2 0x065
#define CHECK_NUCLEO_GAUCHE 0x066
#define CHECK_NUCLEO_DROIT 0x067
#define CHECK_ANTI_COLLISION 0x068


//---------------------------------//
/*              ALIVES             */
//---------------------------------//

#define ALIVE_LIDAR 0x070
#define ALIVE_MOTEUR 0x071
// #define ALIVE_IHM 0x072
#define ALIVE_ASCENSEUR 0x073
#define ALIVE_HERKULEX_1 0x074
#define ALIVE_HERKULEX_2 0x075
#define ALIVE_NUCLEO_GAUCHE 0x076
#define ALIVE_NUCLEO_DROIT 0x077
#define ALIVE_ANTI_COLLISION 0x078


//---------------------------------//
/*           INSTRUCTIONS          */
//---------------------------------//

/* --- ACKNOWLEDGE --- */

#define ACKNOWLEDGE_LIDAR 0x100
#define ACKNOWLEDGE_MOTEUR 0x101
// #define ACKNOWLEDGE_IHM 0x0102
#define ACKNOWLEDGE_ASCENSEUR 0x103
#define ACKNOWLEDGE_HERKULEX_1 0x104
#define ACKNOWLEDGE_HERKULEX_2 0x105
#define ACKNOWLEDGE_NUCLEO_GAUCHE 0x106
#define ACKNOWLEDGE_NUCLEO_DROIT 0x107
#define ACKNOWLEDGE_ANTI_COLLISION 0x0108

#define ACKNOWLEDGE_STRAT 0x10A


/* --- ASCENCEUR --- */

#define ASCENCEUR_ETAGE 0x200 // DATA --> Etage 2: 0x02, Etage 4: 0x04
#define ASCENCEUR_PINCE 0x201 // DATA --> Attraper : 0x01, Lacher : 0x00
#define INSTRUCTION_END_ASCENSEUR 00x20F

/* --- FIN D'INSTRUCTIONS --- */

#define INSTRUCTION_END_LIDAR 0x110
#define INSTRUCTION_END_MOTEUR 0x111
// #define INSTRUCTION_END_IHM 0x112
#define INSTRUCTION_END_HERKULEX_1 0x114
#define INSTRUCTION_HERKULEX_2 0x115

//????
#define ACK_FIN_ACTION 0x116



//---------------------------------//
/*             ERREURS             */
//---------------------------------//

#define ERROR_OVERFLOW_BALISE 0x040
#define ERROR_OVERFLOW_MOTEUR 0x041
//#define ERROR_OVERFLOW_IHM 0x042
#define ERROR_OVERFLOW_STRAT 0x043

#define ERROR_BALISE 0x780
#define ERROR_MOTEUR 0x781
//#define ERROR_IHM 0x782
#define ERROR_ASCENSEUR 0x783
#define ERROR_HERKULEX_1 0x784
#define ERROR_HERKULEX_2 0x785
#define ERROR_NUCLEO_GAUCHE 0x786
#define ERROR_NUCLEO_DROIT 0x787
#define ERROR_ANTI_COLLISION 0x787

#define ERROR_STRATEGIE 0x78A

#endif
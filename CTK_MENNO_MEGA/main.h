//Endereço 0x00 da EEPROM armazena quantidade de ID cadastrados
//Endereço 0x01 da EEPROM armazena endereço do Master ID
#define pMOD 43
#define pINV 45
#define pIO1 41
#define pIO2 39
#define pG2 18
#define pG1 19

#define ONLINE 1
#define OFFLINE 0
//MACROS DE CONFIGURAÇÃO DA CATRACA
//As macros abaixo liberam o sentido horario ou o sentido antihorario
//#define LIBERA_GIRO_HORARIO
//#define LIBERA_GIRO_ANTIHORARIO

//A macro abaixo inverter a detecção de giro dos pinos G1 e G2.
#define INVERTER_DETECCAO_GIRO

//A macro abaixo inverte o acionamento das solenoides
//Deve ser usada quando a catraca a placa aciona a solenoide mas a catraca não bloqueia
//#define INVERTER_ACIONAMENTO
 
#include "tone.h"
#include "nfc_rfid.h"
#include "nfc_lcd.h"
#include "nfc_server.h"
#include "nfc_catraca.h"


catraca ctk(pMOD, pINV, pG1, pG2, pIO1, pIO2);

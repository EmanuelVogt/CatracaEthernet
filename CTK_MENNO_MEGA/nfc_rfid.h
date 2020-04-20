
#include <EEPROM.h>
#include <deprecated.h>
#include <MFRC522.h>
#include <require_cpp11.h>

#define SS_PIN 49
#define RST_PIN 48
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define masterID "25 95 B4 A5"

uint8_t storedCard[4];   // Armazena um ID lido da EEPROM
uint8_t readCard[4];     // Armazena o ID lido da modulo RFID
uint8_t masterCard[4];   // Armazena ID Master lido da EEPROM
#define masterAddress 4090 // (62*4+2) == 0xFA Endereco do ID Master
#define masterNumber 1021 //Numero da tag master cadastrada
#define numMaxID  1020  //Numero maximo de tags que podem ser cadastrados
#define sizeEEPROM 4096
uint8_t successRead;    // Número inteiro variável a ser mantido se tivermos êxito na leitura do Reader


void print_variaveis() {
  Serial.print("STORAGE: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(storedCard[i], HEX);
    Serial.print(' ');
  }
  Serial.println(' ');

  Serial.print("READ: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(readCard[i], HEX);
    Serial.print(' ');
  }
  Serial.println(' ');

  Serial.print("MASTER: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(masterCard[i], HEX);
    Serial.print(' ');
  }
  Serial.println(' ');
}

//////////////////////////////////////Faz a leitura de um cartão e armazena em readCard ///////////////////////////////////
int getID() {
  // Preparando-se para ler RFID
  if ( mfrc522.PICC_IsNewCardPresent()) { //Se um novo PICCs for colocado no leitor RFID.... continua
    if ( mfrc522.PICC_ReadCardSerial()) {   //Como um PICCs colocado, obtén-se o ID serial e continua
      // Existem PICCs da Mifare que tem ID de 4 ou 7 bytes.
      // Devemos assumir que todos os PICCs tenham 4 bytes, pois o algoritmo foi feito para isso.
      // Abiblioteca até suporta PICCs de 7 bytes, porém com modificações.
      Serial.print(F("ID lido: "));
      for ( int i = 0; i < 4; i++) {  //
        readCard[i] = mfrc522.uid.uidByte[i];
        Serial.print(readCard[i], HEX);
        Serial.print(' ');
      }
      Serial.println();
      mfrc522.PICC_HaltA(); // Para de ler
      return 1;
    }
    else return 0;
  }
  else return 0;
}

void EEPROM_scanner () {
  Serial.println("-------EEPROM-----------");
  for (int b = 0; b < sizeEEPROM; b++) {
    Serial.print(b, DEC);
    Serial.print(" = ");
    Serial.println(EEPROM.read(b), HEX);

  }
}

//////////////////////////////////////Compara dois IDs  // PARÂMETROS> ID a (4bytes), ID b (4bytes)
bool checkTwo ( byte a[], byte b[] ) {
  for ( int k = 0; k < 4; k++ ) {   // Loop 4 vezes
    if ( a[k] != b[k] ) {     // SE a! = B então falso, porque: um falha, todos falham
      return false;
    }
  }
  return true;
}


//////////////////////////////////////Checka se o ID é Master   ///////////////////////////////////
bool isMaster( byte test[] ) {
  return checkTwo(test, masterCard);
}
//////////////////////////////////////Escreve 0 em toda EEPROM ///////////////////////////////////
void EEPROM_clear() { 
  for (int x = 0; x < sizeEEPROM; x++) EEPROM.write(x, 0); // caso contrário, escreva 0 para limpar, são necessários 3,3 mS
  Serial.println(F("EEPROM apagada"));
}

void EEPROM_set () {
  Serial.println("-------EEPROM-----------");
  for (int b = 0; b < sizeEEPROM; b++) {
    EEPROM.write(b, 255);
  }
  Serial.println("EEPROM Setada!");
}

//////////////////////////////////////Armazena em storedCard um ID da EEPROM // PARÂMETRO> número do ID a ser lido
void readID( int number ) {
  int start = (number * 4 ) + 6;    // Descobrir a posição inicial na EEPROM
  for ( int i = 0; i < 4; i++ ) {     // Faça um loop 4 vezes para obter os 4 bytes
    storedCard[i] = EEPROM.read(start + i);   // Atribuir valores lidos da EEPROM à matriz
  }
}

//////////////////////////////////////Adiciona ID na EEPROM   // PARÂMETRO> ID a ser escrito (4 bytes)
void writeID( byte a[] ) {
  int num = EEPROM.read(0);     // Obtenha o número de espaços já usados, a posição 0 armazena o número de cartões de cadasgrados
  int start = ( num * 4 ) + 6;  // Descobrir onde o próximo mensagem começa
  num++;                // Incrementa um no contador
  EEPROM.write( 0, num );     //Escreve a nova contagem de cadastros
  for ( int j = 0; j < 4; j++ ) {   // Loop 4 vezes
    EEPROM.write( start + j, a[j] );  // Escreva os valores na matriz da EEPROM na posição correta

  }
  Serial.println(F("Registro de identificação adicionado com êxito à EEPROM"));
}

//////////////////////////////////////Retorna número do ID  // PARÂMETRO> ID a ser encontrado (4 bytes)
int findIDSLOT() {
  char acertos = 0;
  int i;
  for (i = 1; i < numMaxID; i++ ) {    // Loop once for each EEPROM entry
    readID(i);
    for ( int k = 0; k < 4; k++ ) {   // Loop 4 vezes
      if ( readCard[k] == storedCard[k] )    // SE a! = B então falso, porque: um falha, todos falham
        acertos ++;
    }
    if (acertos == 4 ) return (i);
    acertos = 0;
  }
  return false;
}

//////////////////////////////////////Retorna true se ID existe na EEPROM  // PARÂMETRO> ID a ser comparado (4 bytes)
bool findID( byte find[] ) {
  int count = EEPROM.read(0);     // Read the first Byte of EEPROM that
  for ( int i = 1; i < count; i++ ) {    // Loop once for each EEPROM entry
    readID(i);          // Read an ID from EEPROM, it is stored in storedCard[4]
    if ( checkTwo( find, storedCard ) ) {   // Check to see if the storedCard read from EEPROM
      return true;
    }
    else return false;
  }
}
//////////////////////////////////////Remove ID da EEPROM   // PARÂMETRO> ID a ser removido (4 bytes)
void deleteID( byte a[] ) {

  int num = EEPROM.read(0);   // Leia o primeiro byte da EEPROM que armazena o número de cartões cadastrados
  int slot = findIDSLOT( );   // Número do cartão a ser excluído

  int start = (slot * 4) + 2; // Endereço do ID a ser excluído
  //uint8_t looping = ((num - slot) * 4);    // Número loop para chegar no último endereço EEPROM
  int j;
  Serial.print("slot: ");
  Serial.println(slot, DEC);
  num--;      //Decrementa um da variavel
  EEPROM.write( 0, num );   // Escreve na EEPROM o novo número de ID cadastrados

  for ( j = 0; j < (246 - start); j++ ) {         // loop para reorganizar EEPROM
    EEPROM.write(start + j, EEPROM.read(start + 4 + j));   // Desloca ID 4 endereços antes na EEPROM
  }
  for ( int k = 0; k < 4; k++ ) {         // loop para zerar os 4 últimos endereços EEPROM
    EEPROM.write( start + j + k, 0);
  }
  //successDelete();
  Serial.println(F("Registro de identificação removido com êxito da EEPROM"));

}
//////////////////////////////////////Função para gravar master ID na EEPROM
void cadastraMaster() {
  if (EEPROM.read(0) == 255) { //Verifica se a EEPROM ainda esta virgem
    Serial.println(F("Aproxime o card ou tag Master!"));
    int cont = 0;
    do {
      successRead = getID();            // define successRead para 1 quando lemos do leitor, caso contrário 0
    }
    while ((!successRead));

    if (successRead) {
      EEPROM_clear();
      for (int i = 0; i < 4; i++) masterCard[i] = readCard[i]; //Copia o ID lido para a varialvel masterCard
      for (int j = 0; j < 4; j++) EEPROM.write(masterAddress + j,  masterCard[j] ); // Escreva Master ID na EEPROM
      EEPROM.write(0x01, masterAddress); //Escreve no segundo endereco da EEPROM o endereco da masterID
      Serial.println(F("Master adicionado com êxito à EEPROM"));

    }
  }
  else {
    Serial.print("MasterCard: ");
    for (int i = 0; i < 4; i++) {
      readID(masterNumber);
      masterCard[i] = storedCard[i];
      Serial.print(masterCard[i]);

    }
    Serial.println( );
  }
}




char verificaAcesso () {
  char acertos = 0;
  for ( int i = 1; i < numMaxID; i++ ) {    // Loop once for each EEPROM entry
    readID(i);
    for ( int k = 0; k < 4; k++ ) {   // Loop 4 vezes
      if ( readCard[k] == storedCard[k] )    // SE a! = B então falso, porque: um falha, todos falham
        acertos ++;
    }
    if (acertos == 4 ) return (true);
    acertos = 0;
  }
  return false;
}

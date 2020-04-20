#include "main.h"

uint8_t cards[100][4];

void flashModifi (char *tag){
}

void sinc (){
  String tags;
  int tag_cadastradas = EEPROM.read(0);     // Read the first Byte of EEPROM that
  Serial.print("Tags cadastradas: ");
  Serial.println(tag_cadastradas);
  tags += "tags/sinc.php/";
  for(int i = 0; i < tag_cadastradas; i++){
    readID(i);//Armazena em storedCard um ID da EEPROM
    for(int a = 0; a < 4; a++) {
       cards[i][a] = storedCard[a];  
       tags += storedCard[a];
    }
    tags += ':';
  }
  tags += ';';
  Serial.println(tags);
  for(int i = 0; i < tag_cadastradas; i ++){
    Serial.print(" TAG ");
    Serial.print(i,DEC);
    Serial.print(": ");
    for(int a = 0; a < 4; a++) {
      Serial.print(cards[i][a],HEX);
    }
    Serial.println(" ");  
  }
}

void setup()
{
  status_tela = 0;
  pinMode(pino_buzzer, OUTPUT);
  delay(1000);
  Serial.begin(115200);       // Inicia a serial
  SPI.begin();                // Inicia  SPI bus
  lcd.init();                 // Inicializando o LCD
  mfrc522.PCD_Init();         // Inicia MFRC522
  lcd.backlight();            // Ligando o BackLight do LCD
  lcd.clear();
  
  delay(1000);
  sinc();
  lcd_server_conectando();
  
  //EEPROM_scanner ();        //Faz o escaneamento de toda a eeprom e envia para a serial
  cadastraMaster();           //Cadastra a tag master, se não estiver cadastrada
  ethInit();                  //Inicializa o módulo ethernet
  //telaConectado();          //Display
  delay(1000);
  lcd_user_inicio();          //tela Inicial Display
  ctk.modo(FULL);             //Inicializa a placa no modo catraca(full)
  interrupt_giro_config ();   //Configura os pinos g1 e g2 como interrupção extern
  if (servidor_status == 0)   {
    lcd_server_offline();
    Serial.println("Servidor offline");
  }
  else {
    lcd_server_online();
    Serial.println("Servidor onine");
  }
  menu_title();
}

void loop()
{
  do {
    menu_options ();
    giro_check();
    successRead = getID();  // define successRead para 1 quando lemos do leitor, caso contrário 0
    if (status_tela == 1) if (tempo_tela_anterior < (millis() - 2000)) lcd_user_inicio(); 
  }
  while (!successRead);   //o programa não irá além enquanto você não estiver obtendo uma leitura bem-sucedida
  if ( isMaster(readCard)) rotinaMaster(); //Rotina de cadastro (biblioteca user.h
  else if (servidor_status == ONLINE) catraca_online();
  else if (servidor_status == OFFLINE) catraca_offline();
}
void catraca_online() {
  rotina_request(CONSULTA);
  if (stResponse == 'L') {
    giro_antihorario_liberado();
    giro_horario_liberado();
    lcd_user_acesso();
    tone_open ();
    tempo_tela_anterior = millis();
  }
  else if (stResponse == 'B') {
    lcd_user_bloqueado();
    lcd.noBacklight(); // turn off backlight
    tone_close ();
    lcd.backlight(); // turn off backlight
    tempo_tela_anterior = millis();
  }
  if (stResponse == 255) {
    Serial.println("Note: Tempo de resposta exedido!");
  }
}
void catraca_offline() {
  if ( verificaAcesso ()) {    // Se não for master, verifica se o ID está cadastrado
    //telaAcesso ();
    Serial.print("NUMERO DO CARD: ");
    Serial.println(findIDSLOT());
    Serial.print("Find: ");
    Serial.println(findID(readCard));
    
    giro_antihorario_liberado();
    giro_horario_liberado();
    lcd_user_acesso ();
    tempo_tela_anterior = millis();
    tone_open ();
  }
  else {      // Senão, ID não é valido. Acesso é bloqueado!!
    Serial.println("Note: ID nao cadastrado!");
    lcd_user_bloqueado();
    tempo_tela_anterior = millis();
    tone_close ();
    //if (servidor_status == 1)server_sinc_if_del(); //Verifica se pode deletar do servidor
  }
}
void menu_title() {
  Serial.println("Envie 's' para apagar a EEPROM");
  Serial.println("Envie 'r' para escanear a EEPROM");
  Serial.println("Envie 't' para sincronizar");
  Serial.println("Envie 'p' para imprimir as variaveis do RFID");
  Serial.println("Envie 'a' para executar a rotina de registro de acesso");
  Serial.println("Envie '0' para executar a rotina de registro de cadastro");
  Serial.println("Envie '1' para executar a rotina de registro de consulta");
  Serial.println("Envie '2' para executar a rotina de registro de deleta");
}
void menu_options (){
  if (Serial.available() > 0) {
      char d = Serial.read();
      if (d == 's') EEPROM_set();
      if (d == 'r') EEPROM_scanner ();
      if (d == 'p') print_variaveis(); //Imprime as variaveis da biblioteca RFID
      if (d == 'a') rotina_request(ACESSO);
      if (d == '0') rotina_request(CADASTRA);
      if (d == '1') rotina_request(CONSULTA);
      if (d == '2') rotina_request(DELETA);
      if (d == 't') sinc ();
    }
}

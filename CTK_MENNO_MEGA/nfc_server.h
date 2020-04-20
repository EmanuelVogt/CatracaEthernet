#include <SPI.h>
#include <Ethernet.h>

#define port 80
int servidor_status = 0;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEC, 0xFE, 0xED };

IPAddress server(34,95,156,193);

//IPAddress ip(192, 168, 0, 177);
//IPAddress myDns(192, 168, 0, 1);

EthernetClient client;

//String lag = "S1D2F3G4";
#define host  "Host: 34.95.156.193"
//#define host  "Host: www.nfcproject.com.br"
#define http_req  " HTTP/1.1"
#define url_consulta  "GET /consultaphp/consulta.php?tag="
#define url_deleta "GET /tags/excluir.php?tag="
#define url_cadastra "GET /tags/cadastrar.php?tag="
#define url_acesso "GET /tags/registra.php?tag="
String data;

char stResponse;
void ethInit(){
  if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    else{
      Serial.println("Inicializando Ethernet...");
 
    servidor_status = Ethernet.begin(mac);

    if(servidor_status == 1){
      Serial.print("DHCP ok, IP: ");
      Serial.println(Ethernet.localIP());
      lcd_server_online();
    }
    else {
      Serial.println("Note: Servidor Ofline");
      lcd_server_offline();
    }
    
  
  // give the Ethernet shield a second to initialize:
    }
  
  delay(500);
}
char verifiResponse(){
    //Serial.print(data);
    stResponse = 0;
    if((data.endsWith("FEITO        ")) || (data.endsWith("FEITO"))) {
      Serial.println("OK!");
      stResponse = 'K';
      client.stop(); //Encerra a comunicação com o servidor
      data = "";// Zera a variável
      return 2; // Retorna o valor 2 para a  função
    }
    else if((data.endsWith("OPEN        ")) || (data.endsWith("OPEN"))) {
      Serial.println("LIB!");
      stResponse = 'L';
      client.stop(); //Encerra a comunicação com o servidor
      data = "";// Zera a variável
      return 2; // Retorna o valor 2 para a  função
    }
    else if(data.endsWith("CLOSE        ")|| (data.endsWith("CLOSE"))) {
      Serial.println("BLQ!");
      stResponse = 'B';
      client.stop();//Encerra a comunicação com o servidor
      data = ""; // Zera a variável
      return 1; //Retorna o valor 1 para a função
    }
    else return 0;
}

void readResponse (){
  if (client.available()) {
    char c = client.read();
    data += c;
  }
}
void make_acesso (String& tag){
  // if you get a connection, report back via serial:
    if (client.connect(server, port))
    {  
      // Make a HTTP request:
      String request = url_acesso;
      request += tag;
      request += http_req;
      /*
      client.print(url);
      client.print(tag);
      client.println(http_req);*/
      client.println(request);
      client.println(host);
      client.println("Connection: close");
      client.println();

      Serial.print(request);
      request = "";
    }
    else {
      // if you didn't get a connection to the server:
      Serial.println("Note: Falha na conexão (acesso)");
    }
}
void make_deleta (String& tag){
  // if you get a connection, report back via serial:
    if (client.connect(server, port))
    {  
      // Make a HTTP request:
      String request = url_deleta;
      request += tag;
      request += http_req;
      /*
      client.print(url);
      client.print(tag);
      client.println(http_req);*/
      client.println(request);
      client.println(host);
      client.println("Connection: close");
      client.println();

      Serial.print(request);
      request = "";
    }
    else {
      // if you didn't get a connection to the server:
      Serial.println("Note: Falha na conexão (deleta)");
    }
}
void make_cadastra (String& tag){
  // if you get a connection, report back via serial:
    if (client.connect(server, port))
    {  
      // Make a HTTP request:
      String request = url_cadastra;
      request += tag;
      request += http_req;
      /*
      client.print(url);
      client.print(tag);
      client.println(http_req);*/
      client.println(request);
      client.println(host);
      client.println("Connection: close");
      client.println();

      Serial.print(request);
      request = "";
    }
    else {
      // if you didn't get a connection to the server:
      Serial.println("Note: Falha na conexão (cadastro)");
    }
}
void make_consulta(String& tag){
  // if you get a connection, report back via serial:
    if (client.connect(server, port))
    {  
      // Make a HTTP request:
      String request = url_consulta;
      request += tag;
      request += http_req;
      /*
      client.print(url);
      client.print(tag);
      client.println(http_req);*/
      client.println(request);
      client.println(host);
      client.println("Connection: close");
      client.println();

      Serial.print(request);
      request = "";
    }
    else {
      // if you didn't get a connection to the server:
      Serial.println("Note: Falha na conexão (consulta)");
    }
}

#define CADASTRA 0
#define DELETA 1
#define CONSULTA 2
#define ACESSO 3

void rotina_request(char tipo_de_cosulta) {
  String temp = "";
  for (int i = 0; i < 4; i++)temp += readCard[i];
  if (tipo_de_cosulta == CADASTRA) make_cadastra(temp);
  else if (tipo_de_cosulta == DELETA) make_deleta(temp);
  else if (tipo_de_cosulta == CONSULTA) make_consulta(temp);
  else if (tipo_de_cosulta == ACESSO) make_acesso(temp);
  //telaConsultando();
  int time_latencia = 0;
  stResponse = 0;
  while ((stResponse == 0) && (time_latencia < 10001)) {
    readResponse ();
    verifiResponse();
    time_latencia++;
  }
  Serial.print("LAT: ");
  Serial.println(time_latencia);
  if (stResponse == 'L') {
    //telaAcesso ();
  }
  else if (stResponse == 'B') {
    //telaBloqueado();
  }
  else if (stResponse == 'K') {
    lcd_server_registrado();
    //tempo_tela_anterior = millis();
  }
  if (time_latencia > 10000) {
    lcd_user_falha();
    tempo_tela_anterior = millis();
    stResponse = 255;
  }
}
//Essa função verifica se a tag já está cadastrada, senão, cadastra
void server_sinc_if_add() {
  rotina_request(CONSULTA);
  if (stResponse == 'B')rotina_request(CADASTRA);
  if (stResponse > 255)Serial.println(F("Note: Não foi possivel sincronizar com o servidor(add)"));
}

//Essa função verifica se a tag já está cadastrada, se sim, deleta
void server_sinc_if_del() {
  rotina_request(CONSULTA);
  if (stResponse == 'L')rotina_request(DELETA);
  if (stResponse > 255)Serial.println(F("Note: Não foi possivel sincronizar com o servidor(del)"));
}

void rotinaMaster() {
  //Verifica se o tag lido é o master
  Serial.println("Bem vindo Master!");
  lcd_master_inicio();
  uint8_t cont = 50;
  tone_master();
  do {
    successRead = getID(); // define successRead para 1 quando lemos do leitor, caso contrário 0
    cont--;
    delay(100);
    
    lcd.setCursor(17, 3); // Faz um contador regressivo no display
    lcd.print(cont / 10);
    lcd.print("s ");
  }
  while ((!successRead) && (cont > 1));
  if (cont < 2) {
    Serial.println("Note: Nenhum Tag lido");
    //telaInicial(); //Se nenhum Card foi lido...
  }
  if (successRead && !(isMaster(readCard))) { // Se houve a leitura de um novo card
    if ( verificaAcesso ()) { // Se é conhecido... Deleta da EEPROM
      deleteID(readCard);//deleta da EEPROM
      if(servidor_status == 1)rotina_request(DELETA);//deleta do servidor
      Serial.println("TAG CONHECIDA!");
      Serial.println("TAG EXCLUIDA!");
      lcd_master_tag_deletada();
      tone_deleted();
    }
    else {                    // Se é desconhecido.. Adiciona na EEPROM
      writeID(readCard);//deleta da EEPROM
      if(servidor_status == 1)rotina_request(CADASTRA);//deleta do servidor
      Serial.println("TAG DESCONHECIDA!");
      Serial.println("TAG ADICIONADA!");
      lcd_master_tag_adicionada();
      tone_add();
    }
  }
  tempo_tela_anterior = millis();
  lcd.setCursor(17, 3); // Faz um contador regressivo no display
  lcd.print("   ");
}

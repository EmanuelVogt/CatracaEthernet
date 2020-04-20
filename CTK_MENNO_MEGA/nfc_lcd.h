#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // Criando um LCD de 16x2 no endereço 0x20

long int tempo_tela_anterior;
int status_tela;

void lcd_server_offline() {
  lcd.setCursor(0, 3);
  lcd.print("CATRACA OFFLINE     ");
}
void lcd_server_online() {
  lcd.setCursor(0, 3);
  lcd.print("CATRACA ONLINE      ");
}
void lcd_server_consultando() {
  lcd.setCursor(0, 2);
  lcd.print("Consultando....     ");
  status_tela = 1;
}
void lcd_server_conectado() {
  lcd.setCursor(0, 2);
  lcd.print("IP: ");
  //lcd.print(Ethernet.localIP());
  status_tela = 1;
}
void lcd_server_conectando() {
  lcd.setCursor(0, 0);
  lcd.print("Buscando rede...    ");
  status_tela = 1;
}

void lcd_user_bloqueado() {
  lcd.setCursor(0, 0);
  lcd.print("  ACESSO BLOQUEADO! ");
  status_tela = 1;
}
void lcd_user_acesso () {
  lcd.setCursor(0, 0);
  lcd.print("     BEM-VINDO!     ");
  status_tela = 1;
}
void lcd_user_falha () {
  lcd.setCursor(0, 0);
  lcd.print("FALHA NO REGISTRO!  ");
  lcd.setCursor(0, 1);
  lcd.print("Tente novamente!    ");
  status_tela = 1;
}
void lcd_server_registrado() {
  lcd.setCursor(0, 1);
  lcd.print("ACESSO REGISTRADO!  ");
  status_tela = 1;
}
void lcd_server_Nregistrado() {
  lcd.setCursor(0, 1);
  lcd.print("ACESSO SEM REGISTRO!");
  status_tela = 1;
}
void lcd_user_inicio() {
  lcd.setCursor(0, 0);
  lcd.print("APROXIME SEU CARTAO");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  status_tela = 0;
}
void lcd_master_inicio(){
  lcd.setCursor(0, 0);
  lcd.print("OLA MASTER!         ");
  status_tela = 1;
}
void lcd_master_tag_deletada(){
  lcd.setCursor(0, 1);
  lcd.print("TAG DELETADA        ");
  status_tela = 1;
}
void lcd_master_tag_adicionada(){
  lcd.setCursor(0, 1);
  lcd.print("TAG ADICIONADA      ");
  status_tela = 1;
}

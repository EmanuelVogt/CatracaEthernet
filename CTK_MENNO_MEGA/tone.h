
#define pino_buzzer 40

void tone_master() {
  
  tone(pino_buzzer, 294, 300); //RE
  delay(200);
  tone(pino_buzzer, 262, 200); //DO
  delay(200);
}
void tone_deleted() {
  tone(pino_buzzer, 330, 300); //MI
  delay(200);
  tone(pino_buzzer, 349, 300); //FA
  delay(300);
}
void tone_add () {
  tone(pino_buzzer, 262, 100); //DO
  delay(200);
}
void tone_open () {
  tone(pino_buzzer, 262, 100); //DO
  delay(200);
  //tone(pino_buzzer,294,300); //RE
  //delay(300);
}
void tone_close () {
  tone(pino_buzzer, 330, 300); //MI
  delay(200);
  tone(pino_buzzer, 349, 300); //FA
  delay(300);
}

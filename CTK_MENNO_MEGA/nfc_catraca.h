//DEFINIÇÕES
enum{
  PADRAO = 0,
  FULL,
  INV,
  NOT_INV,
  WhiseClock,
  AntiWhiseClock,
};
unsigned long time_whiseClock;
unsigned long time_antiWhiseClock;
int giroWhiseClockDetected, giroAntiWhiseClockDetected;
#define tempo_max_giro 5000
unsigned long int tempo_anterior_giro_horario;
unsigned long int tempo_anterior_giro_antihorario;
int status_giro_antihorario;
int status_giro_horario;
int status_acesso;

class catraca  {
  private:
    int pMode;
    int pInve;
    int pGiroOne;
    int pGiroTwo;
    int pOutOne;
    int pOutTwo;

  public:
    void giroCallback(int tipo);
    void stopGiro (int tipo);
    void modo(int tipo);
    void inverter(int tipo);
    void freeOne(int tipo);
    catraca(int MOD, int INV, int G1, int G2, int IO1, int IO2) {
      pMode = MOD;
      pInve = INV;
      pGiroOne = G1;
      pGiroTwo = G2;
      pOutOne = IO1;
      pOutTwo = IO2;
      pinMode(pMode, OUTPUT);
      pinMode(pInve, OUTPUT);
      pinMode(pGiroOne, INPUT_PULLUP);
      pinMode(pGiroTwo, INPUT_PULLUP);
      pinMode(pOutOne, OUTPUT);
      pinMode(pOutTwo, OUTPUT);
    }
};
void catraca::modo(int tipo) {
  if (tipo == PADRAO) digitalWrite(pMode, LOW);
  else if (tipo == FULL) digitalWrite(pMode, HIGH);
}
void  catraca::inverter(int tipo) {
  if (tipo == NOT_INV) digitalWrite(pInve, LOW);
  else if (tipo == INV) digitalWrite(pInve, HIGH);
}

void ISR_ANTIHORARIO () {
  Serial.println("Note: GIRO ANTIHORARIO DETECTADO");
  status_giro_antihorario = 0;
}
void ISR_HORARIO () {
  Serial.println("Note: GIRO HORARIO DETECTADO");
  status_giro_horario = 0;
}
void interrupt_giro_config () {
  attachInterrupt(digitalPinToInterrupt(pG1), ISR_ANTIHORARIO, RISING);
  attachInterrupt(digitalPinToInterrupt(pG2), ISR_HORARIO, RISING);
}
void giro_antihorario_bloqueado() {
  digitalWrite(pIO2, LOW);
  status_giro_antihorario = 0;
}
void giro_horario_bloqueado () {
  digitalWrite(pIO1, LOW);
  status_giro_horario = 0;
}

void giro_check () {
  if((digitalRead(18)==HIGH) || (digitalRead(19) == HIGH)){
    giro_antihorario_bloqueado();
    giro_horario_bloqueado();
  }
  if (status_giro_antihorario == 0) {
    giro_antihorario_bloqueado();
    if (status_acesso == 1){
      if(servidor_status == 1)rotina_request(ACESSO);
      status_acesso = 0;
    }
  }
  if (status_giro_horario == 0) {
    giro_horario_bloqueado();
    if (status_acesso == 1){
      if(servidor_status == 1)rotina_request(ACESSO);
      status_acesso = 0;
    }
  }
  
  if ((status_giro_antihorario == 1) && (tempo_anterior_giro_antihorario < (millis() - tempo_max_giro))) {
    giro_antihorario_bloqueado();
    status_acesso = 0;
    Serial.println("Note: Giro AntiHorario Bloqueado por time out");
  }
  if ((status_giro_horario == 1) && (tempo_anterior_giro_horario < (millis() - tempo_max_giro))) {
    giro_horario_bloqueado();
    status_acesso = 0;
    Serial.println("Note: Giro Horario Bloqueado por time out");
  }
}

void giro_antihorario_liberado () {
  digitalWrite(pIO2, HIGH);
  tempo_anterior_giro_antihorario = millis();
  status_giro_antihorario = 1;
  status_acesso = 1;
  Serial.println("Note: 1 Giro Antihorario Liberado");
}
void giro_horario_liberado () {
  digitalWrite(pIO1, HIGH);
  tempo_anterior_giro_horario = millis();
  status_giro_horario = 1;
  status_acesso = 1;
  Serial.println("Note: 1 Giro Horario Liberado");
}

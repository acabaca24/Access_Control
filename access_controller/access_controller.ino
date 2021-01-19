

// ? ▼▼ DEFINIÇÃO DE CONSTANTES ▼▼
#define porta_corredorPinIn (1)     // TODO INSERIR NUMERO DO PIN
#define porta_corredorPinOut (2)    // TODO INSERIR NUMERO DO PIN
#define porta_amoedacaoPinIn (3)    // TODO INSERIR NUMERO DO PIN
#define porta_amoedacaoPinOut (4)   // TODO INSERIR NUMERO DO PIN
#define leitor_corredorPinIn (11)   // TODO INSERIR NUMERO DO PIN
#define leitor_corredorPinOut (12)  // TODO INSERIR NUMERO DO PIN
#define leitor_amoedacaoPinIn (13)  // TODO INSERIR NUMERO DO PIN
#define leitor_amoedacaoPinOut (14) // TODO INSERIR NUMERO DO PIN
#define sonar_corredorPin (5)       // TODO INSERIR NUMERO DO PIN
#define sonar_amoedacaoPin (6)      // TODO INSERIR NUMERO DO PIN
#define sensorPin (7)               // TODO INSERIR NUMERO DO PIN
#define avancarPin (8)              // TODO INSERIR NUMERO DO PIN
#define aguardePin (9)              // TODO INSERIR NUMERO DO PIN
#define sairPin (10)                // TODO INSERIR NUMERO DO PIN
#define okCorPin (15)               // TODO INSERIR NUMERO DO PIN
#define okAmoPin (16)               // TODO INSERIR NUMERO DO PIN
#define besouroPin (20)             // TODO INSERIR NUMERO DO PIN
int contador;

void setup()
{
  // ! put your setup code here, to run once:
  Serial.begin(9600);

  // * ▼▼ DEFINIR PINS DE INPUT ▼▼
  pinMode(porta_corredorPinIn, INPUT);
  pinMode(porta_amoedacaoPinIn, INPUT);
  pinMode(leitor_corredorPinIn, INPUT);
  pinMode(leitor_amoedacaoPinIn, INPUT);
  pinMode(sonar_corredorPin, INPUT);
  pinMode(sonar_amoedacaoPin, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(okCorPin, INPUT);
  pinMode(okAmoPin, INPUT);

  // * ▼▼ DEFINIR PINS DE OUTPUT ▼▼
  pinMode(porta_corredorPinOut, OUTPUT);
  pinMode(porta_amoedacaoPinOut, OUTPUT);
  pinMode(leitor_corredorPinOut, OUTPUT);
  pinMode(leitor_amoedacaoPinOut, OUTPUT);
  pinMode(avancarPin, OUTPUT);
  pinMode(aguardePin, OUTPUT);
  pinMode(sairPin, OUTPUT);
  pinMode(besouroPin, OUTPUT);
}

void loop()
{
  // ! put your main code here, to run repeatedly:

  static bool porta_corredorStatus = true;  // ? true ▶ fechada | false ▶ aberta
  static bool porta_amoedacaoStatus = true; // ? true ▶ fechada | false ▶ aberta

  //!------------------------------------▼▼ CICLO CORREDOR -> AMOEDAÇÃO ▼▼ ------------------------------------
  if (okPerson(okCorPin) == true && doorStatus(porta_corredorPinIn) == true)
  {
    // ? SE A PESSOA FOR AUTORIZADA NO CORREDOR COMEÇA O CICLO
    digitalWrite(porta_corredorPinOut, HIGH);
    porta_corredorStatus = false;
    if (closeDoor(porta_corredorPinIn, contador, sensorPin) == true)
    {
      // ? SE AO FIM DE 30 SEC. NINGUEM ENTRAR FECHA A PORTA
      digitalWrite(porta_corredorPinOut, LOW);
      porta_corredorStatus = true; // * RESETAR O ESTADO DA PORTA
    }
  }
  else if (okPerson(okCorPin) == false && doorStatus(porta_corredorPinIn) == false)
  {
    // ! FUCKING ALERT
    digitalWrite(besouroPin, HIGH);
  }

  if (isPersonEnt(sonar_corredorPin) == 1 && sensor(sensorPin) == true)
  {
    // ? SE A CONDIÇÃO SE VERIFICAR FECHA A PORTA DO CORREDOR E ACENDE A LUZ "AGUARDE"
    // ? ABRE PORTA DA AMOEDAÇÃO, DESLIGA A LUZ "AGUARDE" E ACENDE A LUZ "AVANCE"
    digitalWrite(porta_corredorPinOut, LOW);
    digitalWrite(aguardePin, HIGH);
    porta_corredorStatus = true; // * RESETAR O ESTADO DA PORTA
    delay(10000);
    digitalWrite(porta_amoedacaoPinOut, HIGH);
    porta_amoedacaoStatus = false; // * MUDAR O ESTADO DA PORTA
    digitalWrite(aguardePin, LOW);
    digitalWrite(avancarPin, HIGH);
  }
  else if (isPersonEnt(sonar_corredorPin) > 1 && sensor(sensorPin) == true)
  {
    // ? SE ENTRAR MAIS QUE UMA PESSOA, MANDA AS PESSOAS SAIR E FECHA A PORTA DE ENTRADA
    digitalWrite(sairPin, HIGH);
    delay(3000);
    digitalWrite(sairPin, LOW);
    digitalWrite(porta_corredorPinOut, LOW);
    porta_corredorStatus = true; // * RESETAR O ESTADO DA PORTA
  }

  if (isPersonSai(sonar_amoedacaoPin) == 0 && sensor(sensorPin) == false)
  {
    // ? DESLIGA LUZ "AVANCE" E FECHA PORTA DA AMOEDAÇÃO
    digitalWrite(avancarPin, LOW);
    digitalWrite(porta_amoedacaoPinOut, LOW);
    porta_amoedacaoStatus = true; // * RESETAR O ESTADO DA PORTA
  }
  //!----------------------------------------------------------------------------------------------------------

  //!------------------------------------▼▼ CICLO AMOEDAÇAO -> CORREDOR ▼▼ ------------------------------------
  if (okPerson(okAmoPin) == true && doorStatus(porta_amoedacaoPinIn) == true)
  {
    // ? SE A PESSOA FOR AUTORIZADA NA AMOEDAÇAO COMEÇA O CICLO
    digitalWrite(porta_amoedacaoPinOut, HIGH);
    porta_amoedacaoStatus = false;
    if (closeDoor(porta_amoedacaoPinIn, contador, sensorPin) == true)
    {
      // ? SE AO FIM DE 30 SEC. NINGUEM ENTRAR FECHA A PORTA
      digitalWrite(porta_amoedacaoPinOut, LOW);
      porta_amoedacaoStatus = true; // * RESETAR O ESTADO DA PORTA
    }
  }else if (okPerson(okAmoPin) == false && doorStatus(porta_amoedacaoPinIn) == false)
  {
    // ! FUCKING ALERT
    digitalWrite(besouroPin, HIGH);
  }

  if (isPersonEnt(sonar_amoedacaoPin) == 1 && sensor(sensorPin) == true)
  {
    // ? SE A CONDIÇÃO SE VERIFICAR FECHA A PORTA DA AMOEDACAO E ACENDE A LUZ "AGUARDE"
    // ? ABRE PORTA DO CORREDOR, DESLIGA A LUZ "AGUARDE" E ACENDE A LUZ "AVANCE"
    digitalWrite(porta_amoedacaoPinOut, LOW);
    digitalWrite(aguardePin, HIGH);
    porta_amoedacaoStatus = true; // * RESETAR A VARIAVEL QUE VÊ O ESTADO DA PORTA
    delay(10000);
    digitalWrite(porta_corredorPinOut, HIGH);
    porta_corredorStatus = false; // * MUDAR O ESTADO DA PORTA
    digitalWrite(aguardePin, LOW);
    digitalWrite(avancarPin, HIGH);
  }
  else if (isPersonEnt(sonar_amoedacaoPin) > 1 && sensor(sensorPin) == true)
  {
    // ? SE ENTRAR MAIS QUE UMA PESSOA, MANDA AS PESSOAS SAIR E FECHA A PORTA DE ENTRADA
    digitalWrite(sairPin, HIGH);
    delay(3000);
    digitalWrite(sairPin, LOW);
    digitalWrite(porta_amoedacaoPinOut, LOW);
    porta_amoedacaoStatus = true; // * RESETAR O ESTADO DA PORTA
  }

  if (isPersonSai(sonar_corredorPin) == 0 && sensor(sensorPin) == false)
  {
    // ? DESLIGA LUZ "AVANCE" E FECHA PORTA DO CORREDOR
    digitalWrite(avancarPin, LOW);
    digitalWrite(porta_corredorPinOut, LOW);
    porta_corredorStatus = true; // * RESETAR O ESTADO DA PORTA
  }
  //!----------------------------------------------------------------------------------------------------------
}

int isPersonEnt(int sonarIn)
{
  if (digitalRead(sonarIn) == HIGH)
    contador += 1;
  return contador;
}

int isPersonSai(int sonarIn)
{
  if (digitalRead(sonarIn) == HIGH)
    contador -= 1;
  return contador;
}

bool okPerson(int ok)
{
  if (digitalRead(ok) == HIGH)
  {
    return true;
  }
}

bool sensor(int sensor)
{
  if (digitalRead(sensor) == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool closeDoor(int contact, int count, int sensor)
// ? IF FUNTION RETURNS TRUE IT CLOSES THE DOOR, ELSE OPENS IT
{
  delay(30000);
  if (digitalRead(contact) == LOW && count == 0 && digitalRead(sensor) == LOW)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool doorStatus(int door)
{
  if (digitalRead(door) == LOW)
  {
    // ? IF LOW A PORTA ESTÁ ABERTA ▶ RETORNA FALSE
    return false;
  }
  if (digitalRead(door) == HIGH)
  {
    // ? IF HIGH A PORTA ESTÁ FECHADA ▶ RETORNA TRUE
    return true;
  }
}

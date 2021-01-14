#include <arduino-timer.h>


// ? ▼▼ DEFINE CONSTANTS ▼▼
#define porta_corredorPinIn 1, 17;     // TODO INSERT PIN NUMBER
#define porta_corredorPinOut 2;    // TODO INSERT PIN NUMBER
#define porta_amoedacaoPinIn 3;    // TODO INSERT PIN NUMBER
#define porta_amoedacaoPinOut 4;   // TODO INSERT PIN NUMBER
#define leitor_corredorPinIn 11;   // TODO INSERT PIN NUMBER
#define leitor_corredorPinOut 12;  // TODO INSERT PIN NUMBER
#define leitor_amoedacaoPinIn 13;  // TODO INSERT PIN NUMBER
#define leitor_amoedacaoPinOut 14; // TODO INSERT PIN NUMBER
#define sonar_corredorPin 5;       // TODO INSERT PIN NUMBER
#define sonar_amoedacaoPin 6;      // TODO INSERT PIN NUMBER
#define sensorPin 7;               // TODO INSERT PIN NUMBER
#define avancarPin 8;              // TODO INSERT PIN NUMBER
#define aguardePin 9;              // TODO INSERT PIN NUMBER
#define sairPin 10;                // TODO INSERT PIN NUMBER
#define okCorPin 15;               // TODO INSERT PIN NUMBER
#define okAmoPin 16;               // TODO INSERT PIN NUMBER
int counter;

void setup()
{
  // ! put your setup code here, to run once:
  Serial.begin(9600);

  // * ▼▼ DEFINE INPUT PINs ▼▼
  pinMode(porta_corredorPinIn, INPUT);
  pinMode(porta_amoedacaoPinIn, INPUT);
  pinMode(sonar_entradaPin, INPUT);
  pinMode(sonar_saidaPin, INPUT);
  pinMode(sensorPin, INPUT);

  // * ▼▼ DEFINE OUTPUT PINs ▼▼
  pinMode(porta_corredorPinOut, OUTPUT);
  pinMode(porta_amoedacaoPinOut, OUTPUT);
}

void loop(){
  // ! put your main code here, to run repeatedly:

  bool valid_card;
  static bool porta_corredorStatus = true;  // ? true = fechada
  static bool porta_amoedacaoStatus = true; // ? true = fechada


  if (okPersonCor(okCorPin) == true){
    digitalWrite(porta_corredorPinOut, HIGH); // ? OPEN CORREDOR DOOR
    delay(10000); // ? WAIT FOR DOOR TO OPEN

    if (isPersonEnt(sonar_corredorPin) == 1 && sensor(sensorPin) == true){
      digitalWrite(aguardePin, HIGH); // ? LIGHT UP WAIT LIGHT
      digitalWrite(porta_corredorPinOut, HIGH); // ? IF CONDITION CLOSE CORREDOR DOOR
      delay(10000); // ? WAIT FOR DOR TO CLOSE
      digitalWrite(porta_amoedacaoPinOut, HIGH); // ? OPEN CURRENCYING DOOR
      digitalWrite(aguardePin, LOW); // ? LIGHT DOWHN WAIT LIGHT 
      digitalWrite(avancarPin, HIGH); // ? LIGHT UP FORWARD LIGHT
      if (isPersonSai(sonar_amoedacaoPin) == 0 && sensor(sensorPin) == false){
        digitalWrite(porta_amoedacaoPinOut, HIGH); // ? IF CONDITION CLOSE CURRENCYING DOOR
        delay(10000); // ? WAIT FOR DOOR TO OPEN
        digitalWrite(porta_amoedacaoPinOut, LOW);  // ? CLOSE CURRENCYING DOOR
      }
    }else if (isPersonEnt(sonar_corredorPin) > 1 && sensor(sensorPin) == true){
      digitalWrite(sairPin, HIGH); // ? LIGHT UP MOVE OUT LIGHT
      delay(10000); // ? WAIT FOR PEOPLE TO GET OUT
      digitalWrite(porta_corredorPinOut, HIGH); // ? IF CONDITION CLOSE CORREDOR DOOR
    }else if (isPersonEnt(sonar_corredorPin) < 1 && sensor(sensorPin) == false){
      
    }
  }else if (okPersonAmo(okAmoPin) == true){
    ....
  }
}


int isPersonEnt(int sonarIn){
  if (digitalRead(sonarIn) == HIGH)
  counter += 1;
  return counter;
}

int isPersonSai(int sonarIn){
  if (digitalRead(sonarIn) == HIGH)
  counter -= 1;
  return counter;
}

bool okPersonCor (int ok){
  if (digitalRead(ok) == true){
    return true;
  }
}

bool okPersonAmo (int ok){
  if (digitalRead(ok) == true){
    return true;
  }
}

bool sensor(int sensorPin){
  if (digitalRead(sensorPin) == HIGH){
    return true;
  }else{
    return false;
  }
}

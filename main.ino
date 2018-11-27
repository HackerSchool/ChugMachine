//#include <Arduino.h>
#include<Wire.h>
#include <LiquidCrystal.h>
//pins do sensor de prox 1
#define TRIGPIN1 10
#define ECHOPIN1 A1
//pins do sensor de prox 2
#define TRIGPIN2 9
#define ECHOPIN2 A0

#define BUTTONPIN 2

//variáveis de teste
#define DISTMAX 15// distancia minima de trigger (em cms)
#define WAITTIME 3000   //wait time in milliseconds
#define TIMEMIN 500
//pins do LCD
#define RS 12
#define EN 13
#define D4 4
#define D5 5
#define D6 6
#define D7 7

//LiquidCrystal lcd(12, 13, 7, 4, 2,8); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)


//--------------------------------------------------------------------
//Variáveis Globais

int distancias[2] = {0, 0};
int estados[2] = {0, 0};
int ChugTimes[2] = {0, 0};
unsigned long  state_start[2] = {0, 0};
bool button_pressed = 0;


//LCD
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

//--------------------------------------------------------------------
void Transition();
void MedirDistancias ();
void DoStates();
bool buttonState(bool button_pressed);

//--------------------------------------------------------------------
void setup() {
  pinMode(TRIGPIN1, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHOPIN1, INPUT); // Sets the echoPin as an Input
  pinMode(TRIGPIN2, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHOPIN2, INPUT); // Sets the echoPin as an Input
  pinMode(BUTTONPIN, INPUT);
  //Serial.begin(9600); // Starts the serial communication
  //setup do lcd
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Player1: ");
  lcd.setCursor(0,1);
  lcd.print("Player2: ");

}

//--------------------------------------------------------------------
void loop() {

  //state 0 -> maquina armada
  //state 1 -> Bacano a beber o penalty
  //state 2 -> Bacano pousou o copo e maquina está em

  //button_pressed = buttonState(button_pressed);
  MedirDistancias();
  Transition();
  DoStates();
  //Serial.println(digitalRead(BUTTONPIN));

   /* Serial.print("Sensor 1 ->");
    Serial.print(estados[0]);
    Serial.print("    ;    ");
    Serial.print(distancias[0]);
    Serial.print("...   Sensor 2 ->");
    Serial.print(estados[1]);
    Serial.print("    ;    ");
    Serial.println(distancias[1]); */
    
}


//--------------------------------------------------------------------------------
void Transition() {
  int player =  0;
  unsigned long tempo = millis();

  if (digitalRead(BUTTONPIN) ==  1) {
    for (player = 0; player < 2; player++) {
      estados[player] = 0;
      state_start[player] = tempo;
      ChugTimes[player] = 0;
    }
    //button_pressed = 0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Player1: ");
  lcd.setCursor(0,1);
  lcd.print("Player2: ");
    return;
  }

  for (player = 0; player < 2; player++) {

    if (estados[player] ==  0 && distancias[player] > DISTMAX) { //transicao do estado 0
      estados[player] = 1;
      ChugTimes[player] = 0;
      state_start[player] = tempo;
    }

    else if (estados[player] == 1 && distancias[player] < DISTMAX ) { //transicao do estado 1
      estados[player] = 2;
      ChugTimes[player] = tempo - state_start[player];
      state_start[player] = tempo;
    }

   /* else if (estados[player] == 2 && (tempo  - state_start[player]) > WAITTIME    ) { //transicao do estado 2
      estados[player] = 0;
      ChugTimes[player] = 0;
      state_start[player] = tempo;
    }*/

    else if (estados[player] == 1)
      ChugTimes[player] = tempo - state_start[player];

    else if (estados[player] == 2 && ChugTimes[player] < TIMEMIN){
      estados[player] = 1;
      state_start[player] = tempo - ChugTimes[player];
    }
    }
  }

    





//------------------------------------------------------------------------------------
void MedirDistancias () {

  int  duration[2] = {0, 0};

  // Clears the trigPin
  digitalWrite(TRIGPIN1, LOW);
  // digitalWrite(TRIGPIN2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGPIN1, HIGH);
  //digitalWrite(TRIGPIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN1, LOW);
  //digitalWrite(TRIGPIN2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration[0] = pulseIn(ECHOPIN1, HIGH);
  //duration[1] = pulseIn(ECHOPIN2, HIGH);
  // Calculating the distance
  distancias[0] = abs( duration[0] * 0.034 / 2 );
  //distancias[1] = duration[1] * 0.034 / 2;



  digitalWrite(TRIGPIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN2, LOW);
  duration[1] = pulseIn(ECHOPIN2, HIGH);
  distancias[1] = abs( duration[1] * 0.034 / 2 );

}

//------------------------------------------------------------------------------------
void DoStates() {

  //Esta função é igual para todos os estados, apenas mostra o tempo ChugTimes[] no ecra -> é zero   caso de estado 0 e é Chug_times[i] nos  outros dois estados

  int player = 0;
  
  for (player = 0; player < 2; player++) {
    lcd.setCursor(9, player);
    lcd.print(ChugTimes[player]);
  }


}
bool buttonState(bool button_pressed) {
  bool new_state = button_pressed;

  if (digitalRead(BUTTONPIN) == HIGH)
    new_state = 1;


  return new_state;
}

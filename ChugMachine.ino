#include <LiquidCrystal.h>
#include "Timer.h"
//pins do sensor de prox 1
#define TRIGPIN1 3
#define ECHOPIN1 A1 


//pins do sensor de prox 2
#define TRIGPIN2 5
#define ECHOPIN2 A1

//variáveis de teste
#define DISTMAX 20 // distancia minima de trigger
#define TIMEMIN 10 //10 milliseconds = 0.01 seconds (escala mínima)

//pins do LCD
#define RS 12
#define EN 13
#define D4 2
#define D5 4
#define D6 7
#define D7 8

//LiquidCrystal lcd(12, 13, 7, 4, 2,8); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)


//--------------------------------------------------------------------
//Variáveis Globais
int distancia1 = 0;
int distancia2 = 0;
int state1 = 0;
int state2 = 0;
float time_value1 = 0;
float time_value2 = 0;
//Timers
Timer timer1; //objeto do tipo timer1 da bibloteca timer1.h
Timer timer2;
//LCD
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);

//--------------------------------------------------------------------
int figureOutNextState(int state,int distance,float timer1);
int MedirDistancia (int trigPin, int echoPin);
float RefreshTimer1(int state);
float RefreshTimer2(int state);
void DoStateZero(int player);
void DoStateOne(float time_value,int player);
void DoStateTwo(int player);


//--------------------------------------------------------------------
void setup() {
  pinMode(TRIGPIN1, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHOPIN1, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  //setup dos timers
  timer1.every(TIMEMIN, RefreshTimer1,0);
  timer2.every(TIMEMIN, RefreshTimer2,0);

  //setup do lcd
  lcd.begin(16,2);  
  
}

//--------------------------------------------------------------------
void loop() {

  //state 0 -> maquina armada
  //state 1 -> Bacano a beber o penalty
  //state 2 -> Bacano pousou o copo e maquina está em 


  timer1.update();
  timer2.update();
  distancia1 = MedirDistancia(TRIGPIN1,ECHOPIN1);
  RefreshTimer1(state1);
  RefreshTimer2(state2);
  
  
  //Serial.println(MedirDistancia(TRIGPIN2,ECHOPIN2));

  state1 = figureOutNextState(state1,distancia1,time_value1);
  state2 = figureOutNextState(state2,distancia2,time_value2);
  
  switch(state1){
    case 0:
      DoStateZero(1);
      break;
    case 1:
      DoStateOne(1,time_value1);
      break;
    case 2:
      DoStateTwo(1);
    
  }

  switch(state2){
    case 0:
      DoStateZero(2);
      break;
    case 1:
      DoStateOne(2,time_value2);
      break;
    case 2:
      DoStateTwo(2);
  }
      
  }


//--------------------------------------------------------------------------------
int figureOutNextState(int state,int distance,float timer1){

  if(state == 0 && distance > DISTMAX ){
    state = 1;
    
  }

  if(state == 1 && distance < DISTMAX){
    state = 2;
  }

  if(state = 2 && timer1 <0){
    state = 0;
    
  }

  return state;
      
  
}


//------------------------------------------------------------------------------------
int MedirDistancia (int trigPin, int echoPin) {
  int distance = 0;
  int duration = 0;
// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;  

  return distance;
}

//------------------------------------------------------------------------------------
float RefreshTimer1(int state){
  if(state == 0)
    time_value1 = 0;
  else if(state == 1)
    time_value1 = time_value1 + TIMEMIN;
  /*else if(state == 2)
    time_value1 =time_value 1;
    */
}

//------------------------------------------------------------------------------------
float RefreshTimer2(int state){
  time_value2 = time_value2 + TIMEMIN;
}

//------------------------------------------------------------------------------------
void DoStateZero(int player){
  /* Imprime no lcd que está no state0
   *    * 
   */

   if(player==0){
      lcd.setCursor(0,1);
      lcd.print("0.00");
      time_value1 = 0;
   }

   if(player == 1){
    lcd.setCursor(1,1);
    lcd.print("0.00");
    time_value2 = 0;
   }
}

//------------------------------------------------------------------------------------
void DoStateOne(float time_value,int player){
  /*
   * Imprime o tempo de cada timer1
   * 
   */

   if(player == 1){
    lcd.setCursor(0,1);
    lcd.print(time_value);
   }
   
   if(player == 2){
    lcd.setCursor(1,1);
    lcd.print(time_value);
   }
  
}

//------------------------------------------------------------------------------------
void DoStateTwo(int player){
  /*
   * Imprime algo que diga que está no state 2
   * 
    */

    if(player == 1){
      lcd.setCursor(0,1);
      lcd.print(time_value1);
      
    }

    if(player == 2){
      lcd.setCursor(1,1);
      lcd.print(time_value2);
    }


}



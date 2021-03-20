#include <Servo.h>
#define INTERVAL_TIME 20

Servo servoX;
Servo servoY;


const int buttonPin = 3; 
const int buttonPin2 = 4; 

const int signalPin = 5;
const int signalPin2 = 6;
const int signalPin3 = 7;
const int signalPin4 = 8;
int signalState = 0;
int signalState2 = 0;
int signalState3 = 0;
int signalState4 = 0;

int servoXpin = 13;
int servoYpin = 12;


int laser = 11;

boolean laserOn = false;

unsigned long then = 0;  
unsigned long then2 = 0;
unsigned long then3 = 0;
unsigned long then4 = 0;

int index = 0;

int whiteLed = 2;

int buttonState = 0;   
int buttonState2 = 0;    

int resetTrackerCounter = 0;

int xVal = 0;
int yVal = 20;
boolean turnBack = false;
boolean turning = true;


//henk
int bits[8] = {LOW, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW};
int bits2[8] = {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW};
int bits3[8] = {LOW, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW};
int bits4[8] = {HIGH, LOW, HIGH, LOW, HIGH, HIGH, HIGH, LOW};

//toto
/*
int bits[8] = {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW};
int bits2[8] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
int bits3[8] = {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW};
int bits4[8] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
*/

void setup() {

 
servoX.attach(servoXpin);
servoY.attach(servoYpin);


pinMode(buttonPin, INPUT);
pinMode(buttonPin2, INPUT);
pinMode(signalPin, INPUT);
pinMode(signalPin2, INPUT);
pinMode(signalPin3, INPUT);
pinMode(signalPin4, INPUT);

pinMode(whiteLed, OUTPUT);

pinMode(laser, OUTPUT);

servoY.write(5);
servoX.write(0);



  Serial.begin(9600); // open the serial port at 9600 bps:

}

void turnServos(int instruction) {
    switch (instruction) {
      case 0: {
        if (turnBack) {
          if(xVal > 0) {
            xVal --;
          } else {
            yVal = 20;
            servoY.write(yVal);
            turnBack = false;
          }
          
        } else {
          if(xVal < 180) {
            xVal ++;
          } else {
            yVal = 160;
            servoY.write(yVal);
            turnBack = true;
          }
        }
        servoX.write(xVal);
        break;
      }
     case 1: {
      if (xVal == 0) {
      } else {
        xVal = xVal - 1;
        servoX.write(xVal);
        Serial.print("x: ");
        Serial.println(xVal);
        break;
      }
     }
     case 2: {
      if (xVal == 180) {
      } else {
        xVal = xVal + 1;
        servoX.write(xVal);
        Serial.print("x: ");
        Serial.println(xVal);
        break;
      }
     }
     case 3: {
      if (yVal == 0) {
      } else {
        yVal = yVal - 1;
        servoY.write(yVal);
        Serial.print("y: ");
        Serial.println(yVal);
      }
      break;
     }
     case 4: {
       if (yVal == 180) {
      } else {
        yVal = yVal + 1;
        servoY.write(yVal);
         Serial.print("y: ");
         Serial.println(yVal);
        break;
      }
     }
    }
}


void toggleTurn () {
  turning = !turning;
}

void loop() {  
  
   unsigned long now = millis();
  
   if (laserOn) {
   if( now - then >= INTERVAL_TIME) {
  then = now;
  // 0, 1, 2, 3, 4, 5, 6, 7, 8 => 9 sequenzen HIGH
  if ( index < 8 ) {
       if ( index == 0 ){
         digitalWrite(laser, HIGH);
       }
       index ++;
   } 
    else if ( index >= 8 && index <= 15 ) {
     digitalWrite(laser, bits[index-8]);
     index ++;
   }
   else if ( index >= 16 && index <= 23 ) {
     digitalWrite(laser, bits2[index-16]);
     index ++;
   }
    else if ( index >= 24 && index <= 31 ) {
     digitalWrite(laser, bits3[index-24]);
     index ++;
   }
    else if ( index >= 32 && index <= 39 ) {
     digitalWrite(laser, bits4[index-32]);
     index ++;
   }
   else if ( index == 40 ) {
     digitalWrite(laser, LOW);
     index ++;
   } else if ( index < 90 ) {
    index ++;
   } else {
    index = 0;
    laserOn = false;
   }
 }
   } else {
    
      digitalWrite(laser, LOW);

      buttonState = digitalRead(buttonPin);
      buttonState2 = digitalRead(buttonPin2);
      
      signalState = digitalRead(signalPin);
      signalState2 = digitalRead(signalPin2);
      signalState3 = digitalRead(signalPin3);
      signalState4 = digitalRead(signalPin4);
    
     
      if (signalState == HIGH){
         //Serial.println("signal 1 received");
         
      }

      if ( now - then4 > 300 ) {
        then4 = now;
        if (signalState && signalState2 && signalState3 && signalState4) {
          laserOn = true;
        }
        else if (signalState || signalState2 || signalState3 || signalState4) { 
          turning = false;
          resetTrackerCounter = 0;

/*************************X ACHSE****************/
          if( signalState && !signalState2) {
            Serial.println("weiter nach rechts ");
            turnServos(1);
          } else if (!signalState && signalState2 ){
            turnServos(2);
            Serial.println("weiter nach links ");
          } else if ( signalState && signalState2) {
            Serial.println("x achse passt ");
          }
          
/*************************Y ACHSE****************/
          if( signalState3 && !signalState4) {
            turnServos(3);
            Serial.println("weiter nach oben ");
          } else if (!signalState3 && signalState4 ){
            turnServos(4);
            Serial.println("weiter nach unten ");
          } else if ( signalState3 && signalState4) {
            Serial.println("y achse passt ");
          }
          Serial.println(" ");
        } else {
            resetTrackerCounter++;
            if (resetTrackerCounter > 10) {
              Serial.println("reset tracker");
              turning = true;
              resetTrackerCounter = 0;
            }
          
          
        }
      }
      
        if(buttonState2 == HIGH){
        if( now - then4 > 500) {
          then4 = now;
          laserOn = !laserOn;
        }
        }
    if(buttonState == HIGH){    
    if( now - then3 > 500) {
         then3 = now;
         toggleTurn();
        }
    }
          

      if (turning) {
        if ( now - then2 > 100 ) {
          then2 = now;
          turnServos(0);
        }
      }
   }
}

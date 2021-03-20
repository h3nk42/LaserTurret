#define THRESHOLD 20
#define INTERVAL_TIME 20

unsigned long then = 0;
unsigned long then2 = 0;
unsigned long then3 = 0;
unsigned long now;

int solarRead;
int index = 0;
int startBitIndex = 0;



int rBits[32];
int bits[8];
boolean reading = false;
boolean printReading = false;
boolean expectingTransmission = false;


int pinA = 3;
int pinB = 2;
int pinC = 4;
int pinD = 5;
int pinDot = 6;
int pinE = 7;
int pinF = 8;
int pinG = 9;
int D1 = 10;
int D2 = 11;
int D3 = 12;
int D4 = 13;

int solar = A0;
int ambientRead;



// the setup routine runs once when you press reset:
void setup() {

  Serial.begin(9600);
  ambientRead = analogRead(solar);
  Serial.print("ambientRead: ");
  Serial.println(ambientRead);

  // initialize the digital pins as outputs.
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}

void loop() {
  unsigned long now = millis();
  if (!printReading) {
    if (now - then >= INTERVAL_TIME) {
      then = now;
      solarRead = analogRead(solar);
      if (solarRead > ambientRead + THRESHOLD ) {
        if (reading) {
          rBits[index] = HIGH;
          index ++;
        } else {
          startBitIndex++;
        }
      } else {
        if (reading) {
          rBits[index] = LOW;
          index ++;
        } else {
          startBitIndex = 0;
        }
      }
      if (startBitIndex == 8) {
        //Serial.print("8");
        startBitIndex = 0;
        //expectingTransmission = true;
        reading = true;
        return 0;
      }
      if (index == 32) {
        reading = false;
        printReading = true;
        index = 0;
        then2 = now;
        for (int i = 0; i < 32; i++) {
          Serial.print(rBits[i]);
        }
        Serial.println(" ");
      }
    }
  } else {
     
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);
      digitalWrite(pinA, !rBits[0]);
      digitalWrite(pinB, !rBits[1]);
      digitalWrite(pinC, !rBits[2]);
      digitalWrite(pinD, !rBits[3]);
      digitalWrite(pinE, !rBits[4]);
      digitalWrite(pinF, !rBits[5]);
      digitalWrite(pinG, !rBits[6]);
      delay(1);
      
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);
      digitalWrite(pinA, !rBits[8]);
      digitalWrite(pinB, !rBits[9]);
      digitalWrite(pinC, !rBits[10]);
      digitalWrite(pinD, !rBits[11]);
      digitalWrite(pinE, !rBits[12]);
      digitalWrite(pinF, !rBits[13]);
      digitalWrite(pinG, !rBits[14]);
      delay(1);

      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      digitalWrite(pinA, !rBits[16]);
      digitalWrite(pinB, !rBits[17]);
      digitalWrite(pinC, !rBits[18]);
      digitalWrite(pinD, !rBits[19]);
      digitalWrite(pinE, !rBits[20]);
      digitalWrite(pinF, !rBits[21]);
      digitalWrite(pinG, !rBits[22]);
      delay(1);

      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      digitalWrite(D4, HIGH);
      digitalWrite(pinA, !rBits[24]);
      digitalWrite(pinB, !rBits[25]);
      digitalWrite(pinC, !rBits[26]);
      digitalWrite(pinD, !rBits[27]);
      digitalWrite(pinE, !rBits[28]);
      digitalWrite(pinF, !rBits[29]);
      digitalWrite(pinG, !rBits[30]);
      delay(1);

      
      if (now - then2 > 5000) {
      printReading = false;
      digitalWrite(D4, LOW);
      }
      /*
      // TWO

      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);

      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, LOW);
      delay(1);

      // FOUR

      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);

      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      delay(1);
    */
  }
}

void printArray () {
  for (int i = 0; i < 32; i++) {
    if (rBits[i] > ambientRead + THRESHOLD) {
      rBits[i] = HIGH;
    } else {
      rBits[i] = LOW;
    }
    Serial.print(rBits[i]);
    if ( i == 7 || i == 15 || i == 23) {
      Serial.print(" | ");
    }
  }
  Serial.println("");
}

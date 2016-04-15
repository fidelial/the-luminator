
int r0 = 0;
int r1 = 1;
int r2 = 0;
int pin = 0;
int data = 0;

int multiplex_1 = 8;
int multiplex_2 = 9;
int multiplexPin = 0;

int switchPin1 = 11;
int switchPin2 = 12;
int switchPin3 = 13; 

boolean switchState1 = false;
boolean switchState2 = false;
boolean switchState3 = false;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT); // sending digital2 to s0
  pinMode(3, OUTPUT); //sending digital3 to s1;
  pinMode(4, OUTPUT); //s2
  pinMode(8, OUTPUT); //EN of multiplex 1
  pinMode(9, OUTPUT); //EN of multiplex 2

  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);
  pinMode(switchPin3, INPUT_PULLUP);
}

void loop() {
//  Serial.write(255); // separator byte
  int val[6];
  
  Serial.write(255);
  switchState1 = digitalRead(switchPin1);
  switchState2 = digitalRead(switchPin2);
  switchState3 = digitalRead(switchPin3);
  
  //i is analogPin number
    if (multiplexPin == 0) {
      digitalWrite(multiplex_1, LOW); 
      digitalWrite(multiplex_2, HIGH);
      multiplexRead(multiplexPin);
    }
    if (multiplexPin == 1) {
      digitalWrite(multiplex_1, HIGH);
      digitalWrite(multiplex_2, LOW);
      multiplexRead(multiplexPin);
    }

    for (int i = 2; i < 6; ++i) {
      val[i] = analogRead(i);
//      Serial.print("Reading pin: ");
//      Serial.print(i);
//      Serial.print(" ");
//      Serial.println(val[i]);
      Serial.write(val[i]);
    }

    Serial.write(switchState3);
    Serial.write(switchState2);
    Serial.write(switchState1);
    delay(20);
  }

void multiplexRead(int whichMultiplex) {
//    Serial.print("WHICH MULTIPLEX? THIS MULTIPLEX: ");
//    Serial.println(whichMultiplex);
    for (int count = 0; count < 8; ++count) {
      r0 = bitRead(count, 0);
      r1 = bitRead(count, 1);
      r2 = bitRead(count, 2);

      digitalWrite(2, r0);
      digitalWrite(3, r1);
      digitalWrite(4, r2);

      //reading multiplex (A0)
      data = analogRead(whichMultiplex);
//      Serial.print("Reading photocell ");
//      Serial.print(count);
//      Serial.print(": ");
//      Serial.println(data);
      Serial.write(data>>3); //bit shifting
      Serial.write(data&7);
      delay(20);
    }
    if (multiplexPin == 0) {
      multiplexPin = 1;
    } else if (multiplexPin == 1) {
      multiplexPin = 0;
    }
    return;
}

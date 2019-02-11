//  Motor A
int const ENA = 10;  // speed
int const INA = 12;  // direction
//  Motor B
int const ENB = 11;  // speed
int const INB = 13;  // direction

int R_speed = 150;
int L_speed = 126;

int R_state = HIGH;
int L_state = LOW;

void setup() {
  pinMode(ENA, OUTPUT);   // set all the motor control pins to outputs
  pinMode(ENB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  Serial.begin(9600);     // Set comm speed for serial monitor messages
}

void loop() {
  char inputSignal = Serial.read();

  if(Serial.available()){
    Serial.write(inputSignal);
  }
  
  if(inputSignal == 'F'){
    digitalWrite(INA, HIGH);
    digitalWrite(INB, HIGH);
    analogWrite(ENA, R_speed);
    analogWrite(ENB, L_speed);
    R_state = HIGH;
    L_state = HIGH;
  } 

  if(inputSignal == 'L'){
    digitalWrite(INA, R_state);
    digitalWrite(INB, L_state);
    analogWrite(ENA, R_speed);
    analogWrite(ENB, L_speed-30);
  } 

  if(inputSignal == 'R'){
    digitalWrite(INA, R_state);
    digitalWrite(INB, L_state);
    analogWrite(ENA, R_speed-30);
    analogWrite(ENB, L_speed);
  } 
  
  if(inputSignal == 'S'){
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  }

  if(inputSignal == 'B'){
    digitalWrite(INA, LOW);
    digitalWrite(INB, LOW);
    analogWrite(ENA, R_speed);
    analogWrite(ENB, L_speed);
    R_state = LOW;
    L_state = LOW;
  }
}

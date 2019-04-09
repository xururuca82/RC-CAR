//  Motor A
int const ENA = 10;  // speed
int const INA = 12;  // direction
//  Motor B
int const ENB = 11;  // speed
int const INB = 13;  // direction

int const MIN_SPEED = 55;   // Set to minimum PWM value that will make motors turn
int const ACCEL_DELAY = 30; // delay between steps when ramping motor speed up or down.

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
    Motor('C', 'F', 60);
  } 

  if(inputSignal == 'S'){
    Motor('C', 'F', 0);
  }

  if(inputSignal == 'R'){
    Motor('C', 'R', 60);
  }

//  if(inputSignal == 'S'){
//    for(int i=70; i>=0; i--){
//      Motor('C', 'F', i);
//      delay(ACCEL_DELAY);
//    }
//  }  
}

void Motor(char motor, char dir, int speed){
  // remap the speed from range 0-100 to 0-255
  int L_speed;
  int R_speed;
  if (speed == 0){
    L_speed = 0;   // Don't remap zero, but remap everything else.
    R_speed = 0;
  }
  else {
    R_speed = map(speed, 1, 100, MIN_SPEED, 255);
    L_speed = R_speed - 35;
  }
  
  
  switch (motor) {
//    case 'A':   // Controlling Motor A
//      if (dir == 'F'){
//        digitalWrite(INA, HIGH);
//      }
//      else if (dir == 'R'){
//        digitalWrite(INB, LOW);
//      }
//      analogWrite(ENA, newspeed);
//      break;
//
//    case 'B':   // Controlling Motor B
//      if (dir == 'F'){
//        digitalWrite(INB, HIGH);
//      }
//      else if (dir == 'R'){
//        digitalWrite(INB, LOW);
//      }
//      analogWrite(ENB, newspeed);
//      break;

    case 'C':  // Controlling Both Motors
      if (dir == 'F'){
        digitalWrite(INA, HIGH);
        digitalWrite(INB, HIGH);
      }
      else if (dir == 'R'){
        digitalWrite(INA, LOW);
        digitalWrite(INB, LOW);
      }
      analogWrite(ENA, R_speed);
      analogWrite(ENB, L_speed);
      break;
    }
}

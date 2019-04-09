#define C 262   // 도
#define D 294   // 레

int piezoPin = 4;
int tempo = 200;
int notes[2] = {C,D};

void setup() {
  Serial.begin(9600);
  pinMode(piezoPin, OUTPUT);
}

void loop() {
  char inputSignal = Serial.read();
  
  if(Serial.available()){
    Serial.write(inputSignal);
  }

  if(inputSignal=='4'){  
    for(int i=0; i<2; i++){
      tone(piezoPin, notes[i], tempo);
      delay(300);
    }
  }
}

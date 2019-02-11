int trig = 7;
int echo = 8;

void setup() {
  Serial.begin(9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  char inputSignal = Serial.read();

  if(Serial.available()){
    Serial.write(inputSignal);
  }
  
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);
  float distance = duration/29.0/2.0;

  Serial.println(distance);
  delay(500);

}

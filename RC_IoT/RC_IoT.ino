void setup() {
  Serial.begin(9600);

}

void loop() {
  char inputSig = Serial.read();

  if(Serial.available()){
    Serial.write(inputSig);
  }
}

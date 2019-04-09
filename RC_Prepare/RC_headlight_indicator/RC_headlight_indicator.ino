#include <Adafruit_NeoPixel.h>
#include <MsTimer2.h>

#define NEO_PIN 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, NEO_PIN, NEO_GRB+NEO_KHZ800);

int headLightState = LOW;
unsigned long blinkChk = 0;

void setup() {
  pinMode(A5, OUTPUT);  
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void loop() {
  char inputSignal = Serial.read();

  if(Serial.available()){
    Serial.write(inputSignal);
  } 

  if(inputSignal == 'H'){
    if(headLightState){ 
      digitalWrite(A4, LOW);
      digitalWrite(A3, LOW);
      headLightState = LOW;
    } else {
      digitalWrite(A4, HIGH);
      digitalWrite(A3, HIGH);
      headLightState = HIGH;
    }
  }

  if(inputSignal == 'L'){   
    digitalWrite(A2, LOW);
    blinkChk = 0;
    MsTimer2::set(500, leftBlink);
    MsTimer2::start();
  }
  
  if(inputSignal == 'R'){
    digitalWrite(A5, LOW);
    blinkChk = 0;
    MsTimer2::set(500, rightBlink);
    MsTimer2::start();        
  }

  if(inputSignal == 'I'){   
    MsTimer2::stop();
    digitalWrite(A5, LOW);
    digitalWrite(A2, LOW);           
  }

  if(inputSignal == 'A'){
    warningOn(strip.Color(0,255,0),50);
  }

  if(inputSignal == 'F'){
    warningOn(strip.Color(255,0,0),50);
  }

  if(inputSignal == 'W'){
    warningOff();
  }
}

void leftBlink(){
  if(blinkChk%2){
    digitalWrite(A5, LOW);
  } else {
    digitalWrite(A5, HIGH);
  }
  blinkChk++;
  
}

void rightBlink(){
  if(blinkChk%2){
    digitalWrite(A2, LOW);
  } else {
    digitalWrite(A2, HIGH);
  }
  blinkChk++;
}

void warningOn(uint32_t c, uint8_t wait){
  for(uint16_t i=0;i<strip.numPixels();i++){
    strip.setPixelColor(i,c);
    strip.show();
    delay(wait);
  }

//  for(uint16_t j=0;j<strip.numPixels();j++){
//    uint16_t pixel = (strip.numPixels()-1)-j;
//    strip.setPixelColor(pixel, 0);
//    strip.show();
//    delay(wait);
//  }
}

void warningOff(){
  uint32_t c = 0;
  for(uint16_t i=0;i<strip.numPixels();i++){
    strip.setPixelColor(i,c);
    strip.show();
  }
}

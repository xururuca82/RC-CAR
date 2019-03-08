#include <Adafruit_NeoPixel.h>

#define NEO_PIN 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, NEO_PIN, NEO_GRB+NEO_KHZ800);

void setup() {  
  strip.begin();
  strip.show();
}

void loop() { 
    warningOn(strip.Color(0,10,0),50);  
    warningOff();
    delay(50);
}

void warningOn(uint32_t c, uint8_t wait){
  for(uint16_t i=0;i<strip.numPixels();i++){
    strip.setPixelColor(i,c);
    strip.show();
    delay(wait);
  }
}

void warningOff(){
  uint32_t c = 0;
  for(uint16_t i=0;i<strip.numPixels();i++){
    strip.setPixelColor(i,c);
    strip.show();
  }
}

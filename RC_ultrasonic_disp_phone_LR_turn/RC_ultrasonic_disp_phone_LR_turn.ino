#include <Adafruit_NeoPixel.h>

#define C 262   // 도

int piezoPin = 4;
int tempo = 200;
int trig = 7;
int echo = 8;

int neopixelPin = 3;
// 네오픽셀을 사용하기 위해 객체 하나를 생성한다
// 첫번째 인자값은 네오픽셀의 LED의 개수
// 두번재 인자값은 네오픽셀이 연결된 아두이노의 핀번호
// 세번째 인자값은 네오픽셀의 타입에 따라 바뀌는 flag
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, neopixelPin, NEO_GRB+NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(piezoPin, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  strip.begin(); // 네오픽셀의 초기화히기 위해 모든 LED를 off시킨다
  strip.show(); 
  
}

void loop() {
  char inputSignal = Serial.read();
  
  if(Serial.available()){
    Serial.write(inputSignal);
  }

  if(inputSignal=='3'){
    // 아래의 순서대로 NeoPixel을 반복한다.
    colorWipe(strip.Color(255,0,0),500);//빨간색 출력
    pixelsOffSquence(500); //차례로 끄기   
  }  
  
  if(inputSignal=='4'){    
    tone(piezoPin, C, tempo);    
  }

  if(inputSignal=='5'){    
    for(int i=0; i<5; i++){
      pixelsOnL(strip.Color(255,0,0));//빨간색 출력
      delay(500);
      pixelsOffL();
      delay(500);
    }
  }

  if(inputSignal=='6'){    
    for(int i=0; i<5; i++){
      pixelsOnR(strip.Color(255,0,0));//빨간색 출력    
      delay(500);
      pixelsOffR();
      delay(500);
    }
  }
  
  digitalWrite(trig,LOW);
  digitalWrite(echo,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  unsigned long duration = pulseIn(echo,HIGH);
  float distance = duration/29.0/2.0;

  Serial.println(distance);
  delay(800);
}

// NeoPixel에 달린 LED를 각각 주어진 인자값 색으로 채워나가는 함수
void colorWipe(uint32_t c, uint8_t wait){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);  
  }
}

void pixelsOffSquence(uint8_t wait){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    uint16_t pixels = (strip.numPixels()-1)-i;
    strip.setPixelColor(pixels, 0);
    strip.show();
    delay(wait);
  }  
}

void pixelsOnL(uint32_t c){
  uint16_t i=0;
  strip.setPixelColor(i, c);
  strip.show();  
}

void pixelsOffL(){
  uint16_t i=0;
  strip.setPixelColor(i, 0);
  strip.show();  
}

void pixelsOnR(uint32_t c){
  uint16_t i=1;
  strip.setPixelColor(i, c);
  strip.show();  
}

void pixelsOffR(){
  uint16_t i=1;
  strip.setPixelColor(i, 0);
  strip.show();
}

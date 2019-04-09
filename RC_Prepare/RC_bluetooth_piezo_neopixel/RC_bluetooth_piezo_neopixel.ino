#include <Adafruit_NeoPixel.h>

#define C 262   // 도
#define D 294   // 레

int piezoPin = 4;
int tempo = 200;
int notes[2] = {C,D};

int neopixelPin = 3;
// 네오픽셀을 사용하기 위해 객체 하나를 생성한다
// 첫번째 인자값은 네오픽셀의 LED의 개수
// 두번재 인자값은 네오픽셀이 연결된 아두이노의 핀번호
// 세번째 인자값은 네오픽셀의 타입에 따라 바뀌는 flag
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, neopixelPin, NEO_GRB+NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(piezoPin, OUTPUT);

  strip.begin(); // 네오픽셀의 초기화히기 위해 모든 LED를 off시킨다
  strip.show();
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

  if(inputSignal=='3'){
    // 아래의 순서대로 NeoPixel을 반복한다.
    colorWipe(strip.Color(255,0,0),50);//빨간색 출력
    colorWipe(strip.Color(0,255,0),50);//녹색 출력
    colorWipe(strip.Color(0,0,0255),50);//파란색 출력

    theaterChase(strip.Color(127,127,127),50);//흰색 출력
    theaterChase(strip.Color(127,0,0),50);//빨간색 출력
    theaterChase(strip.Color(0,0,127),50);//파란색 출력

    // 화려하게 다양한 색 출력
    rainbow(20);
    rainbowCycle(20);
    theaterChaseRainbow(50);    
  }  
}

// NeoPixel에 달린 LED를 각각 주어진 인자값 색으로 채워나가는 함수
void colorWipe(uint32_t c, uint8_t wait){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);  
  }
}

// 모든 LED를 출력가능한 모든 색으로 한번씩 보여주는 동작을 한번하는 함수
void rainbow(uint8_t wait) {
  uint16_t i,j;

  for(j=0;j<256;j++){
    for(i=0;i<strip.numPixels();i++){
      strip.setPixelColor(i,Wheel((i+j)&255));
    }
    strip.show();
    delay(wait);
  }
}

// NeoPixel에 달린 LED를 각각 다른 색으로 시작하여 다양한 색으로 5번 반복한다.
void rainbowCycle(uint8_t wait){
  uint16_t i,j;

  for(j=0;j<256*5;j++){
    for(i=0;i<strip.numPixels();i++){
      strip.setPixelColor(i, Wheel((((i*256/strip.numPixels())+j)&255)));
    }
    strip.show();
    delay(wait);
  }
}

// 입력한 색으로 LED를 깜빡거리며 표현한다
void theaterChase(uint32_t c, uint8_t wait){
  for(int j=0;j<10;j++){ // do 10 cycles of chasing
    for(int q=0;q<3;q++){
      for(int i=0;i<strip.numPixels();i=i+3){
        strip.setPixelColor(i+q,c); // turn every third pixel on
      }
      strip.show();

      delay(wait);

      for(int i=0;i<strip.numPixels();i=i+3){
        strip.setPixelColor(i+q,0); // turn every third pixel off
      }
    }
  }
}


// LED를 다양한 색으로 표현하며 깜빡거린다
void theaterChaseRainbow(uint8_t wait){
  for(int j=0;j<256;j++){
    for(int q=0;q<3;q++){
      for(int i=0;i<strip.numPixels();i=i+3){
        strip.setPixelColor(i+q, Wheel((i+j)%255));
      }
      strip.show();

      delay(wait);

      for(int i=0;i<strip.numPixels();i=i+3){
        strip.setPixelColor(i+q,0);
      }
    }
  }
}

// 255가지의 색을 나타내는 함수
uint32_t Wheel(byte WheelPos){
  if(WheelPos<85){
    return strip.Color(WheelPos*3, 255-WheelPos*3, 0);
  }else if(WheelPos<17){
    WheelPos-=85;
    return strip.Color(255-WheelPos*3,0,WheelPos*3);
  }else {
    WheelPos-=170;
    return strip.Color(0,WheelPos*3,255-WheelPos*3);
  }
}

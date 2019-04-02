/*
 * 블루투스 신호  
 * - G : 녹색 경광등  
*/

#include <MsTimer2.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>

#define NEO_PIN 3
#define TRIG 7
#define ECHO 8
#define SERVO 9

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, NEO_PIN, NEO_GRB+NEO_KHZ800);
Servo servo;

// 경광등 관련 전역변수
uint32_t c;
uint16_t led_idx = 0;
bool neopixel_onoff_change_chk = true;

// 모터 관련 전역변수
int const ENA = 10; // Speed
int const INA = 12; // Direction
int const ENB = 11;
int const INB = 13;
int r_speed = 90;
int l_speed = 90;
int mr_state = HIGH; // 오른쪽 모터 회전 방향
int ml_state = HIGH;  // 왼쪽 모터 회전 방향

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(A5, OUTPUT);

  //모터 핀 세팅
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  
  strip.begin();
  strip.show();      
}

void loop() {
  char input_sig = Serial.read();

  if(Serial.available()){
    Serial.write(input_sig);
  }

  if(input_sig == 'G') {
    // 녹색 경광등 켜기
    MsTimer2::set(80, neopixel_green_on);
    MsTimer2::start();
  }   
  
//  초음파 센서 
  digitalWrite(TRIG, LOW);
  digitalWrite(ECHO, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ECHO, LOW);

  unsigned long duration = pulseIn(ECHO, HIGH);
  float distance = duration/29.0/2.0;   

// 서보 모터   
  if(distance < 10 && distance > 1){    
    digitalWrite(A5, HIGH);
    analogWrite(ENA,0);
    analogWrite(ENB,0);
    
    for(int pos=95; pos<=180; pos++) {
      servo.write(pos);
      delay(5);
    }
    for(int pos=180; pos>=15; pos--) {
      servo.write(pos);
      delay(5);
    }
    for(int pos=15; pos<=95; pos++) {
      servo.write(pos);
      delay(5);
    }   
    delay(1000);    
  } else {
    digitalWrite(A5, LOW);
    digitalWrite(INA, HIGH);
    digitalWrite(INB, HIGH);
    analogWrite(ENA, r_speed);
    analogWrite(ENB, l_speed);
  }
}

// 경광등 녹색
void neopixel_green_on(){
  if(led_idx == 8){
    led_idx = 0;
    if(neopixel_onoff_change_chk) neopixel_onoff_change_chk = false;
    else neopixel_onoff_change_chk = true;
  }
  if(neopixel_onoff_change_chk) c = strip.Color(0,30,0);
  else c = 0;
  
  strip.setPixelColor(led_idx,c);
  strip.show();
  led_idx++;
}

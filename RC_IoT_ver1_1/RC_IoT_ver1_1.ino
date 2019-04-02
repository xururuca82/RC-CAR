/*
 * 블루투스 신호
 * - b : 부저 울리기
 * - R : 빨간색 경광등
 * - G : 녹색 경광등
 * - B : 파란색 경광등
 * - S : 경광등 끄기
 * - h : 헤드라이트 끄기 켜기
 * - f : 헤들라이트 끄기
 * - l : 왼쪽 깜박이
 * - r : 오른쪽 깜박이
 * - s : 깜박이 끄기
 * 
 * - 0 : 정지
 * - 1 : 전진
 * - 2 : 후진
 * - 3 : 좌회전
 * - 4 : 우회전
 */

#include <Adafruit_NeoPixel.h>

#define BUZZER_PIN 4
#define NEO_PIN 5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, NEO_PIN, NEO_GRB+NEO_KHZ800);

// 경광등 관련 전역변수
uint32_t c;
uint16_t led_idx = 0;
bool neopixel_onoff_change_chk = true;

int const w_delay_time = 80;
unsigned long w_r_previous_millis = 0;
unsigned long w_g_previous_millis = 0;
unsigned long w_b_previous_millis = 0;
bool w_r_chk = false;
bool w_g_chk = false;
bool w_b_chk = false;

// 헤드라이트 관련 전역변수
bool hd_chk = true;

// 좌우 깜박이 관련 전역변수
unsigned long l_previous_millis = 0;
unsigned long r_previous_millis = 0;
const long delay_time = 300;
bool l_start = false;
bool r_start = false;
bool l_state = false;
bool r_state = false;

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
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(A5, OUTPUT); // 깜박이 L
  pinMode(A4, OUTPUT); // 헤드라이트 L
  pinMode(A1, OUTPUT); // 깜박이 R
  pinMode(A0, OUTPUT); // 헤드라이트 R

  //모터 핀 세팅
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  
  strip.begin();
  strip.show();
}

void loop() {
  unsigned long current_millis = millis();
  char input_sig = Serial.read();

  if(Serial.available()){
    Serial.write(input_sig);
  }

//  digitalWrite(BUZZER_PIN, buzzer_chk);

/*------ 버저 신호가 들어 왔을 때 -----*/
  if(input_sig=='b'){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(150);
    digitalWrite(BUZZER_PIN, LOW);
  }
/*-------------------------------------------*/
  
/*----------- 경광등을 켜고 끄기 ---------------*/
  // 빨간색 경광등 켜기
  if(input_sig == 'R'){    
    w_r_previous_millis = millis();
    w_r_chk = true;
    w_g_chk = false;
    w_b_chk = false;
        
  }

  if(w_r_chk) {
    if(current_millis - w_r_previous_millis >= w_delay_time){
      w_r_previous_millis = current_millis;
      if(led_idx == 8) {
        led_idx = 0;
        if(neopixel_onoff_change_chk) neopixel_onoff_change_chk = false;
        else neopixel_onoff_change_chk = true;
      }
      if(neopixel_onoff_change_chk) c=strip.Color(30,0,0);
      else c = 0;
  
      strip.setPixelColor(led_idx, c);
      strip.show();
      led_idx++;
    }
  } else {
    w_r_previous_millis = 0;    
  }
  
  // 녹색 경광등 켜기
  if(input_sig == 'G'){
    w_g_previous_millis = millis();
    w_g_chk = true;   
    w_r_chk = false;
    w_b_chk = false;
  }

  if(w_g_chk) {
    if(current_millis - w_g_previous_millis >= w_delay_time){
      w_g_previous_millis = current_millis;
      if(led_idx == 8) {
        led_idx = 0;
        if(neopixel_onoff_change_chk) neopixel_onoff_change_chk = false;
        else neopixel_onoff_change_chk = true;
      }
      if(neopixel_onoff_change_chk) c=strip.Color(0,30,0);
      else c = 0;
  
      strip.setPixelColor(led_idx, c);
      strip.show();
      led_idx++;
    }
  }else {
    w_g_previous_millis = 0;    
  }

  // 파란색 경광등 켜기
  if(input_sig == 'B'){
    w_b_previous_millis = millis();
    w_b_chk = true;   
    w_r_chk = false;
    w_g_chk = false;
  }

  if(w_b_chk) {
    if(current_millis - w_b_previous_millis >= w_delay_time){
      w_b_previous_millis = current_millis;
      if(led_idx == 8) {
        led_idx = 0;
        if(neopixel_onoff_change_chk) neopixel_onoff_change_chk = false;
        else neopixel_onoff_change_chk = true;
      }
      if(neopixel_onoff_change_chk) c=strip.Color(0,0,30);
      else c = 0;
  
      strip.setPixelColor(led_idx, c);
      strip.show();
      led_idx++;
    }
  }else {
    w_b_previous_millis = 0;    
  }

  // 경광등 끄기
  if(input_sig == 'S'){
   w_r_chk = false;
   w_g_chk = false;
   w_b_chk = false;
   uint32_t c_off = 0;
    for(uint16_t i=0;i<strip.numPixels();i++){
      strip.setPixelColor(i,c_off);
      strip.show(); 
    }
  }
/*------------------------------------*/

/*------- 헤드라이트 켜고 끄기  ----------*/
  // 헤드라이트 on/off 결정
  if(input_sig == 'h'){
    if(hd_chk){
      digitalWrite(A4, HIGH);
      digitalWrite(A0, HIGH);
      hd_chk = false;
    } else {
      digitalWrite(A4, LOW);
      digitalWrite(A0, LOW);
      hd_chk = true;
    }      
  }
  // 헤드라이트 끄기
  if(input_sig == 'f'){
    digitalWrite(A4, LOW);
    digitalWrite(A0, LOW);
  }
/*-------------------------------------*/

/*------------- 깜박이 켜고 끄기 ---------*/
  // 왼쪽 깜박이
  if(input_sig == 'l'){
    r_start = false;
    l_start = true;            
    l_previous_millis = millis();
  }

  if(l_start){
    if(current_millis - l_previous_millis >= delay_time){
      l_previous_millis = current_millis;
      l_state = !l_state;
      digitalWrite(A5, l_state);
    }  
  } else {
    digitalWrite(A5, LOW);
  }
  
  //오른쪽 깜박이
  if(input_sig == 'r'){
    l_start = false;
    r_start = true;        
    r_previous_millis = millis();
  }

  if(r_start){
    if(current_millis - r_previous_millis >= delay_time){
      r_previous_millis = current_millis;
      r_state = !r_state;
      digitalWrite(A1, r_state);
    }  
  }else {
    digitalWrite(A1, LOW);
  }

  // 깜박이 멈추기
  if(input_sig == 's') {
    l_start = false;
    r_start = false;
    digitalWrite(A5, LOW);
    digitalWrite(A1, LOW);
  }  
/*-------------------------------------*/

/*---------- 모터 조정 하기 -------------*/
  // 정지
  if(input_sig == '0'){
    analogWrite(ENA,0);
    analogWrite(ENB,0);
  }
  
  // 전진
  if(input_sig == '1'){
    digitalWrite(INA, HIGH);
    digitalWrite(INB, HIGH);
    analogWrite(ENA, r_speed);
    analogWrite(ENB, l_speed);
    mr_state = HIGH;
    ml_state = HIGH;
  }

  // 후진
  if(input_sig == '2'){
    digitalWrite(INA, LOW);
    digitalWrite(INB, LOW);
    analogWrite(ENA, r_speed);
    analogWrite(ENB, l_speed);
    mr_state = LOW;
    ml_state = LOW;
  }

  // 좌회전
  if(input_sig == '3'){
    digitalWrite(INA, mr_state);
    digitalWrite(INB, ml_state);
    analogWrite(ENA, r_speed);
    analogWrite(ENB, l_speed-30);
    delay(200);
    analogWrite(ENB, l_speed);
  }

  // 우회전
  if(input_sig == '4'){
    digitalWrite(INA, mr_state);
    digitalWrite(INB, ml_state);
    analogWrite(ENA, r_speed-30);
    analogWrite(ENB, l_speed);    
    delay(200);
    analogWrite(ENA, r_speed);
  }
/*-------------------------------------*/
}

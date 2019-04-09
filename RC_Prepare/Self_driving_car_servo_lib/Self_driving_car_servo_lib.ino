#include <Servo.h>



/*
 * 블루투스 신호  
 * - 5: 자율주행 시작 
 * - 6: 자율주행 멈춤
*/


#define TRIG 7
#define ECHO 8

int servo_pin = 9;

Servo servo;

bool self_drive_chk = false;
bool servo_chk = true;

// 모터 관련 전역변수
int const ENA = 6; // Speed
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

  //서보모터
  servo.attach(servo_pin, 1000, 2000);
  servo.writeMicroseconds(1500);
  servo.detach();
}

void loop() {
  
  char input_sig = Serial.read();

  if(Serial.available()){
    Serial.write(input_sig);
  }    

  Serial.print(servo.attached());
  
//  초음파 센서 
  digitalWrite(TRIG, LOW);
  digitalWrite(ECHO, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ECHO, LOW);

  unsigned long duration = pulseIn(ECHO, HIGH);
  float distance = duration/29.0/2.0; 
  

// 자율주행자동차
//  if(input_sig == '5') {
//    self_drive_chk = true;
//  }
  
  if(true){
    if(distance < 15 && distance > 1){    
      digitalWrite(A5, HIGH);
      analogWrite(ENA,0);
      analogWrite(ENB,0);
      if(servo_chk) {
        
      }      
    } else {
      digitalWrite(A5, LOW);
      digitalWrite(INA, HIGH);
      digitalWrite(INB, HIGH);
      analogWrite(ENA, r_speed);
      analogWrite(ENB, l_speed);
    }
  } else {
    analogWrite(ENA,0);
    analogWrite(ENB,0);
  }

  if(input_sig == '6') {
    self_drive_chk = false;    
  }  
}

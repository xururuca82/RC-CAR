#include <Servo.h>

#define TRIG 7
#define ECHO 8
#define SERVO_PIN 9

Servo servo;

// 자율주행차 관련 전역변수
int min_value = 544;
int max_value = 2400;
float distance = 0.0;
unsigned long duration = 0;
bool sonar_chk = false;
bool self_drive_chk = false;
bool servo_chk = true;
int r_dis_opti=0;

// 모터 관련 전역변수
int const ENA = 6; // Speed
int const INA = 12; // Direction
int const ENB = 11;
int const INB = 13;
int r_speed = 100;
int l_speed = 90;
int mr_state = HIGH; // 오른쪽 모터 회전 방향
int ml_state = HIGH;  // 왼쪽 모터 회전 방향

void setup() {
  //모터 핀 세팅
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);

  //초음파센서 핀 세팅
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(A5, OUTPUT);

  //서보모터 초기값 세팅
  servo.attach(SERVO_PIN, min_value, max_value);
  servo.write(90);
  delay(100);
  servo.detach();
}

void loop() {
  // 초음파 거리 측정
  digitalWrite(TRIG, LOW);
  digitalWrite(ECHO, LOW);    
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);  
  delayMicroseconds(10);
  digitalWrite(ECHO, LOW);  
  
  duration = pulseIn(ECHO, HIGH);
  distance = duration/29.0/2.0; 

  if(distance < 20 && distance > 1){    
    servo.attach(SERVO_PIN);  
    int l_dis = 0;
    int r_dis = 0;
    
    digitalWrite(A5, HIGH);
    analogWrite(ENA,0);
    analogWrite(ENB,0);      
    servo_chk = true;
    
    if(servo_chk){
      servo.write(175);
      if(servo.read() == 175) {
        delay(50);
        digitalWrite(TRIG, LOW);
        digitalWrite(ECHO, LOW);
        delayMicroseconds(2);
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(ECHO, LOW);          

        duration = pulseIn(ECHO, HIGH);
        float l_dis = duration/29.0/2.0;
      }
      delay(600);        
      servo.write(20);
      if(servo.read() == 20) {
        delay(50);
        digitalWrite(TRIG, LOW);
        digitalWrite(ECHO, LOW);
        delayMicroseconds(2);
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(ECHO, LOW);          

        duration = pulseIn(ECHO, HIGH);
        float r_dis = duration/29.0/2.0;
        r_dis_opti = (int)r_dis - 15;      
      }        
      delay(1200);
      servo.write(90);
      delay(1000);

      servo_chk = false;
    }

    servo.detach();
    
    if(r_dis_opti < 20) {
      delay(100);
      digitalWrite(INA, HIGH);
      digitalWrite(INB, HIGH);
      analogWrite(ENA, 0);
      analogWrite(ENB, l_speed);
    } else {
      delay(100);
      digitalWrite(INA, HIGH);
      digitalWrite(INB, HIGH);
      analogWrite(ENA, r_speed);
      analogWrite(ENB, 0);
    }
    delay(800);
  } else {
    digitalWrite(A5, LOW);
    digitalWrite(INA, HIGH);
    digitalWrite(INB, HIGH);
    analogWrite(ENA, r_speed);
    analogWrite(ENB, l_speed);
  }  
}

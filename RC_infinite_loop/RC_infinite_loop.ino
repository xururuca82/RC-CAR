#define TRIG 7
#define ECHO 8

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

  // 초음파 센서 관련
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  //모터 핀 세팅
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);

  digitalWrite(INA, HIGH);
  digitalWrite(INB, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG, LOW);
  digitalWrite(ECHO, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ECHO, LOW);

  unsigned long duration = pulseIn(ECHO, HIGH);
  float distance = duration/29.0/2.0; 

  if(distance < 20 && distance > 1){
    delay(100);
    digitalWrite(INA, LOW);
    digitalWrite(INB, LOW);
    analogWrite(ENA, l_speed);
    analogWrite(ENB, r_speed);
    delay(2000);
  } else {
    digitalWrite(INA, HIGH);
    digitalWrite(INB, HIGH);  
    analogWrite(ENA, r_speed);
    analogWrite(ENB, l_speed);
  }
}

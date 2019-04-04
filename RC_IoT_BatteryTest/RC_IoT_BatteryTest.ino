// 모터 관련 전역변수
int const ENA = 10; // Speed
int const INA = 12; // Direction
int const ENB = 11;
int const INB = 13;
int r_speed = 90;
int l_speed = 90;

void setup() { 
  //모터 핀 세팅
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
}

void loop() {
    /*---------- 모터 시계방향 회전 -------------*/ 
    digitalWrite(INA, HIGH);
    digitalWrite(INB, HIGH);
    analogWrite(ENA, r_speed);
    analogWrite(ENB, l_speed);   
}

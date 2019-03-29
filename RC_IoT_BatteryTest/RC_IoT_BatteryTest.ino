// 모터 관련 전역변수
int const ENA = 10; // Speed
int const INA = 12; // Direction
int const ENB = 11;
int const INB = 13;
int r_speed = 20;
int l_speed = 50;
int const MIN_SPEED = 27;

void setup() { 
  //모터 핀 세팅
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
}

void loop() {
    /*---------- 모터 시계방향 회전 -------------*/     
    int new_r_speed = map(r_speed, 1, 100, MIN_SPEED, 255);
    int new_l_speed = map(l_speed, 1, 100, MIN_SPEED, 255);
    
    digitalWrite(INA, HIGH);
    digitalWrite(INB, HIGH);
    analogWrite(ENA, new_r_speed);
    analogWrite(ENB, new_l_speed);   
}

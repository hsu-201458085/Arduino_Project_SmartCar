//출력핀(trig)과 입력핀(echo) 설정
int trigPinC = 13;                  // 디지털 13번 핀에 연결
int echoPinC = 12;                  // 디지털 12번 핀에 연결
int trigPinL = 3;                   // 왼쪽 초음파 3번핀 연결
int echoPinL = 2;                   // 왼쪽 초음파 2번핀 연결
int trigPinR = 7;                   // 오른쪽 초음파 5번핀 연결
int echoPinR = 4;                   // 오른쪽 초음파 4번핀 연결
int trigPinLW = 7;                   // 왼쪽 날개
int echoPinLW = 4;                   // 왼쪽 날개
int trigPinRW = 7;                   // 오른쪽 날개
int echoPinRW = 4;                   // 오른쪽 날개

long durationC;
long durationL;
long durationR;
long durationLW;
long durationRW;
long distanceC;
long distanceL;
long distanceR;
long distanceLW;
long distanceRW;

int RightMotor_E_pin = 5;      // 오른쪽 모터의 Enable & PWM
int RightMotor_1_pin = 8;      // 오른쪽 모터 제어선 IN1
int RightMotor_2_pin = 9;     // 오른쪽 모터 제어선 IN2
int LeftMotor_3_pin = 10;      // 왼쪽 모터 제어선 IN3
int LeftMotor_4_pin = 11;      // 왼쪽 모터 제어선 IN4
int LeftMotor_E_pin = 6;      // 왼쪽 모터의 Enable & PWM
int E_carSpeed = 153; // 최대 속도의  60 %
int prev_speed = 0;

void SmartCar_Go();
void SmartCar_Back();
void SmartCar_Stop();
void SmartCar_Left();
void SmartCar_Right();
void SmartCar_Update();
void Obstacle_Check();
void Distance_Measurement1();
void Distance_Measurement2();
void Distance_Measurement3();
void Distance_Measurement4();
void Distance_Measurement5();

void setup() {
    
   pinMode(echoPinC, INPUT);                  // echoPin 입력
   pinMode(trigPinC, OUTPUT);                 // trigPin 출력
   pinMode(echoPinL, INPUT);                  // echoPin 입력
   pinMode(trigPinL, OUTPUT);                 // trigPin 출력
   pinMode(echoPinR, INPUT);                  // echoPin 입력
   pinMode(trigPinR, OUTPUT);                 // trigPin 출력
   pinMode(echoPinLW, INPUT);                  // echoPin 입력
   pinMode(trigPinLW, OUTPUT);                 // trigPin 출력
   pinMode(echoPinRw, INPUT);                  // echoPin 입력
   pinMode(trigPinRW, OUTPUT);                 // trigPin 출력
   
   pinMode(RightMotor_E_pin, OUTPUT);        // 출력모드로 설정
   pinMode(RightMotor_1_pin, OUTPUT);
   pinMode(RightMotor_2_pin, OUTPUT);
   pinMode(LeftMotor_3_pin, OUTPUT);
   pinMode(LeftMotor_4_pin, OUTPUT);
   pinMode(LeftMotor_E_pin, OUTPUT);
   digitalWrite(RightMotor_E_pin, HIGH);     // 오른쪽 모터의 Enable 핀 활성화
   digitalWrite(LeftMotor_E_pin, HIGH);      // 왼쪽 모터의 Enable 핀 활성화
}

void loop() {
  Obstacle_Check();
  delay(100);
}

void Obstacle_Check() {
    Distance_Measurement1(); 
   SmartCar_Go();
   while (distanceC < 700) {
    
      if(distanceC < 100){
         SmartCar_Back();
         delay(500);
         SmartCar_Stop();
         delay(200);

         Distance_Measurement1();
         Distance_Measurement2();
         Distance_Measurement3();
         Distance_Measurement4();
         Distance_Measurement5();
         
      }
      else if (distanceC 100 && distanceC < 350) {
          if (distanceL + distanceLW < distanceR + distanceRW) {
            SmartCar_Right();
            delay(200);
          }
          else if (distanceL + distanceLW > distanceR + distanceRW) {
            SmartCar_Left();
            delay(200);
          }
          else{
            SmartCar_Go();
          }
      }
      else{
         SmartCar_NGo();
      }

      Distance_Measurement1();
      Distance_Measurement2();
      Distance_Measurement3();
      Distance_Measurement4();
      Distance_Measurement5();
   }
}

void Distance_Measurement1() { // 센터
    digitalWrite(trigPinC, LOW);
    delay(2);
    digitalWrite(trigPinC, HIGH);  // trigPin에서 초음파 발생(echoPin도 HIGH)
    delayMicroseconds(10);
    digitalWrite(trigPinC, LOW);
    durationC = pulseIn(echoPinC, HIGH);    // echoPin 이 HIGH를 유지한 시간을 저장 한다.
    distanceC = ((float)(340 * durationC) / 1000) / 2;
    delay(5);
}
void Distance_Measurement2() { // 왼쪽
  digitalWrite(trigPinL, LOW);
  delay(2);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  distanceL = ((float)(340 * durationL) / 1000) / 2;
  delay(5);
}
void Distance_Measurement3() { // 오른쪽
  digitalWrite(trigPinR, LOW);
  delay(2);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  distanceR = ((float)(340 * durationR) / 1000) / 2;
  delay(5);
}
void Distance_Measurement4() { // 왼쪽 날개 
  digitalWrite(trigPinLW, LOW);
  delay(2);
  digitalWrite(trigPinLW, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLW, LOW);
  durationLW = pulseIn(echoPinLW, HIGH);
  distanceLW = ((float)(340 * durationLW) / 1000) / 2;
  delay(5);
}
void Distance_Measurement5() { // 오른쪽 날개
  digitalWrite(trigPinRW, LOW);
  delay(2);
  digitalWrite(trigPinRW, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRW, LOW);
  durationRW = pulseIn(echoPinRW, HIGH);
  distanceRW = ((float)(340 * durationRW) / 1000) / 2;
  delay(5);
}
// 스마트카 동작 함수들
void SmartCar_Go()  // 전진
{
  digitalWrite(RightMotor_1_pin, HIGH);
  digitalWrite(RightMotor_2_pin, LOW);
  digitalWrite(LeftMotor_3_pin, HIGH);
  digitalWrite(LeftMotor_4_pin, LOW);
  
  for (int i = prev_speed; i <= E_carSpeed; i = i + 1) {
    analogWrite(RightMotor_E_pin, i);
    analogWrite(LeftMotor_E_pin, i);
    delay(20);
  }
  prev_speed = E_carSpeed;
  
}
void SmartCar_NGo()  
{  
  digitalWrite(RightMotor_1_pin, HIGH);
  digitalWrite(RightMotor_2_pin, LOW);
  digitalWrite(LeftMotor_3_pin, HIGH);
  digitalWrite(LeftMotor_4_pin, LOW);
  
  if(distanceLW > distanceRW){              // 오른쪽에 가까울 때
    analogWrite(RightMotor_E_pin, prev_speed * 1.1);           
    analogWrite(LeftMotor_E_pin, prev_speed * 0.9);            
  }
 else if(distanceLW < distanceRW){
  analogWrite(RightMotor_E_pin, prev_speed * 0.9);           
  analogWrite(LeftMotor_E_pin, prev_speed * 1.1);
 }
 
} 
void SmartCar_Back() // 후진
{
  digitalWrite(RightMotor_1_pin, LOW);
  digitalWrite(RightMotor_2_pin, HIGH);
  digitalWrite(LeftMotor_3_pin, LOW);
  digitalWrite(LeftMotor_4_pin, HIGH);
  for (int i = prev_speed; i <= E_carSpeed; i = i + 5) {
    analogWrite(RightMotor_E_pin, i);
    analogWrite(LeftMotor_E_pin, i);
    delay(20);
  }
  prev_speed = E_carSpeed;
}
void SmartCar_Left()  // 좌회전
{
  digitalWrite(RightMotor_1_pin, HIGH);
  digitalWrite(RightMotor_2_pin, LOW);
  digitalWrite(LeftMotor_3_pin, HIGH);
  digitalWrite(LeftMotor_4_pin, LOW);
  for (int i = prev_speed; i <= E_carSpeed; i = i + 5) {
    analogWrite(RightMotor_E_pin, i * 1.5);           // 140%
    analogWrite(LeftMotor_E_pin, i * 0.1);            // 20%
    delay(50);
  }
  prev_speed = E_carSpeed;
}
void SmartCar_Right() // 우회전
{
  digitalWrite(RightMotor_1_pin, HIGH);
  digitalWrite(RightMotor_2_pin, LOW);
  digitalWrite(LeftMotor_3_pin, HIGH);
  digitalWrite(LeftMotor_4_pin, LOW);
  for (int i = prev_speed; i <= E_carSpeed; i = i + 5) {
    analogWrite(RightMotor_E_pin, i * 0.1);           // 20%
    analogWrite(LeftMotor_E_pin, i * 1.5);            // 140%
    delay(50);
  }
  prev_speed = E_carSpeed;
}
void SmartCar_Stop()  // 정지
{

    for (int i = E_carSpeed; i >= 0; i = i - 5) {
      analogWrite(RightMotor_E_pin, i);
      analogWrite(LeftMotor_E_pin, i);
      delay(20);
    }
  digitalWrite(RightMotor_E_pin, LOW); // 정지
  digitalWrite(LeftMotor_E_pin, LOW);
}
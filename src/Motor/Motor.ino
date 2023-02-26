#include <Servo.h>

// Servo Setting
Servo servoR;
Servo servoL;

#define Straight_L 80
#define Straight_R 180

int motorR = 6;
int motorL = 7;
int angleR = Straight_R;
int angleL = Straight_L;

// DC Setting
int motorRpin1 = 9;
int motorRpin2 = 10;
int motorLpin1 = 11;
int motorLpin2 = 12;

void setup() {
  servoR.attach(motorR); //servoR에 입출력 6번 핀을 지정
  servoL.attach(motorL); //servoL에 입출력 7번 핀을 지정
  Serial.begin(9600); //시리얼 모니터 사용
  pinMode(motorLpin1, OUTPUT);
  pinMode(motorLpin2, OUTPUT);
  pinMode(motorRpin1, OUTPUT);
  pinMode(motorRpin2, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
    if(Serial.available()) //시리얼 통신이 가능할 경우
    {
        char input = Serial.read(); //시리얼 모니터 입력 값을 읽어옴
        Serial.println("Typing Number : ");
        /*
        1 : Straight
        2 : Stop
        3 : Right
        4 : Left

        (1) Servo Change
        (2) delay 10
        (3) DC go
        (4) delay 500
        (5) Stop (to know direction by LiDAR)
        */
        if(input == '1')
        {
            analogWrite(8, 100);
            analogWrite(13, 100);
            servoR.write(90);
     //       delay(10);
            servoL.write(80);
            delay(10);
            digitalWrite(motorRpin1, HIGH);
            digitalWrite(motorRpin2, LOW);
            digitalWrite(motorLpin1, HIGH);
            digitalWrite(motorLpin2, LOW);
            delay(500);
            Serial.println("fin");
        }
        else if(input =='2')
        {
            analogWrite(9, 0);
            analogWrite(13, 0);
            servoR.write(90);
     //       delay(10);
            servoL.write(80);
            delay(10);
            digitalWrite(motorRpin1, LOW);
            digitalWrite(motorRpin2, LOW);
            digitalWrite(motorLpin1, LOW);
            digitalWrite(motorLpin2, LOW);
            delay(500);
            Serial.println("fin");
        }
        else if(input == '3')
        {
            analogWrite(9, 70);
            analogWrite(13, 70);
            servoR.write(120);
       //     delay(10);
            servoL.write(110);
            delay(10);
            digitalWrite(motorRpin1, HIGH);
            digitalWrite(motorRpin2, LOW);
            digitalWrite(motorLpin1, HIGH);
            digitalWrite(motorLpin2, LOW);
            delay(500);
            Serial.println("fin");
        }
        else if(input == '4')
        {
            analogWrite(9, 70);
            analogWrite(13, 70);
            servoR.write(60);
         //   delay(10);
            servoL.write(50);
            delay(10);
            digitalWrite(motorRpin1, HIGH);
            digitalWrite(motorRpin2, LOW);
            digitalWrite(motorLpin1, HIGH);
            digitalWrite(motorLpin2, LOW);
            delay(500);
            Serial.println("fin");
        }
        else
        {
          analogWrite(9, 0);
          analogWrite(13, 0);
        }
    }
}

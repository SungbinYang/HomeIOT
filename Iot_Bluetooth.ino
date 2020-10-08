#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
#include "Servo.h" //서보 라이브러리

#define Sensing_pin 4  
 
Servo myservo1; //서보객체1
Servo myservo2;
int blueTx=2;   //Tx (블투 보내는핀 설정)
int blueRx=3;   //Rx (블투 받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
String myString=""; //받는 문자열
int led = 13;       // LED 핀 번호 13
int buzzer = 6;     // BUZZER 핀 번호 6
int flame = 8;      // 불꽃감지 센서 핀 번호 2
int state = 0;      // 불꽃감지 센서의 상태 값 저장 변수
 
void setup() {
  myservo1.attach(12);   //서보 시그널 핀설정
  myservo2.attach(10);
  myservo1.write(0);     //서보 초기각도 0도 설정
  myservo2.write(0);     //서보 초기각도 0도 설정
  mySerial.begin(9600); //블루투스 시리얼 개방
  pinMode(led, OUTPUT);    // LED를 출력으로 설정
  pinMode(buzzer, OUTPUT); // BUZZER를 출력으로 설정
  pinMode(flame, INPUT);   // 불꽃 감지 센서를 입력으로 설정
  Serial.begin(9600);      // 시리얼 통신, 속도는 9600
}
 
void loop() {
  while(mySerial.available())  //mySerial 값이 있으면
  {
    char myChar = (char)mySerial.read();  //mySerial int형식의 값을 char형식으로 변환
    myString+=myChar;   //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }
  
  if(!myString.equals(""))  //myString 값이 있다면
  {
    Serial.println("input value: "+myString); //시리얼모니터에 myString값 출력
 
      if(myString=="on")  //myString 값이 'on' 이라면
      {
        //문 각도 60도로 움직임
        myservo1.write(15);
        delay(30);
        myservo1.write(30);   
        delay(30);
        myservo1.write(45);
        delay(30);
        myservo1.write(60);
      } 
      if(myString=="1") {
        //창문 각도 40도로 움직임
        myservo2.write(10);   
        delay(30);
        myservo2.write(20);
        delay(30);
        myservo2.write(30);
        delay(30);
        myservo2.write(40);
      } 
      if(myString=="off") {
        // 문 닫아주기
        myservo1.write(60);
        delay(30);
        myservo1.write(45);
        delay(30);
        myservo1.write(30);
        delay(30);
        myservo1.write(15);
        delay(30);
        myservo1.write(0);
      } 
      if(myString=="0") {
        // 창문 닫아주기
        myservo2.write(40);
        delay(30);
        myservo2.write(30);
        delay(30);
        myservo2.write(20);
        delay(30);
        myservo2.write(10);
        delay(30);
        myservo2.write(0);
      }
    myString="";  //myString 변수값 초기화
  }
   state = digitalRead(flame);   // 불꽃 감지 센서값 입력받음

  digitalWrite(led, LOW);       // 초기 LED값을 0FF로 설정해주기
  noTone(buzzer);               // 초기에 BUZZER를 출력하지 않기.
  
  if (state == 0){              // 불꽃감지 센서의 값이 0일때(불꽃이 감지 되었을 때)
    Serial.println("ON");       // 시리얼 통신에 센서값 출력해 주기.
    digitalWrite(led, HIGH);    // LED ON
    tone(buzzer, 1000, 400);     // 1000 - 음의 높낮이, 400 - 부저 지속 시간
    delay(100);
  } else {
    Serial.println("OFF");      // 시리얼 통신에 센서값 출력해 주기.
    digitalWrite(led, LOW);     // LED OFF
    noTone(buzzer);             // BUZZER OFF              
  }
  if (digitalRead(Sensing_pin) == LOW)
  {
    Serial.println("detection");                     // 움직임이 감지됐어요!
  }
  else
  {
    Serial.println("not detection");                 // 움직임이 감지 되지 않았어요
  }
  delay(500);
}

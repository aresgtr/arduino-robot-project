#include <IRremote.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
int RECV_PIN = 13; //接收器在pin13
const int echopin=4; // echo接4端口 超声波
const int trigpin=7; // trig接7端口
float distance = pulseIn(echopin,HIGH);//接收高电平时间
float distance1;
float distance2;


IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(6,1); //pin6电机
  pinMode(5,1); //pin5电机
  pinMode(11,1); //pin11电机
  pinMode(10,1); //pin10电机
  pinMode(echopin,INPUT); //设定echo为输入模式
  pinMode(trigpin,OUTPUT);//设定trig为输出模式
  myservo.attach(8);  // attaches the servo on pin 8 to the servo object
}


void hcsr04()
{
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW); //发一个10ms的高脉冲去触发TrigPin
  float distance = pulseIn(echopin,HIGH);//接收高电平时间
  distance = distance/58.0;//计算距离
  Serial.print(distance);  //输出距离
  Serial.println("cm");  //输出单位
  delay(60);   //循环间隔60uS
}


void loop() 
{
  // put your main code here, to run repeatedly:
  hcsr04();
 
      myservo.write(92); //hcsr04向前
      if (distance>=20)
      {
        analogWrite(6,100); // forward control
        analogWrite(5,100);
        digitalWrite(11,0);
        digitalWrite(10,0);
      }
      else
      {
        digitalWrite(6,0); // stop moving
        digitalWrite(5,0);
        digitalWrite(11,0);
        digitalWrite(10,0);
      
        for (pos = 92; pos <= 180; pos += 2) { // goes from 92 degrees to 180 degrees
          // in steps of 1 degree
          distance1=distance;
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
        for (pos = 180; pos >= 20; pos -= 2) { // goes from 180 degrees to 20 degrees
          distance2=distance;
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
        
        if (distance2>=distance1) //右边距离大
        {
          digitalWrite(6,0); // spin right control
          analogWrite(5,100);
          digitalWrite(11,1);
          digitalWrite(10,0);
          delay(20);
          myservo.write(92);
          analogWrite(6,100); // forward control
          analogWrite(5,100);
          digitalWrite(11,0);
          digitalWrite(10,0);
        }
        if (distance2<distance1) //左边距离大
        {
          analogWrite(6,100); // spin left control
          digitalWrite(5,0);
          digitalWrite(11,0);
          analogWrite(10,100);
          delay(20);
          myservo.write(92);
          analogWrite(6,100); // forward control
          analogWrite(5,100);
          digitalWrite(11,0);
          digitalWrite(10,0);
        }
      }


 }


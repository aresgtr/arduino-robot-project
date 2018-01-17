const int echopin=3; // echo接3端口
const int trigpin=2; // trig接2端口
int led = 10; // led灯接10端口
void setup()
{
  Serial.begin(9600);  
  pinMode(echopin,INPUT); //设定echo为输入模式
  pinMode(trigpin,OUTPUT);//设定trig为输出模式
  pinMode(led,OUTPUT);//设定led为输出模式
}
void loop()
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

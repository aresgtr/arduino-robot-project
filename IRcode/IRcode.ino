/*
[url=http://www.openjumper.com/]www.openjumper.com[/url]
日期:2013.5.18
IDE 版本:1.0.1
功能：获取遥控器各按键的编码值
*/
 
#include <IRremote.h>
 
int RECV_PIN = 9; // 红外一体化接收头连接到Arduino 9号引脚
 
IRrecv irrecv(RECV_PIN);
 
decode_results results; // 用于存储编码结果的对象
 
void setup()
{
Serial.begin(9600); // 初始化串口通信
irrecv.enableIRIn(); // 初始化红外解码
}
 
void loop() {
if (irrecv.decode(&results)) {
Serial.println(results.value, HEX);
irrecv.resume(); // 接收下一个编码
}
}

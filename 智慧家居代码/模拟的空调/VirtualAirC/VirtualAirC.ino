#include <IRremote.h> 
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#define RECV_PIN  6 //设定接收红外线的引脚为11引脚
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);


IRrecv irrecv(RECV_PIN);                           //将红外线脚位设定为11号引脚
decode_results results; 
decode_results results2;//接收红外线引脚赋值
void setup()
{
  Serial.begin(115200); 
  irrecv.enableIRIn();   // 开始接收Start the receiver
  Serial.println("Enabled IRin"); //打印红外接收开始
  u8g2.begin();//构造U8G2，初始化显示器，重置清屏，唤醒屏幕
}

char* state="";//用来记住上次的模式
uint8_t temp;//记录温度

void loop() 
{
  //FLAG：
  state="natural";
  char temp_str[3];
  if (irrecv.decode(&results))// 解码成功，把数据放入results变量中
  {  
    
     Serial.println(results.value);//打印接收到的值
     Serial.print(temp_str);
     Serial.print(state);

     if(results.value==812647431)//打开空调
     { 
       delay(100);//消抖
       irrecv.resume();  //让接收器可以再接收
       state="NATURAL";
       temp=27;
       u8g2.firstPage();
       u8g2.setFont(u8g2_font_luIS12_tf);//设置字体集
       u8g2.drawStr(0,19,"STAT:");u8g2.drawStr(64,19,"ON");
       u8g2.drawStr(0,41,"MODE:");u8g2.drawStr(64,41,state);
       u8g2.drawStr(0,63,"TEMP:");u8g2.drawStr(64,63,"27");
       u8g2.nextPage();
        results2.value==results.value;
              while(results2.value!=812647430)
              {
              
                   u8g2.firstPage();
                  do 
                  {
                    u8g2.setFont(u8g2_font_luIS12_tf);//设置字体集
                    u8g2.drawStr(0,19,"STAT:");u8g2.drawStr(64,19,"ON");
                    u8g2.drawStr(0,41,"MODE:");u8g2.drawStr(64,41,state);
                    u8g2.drawStr(0,63,"TEMP:");u8g2.drawStr(64,63,temp_str);
                   }while ( u8g2.nextPage()/*参数没有改变*/ );
                   if(irrecv.decode(&results2)) Serial.println(results2.value);
                   switch(results2.value)
                    {
                    case 812647433:state="HEAT";break;//加热按键
                    case 812647434:state="COOL";break;//制冷
                   
                    case 812647437:state="NATURAL";break;//自然风
                    
                    case 812647435:temp++;break;
                    case 812647436:temp--;break; 
                    case 812647430:u8g2.initDisplay();break;
                    }
                  if(temp==16) temp=16;
                  if(temp==30) temp=30;
                  results2.value=00000000;
                  strcpy(temp_str, u8x8_u8toa(temp, 2));//将int类型的温度转换为2位的char类型
                  irrecv.resume();  // 继续等待接收下一组信号
               }
                
    }
    irrecv.resume();  // 继续等待接收下一组信号
   // goto FLAG;循环
  }              
  delay(100);//消抖
}



//打开空调：812647431
//关闭空调：812647430
//制热：812647433
//制冷：812647434
//温度增加：812647435
//温度降低：812647436
//自然风：812647437

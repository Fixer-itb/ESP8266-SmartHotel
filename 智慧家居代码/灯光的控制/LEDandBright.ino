#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>//需要16mhz Adafruit Trinket
#endif
#define PIN  5//定义D1为输入引脚
#define NUMPIXELS 3//有三个灯
#define BRIGHTNESS 153 //初始亮度为 5； 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int value = 0;//初始化亮度为0；
int bright = 0;//初始化灯的亮度；
String FLAG="OFF";
const char* ssid = "TP-LINK_648A";//连接的路由器的名字
const char* password = "369369369";//连接的路由器的密码
const char* mqtt_server = "106.52.105.247";//服务器的地址
const int   port=1883;//服务器端口号 
    
//const char* clientID = "{\"device\":\"LED\",\"key\":\"101LED\"}";//尽量保持唯一，相同的id连接会被替代
const char* clientID = "101LED";//尽量保持唯一，相同的id连接会被替代
const char* topic_name = "PEOPLE_101";//订阅的主题
const char* lightCtopic = "DEVICE/101/LED";//客户端主题
const char* lightAtopic = "ALL";//工作人员端主题
    
StaticJsonDocument<500> doc; //声明一个JsonDocument对象,用于LED的状态//
WiFiClient espClient;
PubSubClient client(espClient);
    //const char* answeron = "{\"ledStatus\":\"ON\"}";
    //const char* answeroff = "{\"ledStatus\":\"OFF\"}";

    //初始化程序，只运行一遍
void setup() 
{
    Serial.begin(115200);//设置串口波特率（与烧写用波特率不是一个概念）
    Serial.println();     //隔开乱码
    
    #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
      clock_prescale_set(clock_div_1);
    #endif
    pixels.setBrightness(BRIGHTNESS);
    pixels.begin(); //初始化NeoPixel strip对象(必选)
    pulseWhite(1,5);
    delay(10);
    pulseWhite(0,5);
  
    setup_wifi();//自动连WIFI接入网络
    client.setServer(mqtt_server, port);//端口号
    client.setCallback(callback); //用于接收服务器接收的数据,处理消息回调
}
    
    //初始化WIFI//自动连WIFI接入网络
void setup_wifi() 
{
    delay(10);
    WiFi.begin(ssid, password);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print("..."); 
    } 
    Serial.println("");
    Serial.println("WiFi connected");
}
    
    /*mqtt不会从loop（）调用回调，而是当Arduino收到有关已订阅的主题的MQTT消息时，
    MQTT库代码会调用该回调。*/
void callback(char* topic, byte* payload, unsigned int length) 
    /*接收MQTT数据topic（从哪个主题发过来的） payload把总的数据存入数组 length总的数据长度*/
{
    
    //int FLAG;//用于判断是否打开了灯
    String callMsg = "";//新建callmsg为字符串类型
    Serial.print("Message arrived [");Serial.print(topic);Serial.print("] ");   // 打印主题信息
    Serial.print("收到了： ");
    for (int i = 0; i < length; i++) 
    {
         callMsg += char(payload[i]);//把接收到的数据存入callMsg
    }
    Serial.println(callMsg);//打印收到了什么消息
      
      //反序列化JSON数据，把callMsg的JSON数据提取出来给doc
    DeserializationError error = deserializeJson(doc, callMsg); 
      

     //检查反序列化是否成功//这其中要接收两次数据，第一次是灯的操作，第二次是灯的亮度
    if (!error) 
    {
          //String ID=doc["key"];//接收房间号
          String ID=doc["c050596fd74ef3d2325420a9f6e59da6"];//接收房间号
          //String EQ=doc["device"];//设备名称
          String EQ=doc["8276e1aee751dbbc72cfdf1e9b1f129b"];//设备名称
          //String order1 = doc["ledOperate"];//接收的第一次JSON数据：对灯的操作//等同于const char *myC = doc["myChar"].as<char*>();
          String order1 = doc["70ada932e71aad20270f3451a9ac98a9"];//接收的第一次JSON数据：对灯的操作//等同于const char *myC = doc["myChar"].as<char*>()
          //String order2= doc["bright"];//接收的第二次JSON数据：灯的亮度，只在ledon的时候可操作
          int order2= doc["478a67e87bb7c38888656bad3dcc04b1"];//接收的第二次JSON数据：灯的亮度，只在ledon的时候可操作
                  
          
        Serial.println();
        Serial.print(ID);  
        Serial.print(EQ);
        Serial.print(order1);  
        Serial.print(order2);  
          //如果返回LED_ON打开LED
      //if(ID.equals("101PEOPLE")&&EQ.equals("LED"))
      if(ID.equals("aff61d2310122dfd88f419986150c2da")&&EQ.equals("faa989c74ad023a468b999d5393b7780"))
      {
        //if(order1.equals("LED_ON"))
        if(order1.equals("237d2c0656db7383b1fc77b1eea9a105"))
        {
          FLAG="ON";
           //client.publish(lightCtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"ledStatus\":\"ON\"}");
           //client.publish(lightCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"44770b5a68314487fbaee50f63b35e41\":\"836c6a9248c3f7fcec6a51e628567d3e\"}");
           //client.publish(lightAtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"ledStatus\":\"ON\"}");
           //client.publish(lightAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"44770b5a68314487fbaee50f63b35e41\":\"836c6a9248c3f7fcec6a51e628567d3e\"}");
           //String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",";
           //String msg2 = "\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",";
           //String msg3 = "\"44770b5a68314487fbaee50f63b35e41\":\"836c6a9248c3f7fcec6a51e628567d3e\"}";
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"c17c049409f82b68c9b66632bcf96ab5\",";
           String msg5 = "\"44770b5a68314487fbaee50f63b35e41\":";
           String msg6 = "\"836c6a9248c3f7fcec6a51e628567d3e\",";
           String msg7 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg8 = 3;
           String msg9 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length()+msg7.length()+1+msg9.length();
            client.beginPublish(lightCtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.print(msg8);
            client.print(msg9);
            client.endPublish();
            client.beginPublish(lightAtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.print(msg8);
            client.print(msg9);
            client.endPublish();
           value=6;
         
        }
        else if(order1.equals("63eed23e0eb39b784fb338d0c101a13d"))
        {
            FLAG=="OFF";
           //client.publish(lightCtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"ledStatu\":\"OFF\"}");
           //client.publish(lightCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"44770b5a68314487fbaee50f63b35e41\":\"53ce1f79ec026bb55e15bc7f6b6ab969\"}");
           //client.publish(lightAtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"ledStatu\":\"OFF\"}");
           //client.publish(lightAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"44770b5a68314487fbaee50f63b35e41\":\"53ce1f79ec026bb55e15bc7f6b6ab969\"}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"c17c049409f82b68c9b66632bcf96ab5\",";
           String msg5 = "\"44770b5a68314487fbaee50f63b35e41\":";
           String msg6 = "\"53ce1f79ec026bb55e15bc7f6b6ab969\"}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length();
            client.beginPublish(lightCtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.endPublish();
            client.beginPublish(lightAtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.endPublish();
           value = 0;//将值传给loop,loop一直在循环，不断接收到来自callback的值
        }

        if(order2==1&&FLAG=="ON") 
        {
          value=1;
          //client.publish(lightAtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"bright\":1}");
          //client.publish(lightAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"478a67e87bb7c38888656bad3dcc04b1\":1}");
          //client.publish(lightCtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"bright\":1}");
          //client.publish(lightCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"478a67e87bb7c38888656bad3dcc04b1\":1}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"c17c049409f82b68c9b66632bcf96ab5\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 1;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(lightCtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(lightAtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            //FLAG=0;
        }
        if(order2==2&&FLAG=="ON") 
        {
          value=3;
          //client.publish(lightAtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"bright\":1}");
          //client.publish(lightAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"478a67e87bb7c38888656bad3dcc04b1\":2}");
          //client.publish(lightCtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"bright\":1}");
          //client.publish(lightCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"478a67e87bb7c38888656bad3dcc04b1\":2}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"c17c049409f82b68c9b66632bcf96ab5\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 2;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(lightCtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(lightAtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish(); 
            //FLAG=0;   
        }
        if(order2==3&&FLAG=="ON") 
        {
          value=6;
          //client.publish(lightAtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"bright\":1}");
          //client.publish(lightAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"478a67e87bb7c38888656bad3dcc04b1\":3}");
          //client.publish(lightCtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"bright\":1}");
          //client.publish(lightCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"478a67e87bb7c38888656bad3dcc04b1\":3}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"c17c049409f82b68c9b66632bcf96ab5\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 3;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(lightCtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(lightAtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish(); 
            //FLAG=0;
        }
        if(order2==4&&FLAG=="ON") 
        {
          value=11;
          //client.publish(lightAtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"bright\":1}");
          //client.publish(lightAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"478a67e87bb7c38888656bad3dcc04b1\":4}");
          //client.publish(lightCtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"bright\":1}");
          //client.publish(lightCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"478a67e87bb7c38888656bad3dcc04b1\":4}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"c17c049409f82b68c9b66632bcf96ab5\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 4;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(lightCtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(lightAtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish(); 
            //FLAG=0;
        }
  
        if(order2==5&&FLAG=="ON") 
        {
          value=15;
          //client.publish(lightAtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"bright\":1}");
          //client.publish(lightAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"478a67e87bb7c38888656bad3dcc04b1\":5}");
          //client.publish(lightCtopic,"{\"device\":\"LED\",\"key\":\"101LED\",\"bright\":1}");
          //client.publish(lightCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"faa989c74ad023a468b999d5393b7780\",\"c050596fd74ef3d2325420a9f6e59da6\":\"c17c049409f82b68c9b66632bcf96ab5\",\"478a67e87bb7c38888656bad3dcc04b1\":5}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"c17c049409f82b68c9b66632bcf96ab5\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 5;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(lightCtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(lightAtopic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish(); 
            //FLAG=0;        
        }
          //如果返回LED_OFF关闭LED
        
      }
    }
}
    
    
    
   //等待，直到连接上服务器 
void reconnect() 
  {
      while (!client.connected()) 
      {//如果没有连接上
          Serial.print("Attempting MQTT connection...");
          if (client.connect(clientID)) 
          {
              Serial.println("MQTT连接成功");
              client.subscribe(topic_name,1);//订阅主题
          } 
          else 
          {
              Serial.print("failed, rc=");//连接失败
              Serial.print(client.state());//重新连接
              Serial.println(" try again in 5 seconds");//延时5秒后重新连接
              delay(5000);
          }
      }
}
//主循环
void loop() 
{
    if (value == 0)
    {
      pulseWhite(0,20); 
    }
    else 
    {
      pulseWhite(value*17,20);// 1，2，3,4,5个等级
    }
      if(!client.connected())
    {
        reconnect();
    }
     client.loop();      
}
void pulseWhite(uint8_t result,uint8_t wait) 
{  // 第一个参数为要变为的亮度值 第二个参数为变化间隔的时间单位为毫秒
  if (bright < result)
  {
    for(int j = bright; j < result ; j++)
    {
      for(uint16_t i=0; i<pixels.numPixels(); i++) 
      {
          pixels.setPixelColor(i, pixels.Color(j,j,j) );
      }
        delay(wait);
        pixels.show();
    }
      bright = result;
  }
  else if(bright > result)
  {
    for(int j = bright; j >= result ; j--)
    {
      for(uint16_t i=0; i<pixels.numPixels(); i++) 
      {
          pixels.setPixelColor(i, pixels.Color(j,j,j) );
      }
        delay(wait);
        pixels.show();
    }
      bright = result;
  }  
}

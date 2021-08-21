#include <PubSubClient.h>
#include <ESP8266WiFi.h>
const char* ssid = "TP-LINK_648A";          //连接的路由器的名字
const char* password = "369369369";         //连接的路由器的密码
const char* mqtt_server = "106.52.105.247"; //服务器的地址
const char* clientID ="{\"device\":\"speak\"}";   // 设备id

/*************************************对灯的控制*****************************************************/
int value = 3;//初始化亮度为3；
const char* control_topic = "PEOPLE_101";//客户端主题
/*************************************对灯的控制*****************************************************/

/*************************************对空调的控制*****************************************************/
/*************************************对空调的控制*****************************************************/
WiFiClient espClient;
PubSubClient client(espClient);

//初始化程序，只运行一遍
void setup() 
{
  Serial.begin(9600);                            //初始化通信波特率
  //Serial.begin(9600);
  setup_wifi();                     
  client.setServer(mqtt_server,1883);
}

//初始化WIFI//自动连WIFI接入网络
void setup_wifi() 
{
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print("...");
  }
}

  // 循环重新连接，直到连上
void reconnect() 
{
  while (!client.connected()) 
  {
    if (client.connect(clientID)) 
    {               
      Serial.print("MQTT连接成功");// 连接mqtt成功
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
  

void loop() 
{
//if(!client.connected())
//{
//  reconnect();
//}
//client.loop();
  
  String a;             //定义字符数组，接受来自上位机的数据
  
  while (!Serial.available()); //等待数据传送过来，若没有数据，一直等待，即执行到本行不向下执行
  while (Serial.available()) //当发现缓存中有数据时，将数据送至字符数组a中
  {
    a = Serial.readString();
    //delay(200);
  }
  Serial.println(a);
   delay(200);

   if(!client.connected())
{
  reconnect();
}
client.loop();
   if(a=="light_on")
   {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"70ada932e71aad20270f3451a9ac98a9\":";
           String msg6 = "\"237d2c0656db7383b1fc77b1eea9a105\"";
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length()+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
        }
   if(a=="light_off")
   {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"70ada932e71aad20270f3451a9ac98a9\":";
           String msg6 = "\"63eed23e0eb39b784fb338d0c101a13d\"";
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length()+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
    }
   if(a=="bright_up")
   {
    value++;
    if(value==1)
    {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 1;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
      }
         else if(value==2)
    {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 2;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
      }
         else if(value==3)
    {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 3;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
      }
         else if(value==4)
    {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 4;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
      }
          else if(value==5)
    {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 5;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
      }
     else if(value>5)value=5;
     else if(value<1)value=1;
      Serial.println(value);
 //     break;
   }
   if(a=="bright_down")
   {
    value--;
    if(value==1)
    {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 1;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
      }
         else if(value==2)
    {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 2;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
      }
         else if(value==3)
    {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 3;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
      }
         else if(value==4)
    {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 4;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
      }
          else if(value==5)
    {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"faa989c74ad023a468b999d5393b7780\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"478a67e87bb7c38888656bad3dcc04b1\":";
           int msg6 = 5;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+1+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
      }
      else if(value>5)value=5;
      else if(value<1)value=1;
      Serial.println(value);
      
    }
   if(a=="air_on")
   {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"675acff3d9441e5c0e1b0333000e8369\":";
           String msg6 = "\"1ae0e709f8c464612151ef4e9a82ab41\"";
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length()+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
    }
   if(a=="air_off")
   {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"675acff3d9441e5c0e1b0333000e8369\":";
           String msg6 = "\"89eab8a9179b10ae51e37294685a1da3\"";
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length()+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
    }
   if(a=="air_heat")
   {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"7ecfb285d06e3798f3d0c9165cbd61a0\":";
           String msg6 = "\"7d795952f8a1530f5fbf2b544f26317a\"";
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length()+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
    }   
    if(a=="air_cool")
   {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"7ecfb285d06e3798f3d0c9165cbd61a0\":";
           String msg6 = "\"fdd990ab0b92f64d79924fbc2590377b\"";
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length()+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
    }
    if(a=="temp_up")
   {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"19e605b464ab6dda66f333921d34065a\":";
           String msg6 = "\"1a95a8ec55467c7bd1649de3096cbc49\"";
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length()+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
    }
    if(a=="temp_down")
   {
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\":";
           String msg2 = "\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"aff61d2310122dfd88f419986150c2da\",";
           String msg5 = "\"19e605b464ab6dda66f333921d34065a\":";
           String msg6 = "\"d7228b627dd5efd0ccc1a46b99485d76\"";
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length()+msg7.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
    }
  if(a=="curtain_on")
  {
           String msg1 = "{\"state\":";
           int msg2 = 1;
           String msg3 = "}";
           int msgLen = msg1.length() + 1 + msg3.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.endPublish();  
  }
  if(a=="curtain_off")
  {
           String msg1 = "{\"state\":";
           int msg2 = -1;
           String msg3 = "}";
           int msgLen = msg1.length() + 1 + msg3.length();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.endPublish();
            client.beginPublish(control_topic, msgLen, false);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.endPublish();  
  }
    
}
//  Serial.println(a);
//  delay(2000);

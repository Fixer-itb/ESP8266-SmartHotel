#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#define IR_LED 5  //ESP8266 GPIO 引脚使用。推荐： 4 （D1）
int i=27;

IRsend irsend(IR_LED);  // 将 GPIO4 设置为用于发送消息
    
    const char* ssid = "TP-LINK_648A";//连接的路由器的名字
    const char* password = "369369369";//连接的路由器的密码
    const char* mqtt_server = "106.52.105.247";//服务器的地址
    const int   port=1883;//服务器端口号 
    const char* clientID = "AIR101";//尽量保持唯一，相同的id连接会被替代
    
    const char* topic_name = "PEOPLE_101";//订阅的主题
    const char* AirCtopic = "DEVICE/101/AIR";//客户端主题
    const char* AirAtopic = "ALL";//工作人员端主题

    StaticJsonDocument<500> doc; //声明一个JsonDocument对象,用于对灯的操作的状态//
    WiFiClient espClient;
    PubSubClient client(espClient);
    
    //初始化程序，只运行一遍
    void setup() 
    {
      Serial.begin(115200);//设置串口波特率（与烧写用波特率不是一个概念）
      Serial.println();     //隔开乱码
      irsend.begin();
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


    void callback(char* topic, byte* payload, unsigned int length) 
    /*接收MQTT数据topic（从哪个主题发过来的） payload把总的数据存入数组 length总的数据长度*/
    {
      String callMsg = "";//新建callmsg为字符串类型
      //Serial.print("Message arrived [");Serial.print(topic);Serial.print("] ");   // 打印主题信息
      //Serial.print("收到了： ");
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
          //String order1 = doc["airOperate"];//接收的第一次JSON数据：对灯的操作//等同于const char *myC = doc["myChar"].as<char*>();
          String order1 = doc["675acff3d9441e5c0e1b0333000e8369"];
          //String order2 = doc["airMode"];//接收的第2次JSON数据：
          String order2 = doc["7ecfb285d06e3798f3d0c9165cbd61a0"];//接收的第2次JSON数据：
          //String order3 = doc["airControl"];//接收的第3次JSON数据：
          String order3 = doc["19e605b464ab6dda66f333921d34065a"];//接收的第3次JSON数据：
          Serial.println();
          Serial.print(ID);  
          Serial.print(EQ);
          Serial.print(order1); 
          Serial.print(order2);
          Serial.print(order3);
          //如果返回LED_ON打开LED
        //if(ID.equals("101PEOPLE")&&EQ.equals("AIR"))
        if(ID.equals("aff61d2310122dfd88f419986150c2da")&&EQ.equals("0a56fe9a197d559acc6efca0ebd768b7"))
        {
          //if(order1.equals("AIR_ON"))
          if(order1.equals("1ae0e709f8c464612151ef4e9a82ab41"))
          {
             i=27;
           irsend.sendNEC(812647431);
           Serial.println(812647431);
           //client.publish(AirAtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\",\"AirStatus\":\"ON\"}");
           //client.publish(AirAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\",\"cb012e420d12c0badea30d426754bfb5\":\"836c6a9248c3f7fcec6a51e628567d3e\"}");
           //client.publish(AirCtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\",\"AirStatus\":\"ON\"}");
           //client.publish(AirAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\",\"cb012e420d12c0badea30d426754bfb5\":\"836c6a9248c3f7fcec6a51e628567d3e\"}");
           //client.publish(AirCtopic,"{\"AirStatus\":\"ON\",\"airPattern\":\"natural\",\"aircTemperature\":27}");//给客户发送状态
           //client.publish(AirCtopic,"{\"cb012e420d12c0badea30d426754bfb5\":\"836c6a9248c3f7fcec6a51e628567d3e\",\"6e0ebe1f718b0d20f70e7953142aeb8f\":\"natural\",\"314d7941e84e91fcbec82ff587b1f399\":27}");
           //client.publish(AirAtopic,"{\"AirStatus\":\"ON\",\"airPattern\":\"natural\",\"aircTemperature\":27}");//给工作人员发送状态
           //client.publish(AirAtopic,"{\"cb012e420d12c0badea30d426754bfb5\":\"836c6a9248c3f7fcec6a51e628567d3e\",\"6e0ebe1f718b0d20f70e7953142aeb8f\":\"natural\",\"314d7941e84e91fcbec82ff587b1f399\":27}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"729af9a68500486a7130abcaa8285ce4\",";
           String msg5 = "\"cb012e420d12c0badea30d426754bfb5\":";
           String msg6 = "\"836c6a9248c3f7fcec6a51e628567d3e\"}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length();
            client.beginPublish(AirCtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.endPublish();
            client.beginPublish(AirAtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.endPublish();
           
          }
          //if(order2.equals("AIR_HEAT"))
          if(order2.equals("7d795952f8a1530f5fbf2b544f26317a"))
           {
            //client.publish(AirAtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\",\"airPattern\":\"HEAT\"}");
            //client.publish(AirAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\",\"6e0ebe1f718b0d20f70e7953142aeb8f\":\"1a0691e7829597c7d9265c8d1d194621\"}");
            //client.publish(AirCtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\",\"airPattern\":\"HEAT\"}");
            //client.publish(AirCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\",\"6e0ebe1f718b0d20f70e7953142aeb8f\":\"1a0691e7829597c7d9265c8d1d194621\"}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"729af9a68500486a7130abcaa8285ce4\",";
           String msg5 = "\"6e0ebe1f718b0d20f70e7953142aeb8f\":";
           String msg6 = "\"1a0691e7829597c7d9265c8d1d194621\"}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length();
            client.beginPublish(AirCtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.endPublish();
            client.beginPublish(AirAtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.endPublish();
            irsend.sendNEC(812647433);
            Serial.println(812647433);
           }
          //if(order2.equals("AIR_COOL"))
          if(order2.equals("fdd990ab0b92f64d79924fbc2590377b"))
           {
            irsend.sendNEC(812647434);
            //client.publish(AirAtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\",\"airPattern\":\"COOL\"}");
            //client.publish(AirAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\",\"6e0ebe1f718b0d20f70e7953142aeb8f\":\"99ef072db061f69ff1038f84db116474\"}");
            //client.publish(AirCtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\",\"airPattern\":\"COOL\"}");
            //client.publish(AirCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\",\"6e0ebe1f718b0d20f70e7953142aeb8f\":\"99ef072db061f69ff1038f84db116474\"}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"729af9a68500486a7130abcaa8285ce4\",";
           String msg5 = "\"6e0ebe1f718b0d20f70e7953142aeb8f\":";
           String msg6 = "\"99ef072db061f69ff1038f84db116474\"}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length();
            client.beginPublish(AirCtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.endPublish();
            client.beginPublish(AirAtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.endPublish(); 
           }

           
           //自然风AIR_NATUREmaninthestreet:
            if(order2.equals("8c8f31cd23b773a891024035c1706f2c"))
           {
            irsend.sendNEC(812647437);
            //client.publish(AirAtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\",\"airPattern\":\"NATURE\"}");
            //client.publish(AirAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\",\"6e0ebe1f718b0d20f70e7953142aeb8f\":\"99ef072db061f69ff1038f84db116474\"}");
            //client.publish(AirCtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\",\"airPattern\":\"NATURE\"}");
            //client.publish(AirCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\",\"6e0ebe1f718b0d20f70e7953142aeb8f\":\"99ef072db061f69ff1038f84db116474\"}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"729af9a68500486a7130abcaa8285ce4\",";
           String msg5 = "\"6e0ebe1f718b0d20f70e7953142aeb8f\":";
           String msg6 = "\"f7beedb5320fc2c1bef3c4d07d7e4e4c\"}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length();
            client.beginPublish(AirCtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.endPublish();
            client.beginPublish(AirAtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.endPublish(); 
           }



           
           //if(order3.equals("TempAdd"))
           if(order3.equals("1a95a8ec55467c7bd1649de3096cbc49"))
           {
            i++;
            irsend.sendNEC(812647435);
            //client.publish(AirAtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\"}");
            //client.publish(AirAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\"}");
            //client.publish(AirCtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\"}");
            //client.publish(AirCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\"}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"729af9a68500486a7130abcaa8285ce4\",";
           String msg5 = "\"314d7941e84e91fcbec82ff587b1f399\":";
           int msg6 = i;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+2+msg7.length();
            client.beginPublish(AirCtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(AirAtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
           }
           //if(order3.equals("TempMin"))
           if(order3.equals("d7228b627dd5efd0ccc1a46b99485d76"))
           {
            i--;
            irsend.sendNEC(812647436);
            //client.publish(AirAtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\"}");
            //client.publish(AirAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\"}");
            //client.publish(AirCtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\"}");
            //client.publish(AirCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\"}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"729af9a68500486a7130abcaa8285ce4\",";
           String msg5 = "\"314d7941e84e91fcbec82ff587b1f399\":";
           int msg6 = i;
           String msg7 = "}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+2+msg7.length();
            client.beginPublish(AirCtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
            client.beginPublish(AirAtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.print(msg7);
            client.endPublish();
           }
          //if(order1.equals("AIR_OFF"))
          if(order1.equals("89eab8a9179b10ae51e37294685a1da3"))
          {
           //client.publish(AirAtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\",\"airStatus\":\"OFF\"}");
           //client.publish(AirAtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\",\"cb012e420d12c0badea30d426754bfb5\":\"53ce1f79ec026bb55e15bc7f6b6ab969\"}");
           //client.publish(AirCtopic,"{\"device\":\"AIR\",\"key\":\"101AIR\",\"airStatus\":\"OFF\"}");
           //client.publish(AirCtopic,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0a56fe9a197d559acc6efca0ebd768b7\",\"c050596fd74ef3d2325420a9f6e59da6\":\"729af9a68500486a7130abcaa8285ce4\",\"cb012e420d12c0badea30d426754bfb5\":\"53ce1f79ec026bb55e15bc7f6b6ab969\"}");
           String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
           String msg2 = ":\"0a56fe9a197d559acc6efca0ebd768b7\",";
           String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
           String msg4 = "\"729af9a68500486a7130abcaa8285ce4\",";
           String msg5 = "\"cb012e420d12c0badea30d426754bfb5\":";
           String msg6 = "\"53ce1f79ec026bb55e15bc7f6b6ab969\"}";
           int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+msg6.length();
            client.beginPublish(AirCtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.endPublish();
            client.beginPublish(AirAtopic, msgLen, true);
            client.print(msg1);
            client.print(msg2);
            client.print(msg3);
            client.print(msg4);
            client.print(msg5);
            client.print(msg6);
            client.endPublish();
           irsend.sendNEC(812647430);
          }
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
          client.subscribe(topic_name);//订阅主题
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
      if(!client.connected())
      {
        reconnect();
      }
        client.loop();      
    }


/*.
接收命令
打开空调：812647431
关闭空调：812647430
制热：812647433
制冷：812647434
温度增加：812647435
温度降低：812647436
自然风：812647437
*/

    

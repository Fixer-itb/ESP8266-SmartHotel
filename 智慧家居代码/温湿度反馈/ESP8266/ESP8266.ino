#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <SimpleDHT.h>
#include <ArduinoJson.h>

int pinDHT11 = 2;                           //esp8266用gpio2脚
const char* ssid = "TP-LINK_648A";          //连接的路由器的名字
const char* password = "369369369";         //连接的路由器的密码
const char* mqtt_server = "106.52.105.247"; //服务器的地址
const char* clientID ="{\"device\":\"T&H\"}";            // 设备id
const char* topic_name = "PEOPLE_101";//订阅的主题
const char* Ctopic_name = "DEVICE/101/T&W";         //发送的主题
const char* Atopic_name = "ALL";

WiFiClient espClient;
PubSubClient client(espClient);
SimpleDHT11 dht11(pinDHT11);    //初始化数据GPIO

//初始化程序，只运行一遍
void setup() 
{
  Serial.begin(115200);
  setup_wifi();                     
  client.setServer(mqtt_server,1883);
  client.setCallback(callback);
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

/*接收MQTT数据topic（从哪个主题发过来的） payload把总的数据存入数组 length总的数据长度*/
void callback(char* topic,byte* payload, unsigned int length)
{
  Serial.print("Message arrived ["); Serial.print(topic); Serial.print("] ");
 
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
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
      client.subscribe(topic_name);// 一旦连接，订阅主题
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
if(!client.connected())
{
  reconnect();
}
 client.loop();
  // DHT11开始干活
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;               //接收数据0-255
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
//   String tmp = "temp:";            //字符串拼接
//   tmp += String(temperature);
//   tmp += String("humi:");
//   tmp += String(humidity);
   //String tmp = "{\"roomTemperature\":";
   
//   String tmp = "{\"71247ed4e16f1965b1c23685f7cff83e\":";            
//   tmp += String(temperature);
//   tmp += String(",");
//   //tmp += String("\"humidity\":");
//   tmp += String("\"1e40da25eafb5b2ade2f91e305ad0aaf\":");
//   tmp += String(humidity);
//   tmp += String("}");
  
  
  Serial.print("Sample OK: ");
  Serial.print(temperature); Serial.print(" ℃, "); 
  Serial.print(humidity); Serial.println(" H");
  String msg1 = "{\"8276e1aee751dbbc72cfdf1e9b1f129b\"";
  String msg2 = ":\"0b92f84a68b615c435ac1cf2c4237222\",";
  String msg3 = "\"c050596fd74ef3d2325420a9f6e59da6\":";
  String msg4 = "\"99183d0c6b47f43ca10514d62b7ed22b\",";
  String msg5 = "\"83af065e2f500111328da91be3361872\":";
  int msg6 = temperature;
  String msg7 = ",";
  String msg8 = "\"979a02b371a8c5be7ce7f71e4696ac3f\":";
  int msg9 = humidity;
  String msg10="}";
  int msgLen = msg1.length() + msg2.length() + msg3.length()+msg4.length()+msg5.length()+2+msg7.length()+msg8.length()+2+msg10.length();
  client.beginPublish(Ctopic_name, msgLen, true);
  client.print(msg1);
  client.print(msg2);
  client.print(msg3);
  client.print(msg4);
  client.print(msg5);
  client.print(msg6);
  client.print(msg7);
  client.print(msg8);
  client.print(msg9);
  client.print(msg10);
  client.endPublish();
    client.beginPublish(Atopic_name, msgLen, true);
  client.print(msg1);
  client.print(msg2);
  client.print(msg3);
  client.print(msg4);
  client.print(msg5);
  client.print(msg6);
  client.print(msg7);
  client.print(msg8);
  client.print(msg9);
  client.print(msg10);
  client.endPublish();
  //client.publish(Ctopic_name,"{\"device\":\"T&W\",\"key\":\"101T&W\"}");
  //client.publish(Ctopic_name,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0b92f84a68b615c435ac1cf2c4237222\",\"c050596fd74ef3d2325420a9f6e59da6\":\"99183d0c6b47f43ca10514d62b7ed22b\"}");
  //client.publish(Atopic_name,"{\"device\":\"T&W\",\"key\":\"101T&W\"}");
  //client.publish(Ctopic_name,"{\"8276e1aee751dbbc72cfdf1e9b1f129b\":\"0b92f84a68b615c435ac1cf2c4237222\",\"c050596fd74ef3d2325420a9f6e59da6\":\"99183d0c6b47f43ca10514d62b7ed22b\"}");
  //client.publish(Ctopic_name,tmp.c_str()); //发送主题和内容
  //client.publish(Atopic_name,tmp.c_str()); //发送主题和内容
  delay(3000);
}

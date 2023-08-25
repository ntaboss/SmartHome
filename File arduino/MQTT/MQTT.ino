#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "LAB 204";
const char* password = "lab20481011167@";

#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT 1883
#define MQTT_USER "anh.nt194903"
#define MTQQ_PASSWORD "Tuan16092001@"

#define MQTT_LED1_TOPIC "MQTT_ESP32/LED1"
#define MQTT_LED2_TOPIC "MQTT_ESP32/LED2"

#define LED1 12
#define LED2 13
#define BUT1 14

String ledStatus1;
String ledStatus2;

WiFiClient espClient;
PubSubClient client(espClient);

//****************************************************************
void setup_wifi(){
  Serial.print("connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wifi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void connect_to_broker(){
  // Lặp tới khi được kết nối
  while(!client.connected()){
    Serial.print("Attemping MQTT connection...");
    //Tạo một ID client ngẫu nhiên
    String clientId = "ESP32";
    clientId += String(random(0xffff), HEX);
    //Attempt to connect
    if (client.connect(clientId.c_str())){
      Serial.println("connected");
      client.subscribe(MQTT_LED1_TOPIC);
      client.subscribe(MQTT_LED2_TOPIC);
    } else{
      Serial.println("try again in 2 seconds");
      //Đợi 2s để kết nối lại
      delay(2000);
    }
  }
}
//nhận message from broker
void callback(char* topic, byte* payload, unsigned int length){
  char stt[20];
  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.println("message: ");
  for( int i = 0; i<length;i++){
    Serial.print((char)payload[i]);
    stt[i] = payload[i];
  }
  if(String(topic) == MQTT_LED1_TOPIC){
    if(String(stt) == "OFF"){
      ledStatus1 = "OFF";
      digitalWrite(LED1, LOW);
      Serial.println(" LED1 OFF");
    }
    else if(String(stt) == "ON"){
      ledStatus1 = "ON";
      digitalWrite(LED1, HIGH);
      Serial.println(" LED1 ON");
    }
  }

  if(String(topic) == MQTT_LED2_TOPIC){
    if(String(stt) == "OFF"){
      ledStatus2 = "OFF";
      digitalWrite(LED2, LOW);
      Serial.println(" LED2 OFF");
    } 
    else if(String(stt) == "ON"){
      ledStatus2 = "ON";
      digitalWrite(LED2, HIGH);
      Serial.println(" LED2 ON");
    }
  }
}
//****************************************************************
void setup(){
  Serial.begin(115200);
  Serial.setTimeout(500);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  connect_to_broker();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUT1, INPUT);
}

void loop(){
  client.loop();
  if(!client.connected()){
    connect_to_broker();
  } 
  if(digitalRead(BUT1) == 1){
    while(digitalRead(BUT1) == 1){
      }
    if(ledStatus1 == "ON"){
      client.publish(MQTT_LED1_TOPIC, "OFF");
      ledStatus1 = "OFF";
    }
    else if(ledStatus1 == "OFF"){
      client.publish(MQTT_LED1_TOPIC, "ON");
      ledStatus1 = "ON";
    }
  }
}

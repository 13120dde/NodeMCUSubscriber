#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "YourNetworkName";
const char* password =  "YourNetworkPassword";
const char* mqttServer = "m23.cloudmqtt.com";
const int mqttPort = 14381;
const char* mqttUser = "bjbvmjbc";
const char* mqttPassword = "3ZSXthhxYYoW";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {

  pinMode(D1, OUTPUT);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("androidkt/topic", "Arduino connected");
  client.subscribe("androidkt/topic");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  char msg[length];
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    msg[i]=(char) payload[i];
  }

  if(msg == "Led on"){
     digitalWrite(D1, HIGH);
  }
  else if (msg =="Led off"){
    digitalWrite(D1, LOW);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
}

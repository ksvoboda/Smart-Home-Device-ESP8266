#include "firmwareUpdate.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "curry";
const char* password = "Papagaj43*";

#define MSG_BUFFER_SIZE  (50)

void setup() {

  Serial.begin(115200);
  
  delay(2000);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    
    delay(500);
    Serial.print(".");
    
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqttClient.setServer(mqtt_server, mqttPort);
  mqttClient.setCallback(callback);
  
  firmwareUpdate();
  
}

void loop() {

  if (!mqttClient.connected()) {
    
    reconnect();
    
  }
  
  mqttClient.loop();
  
}

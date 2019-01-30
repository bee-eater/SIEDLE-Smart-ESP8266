#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/*--------------------------------------------*/
/* DEFAULT VALUES                             */
/*--------------------------------------------*/
#define WIFI_RECONNECT      5000    // Delay between wifi reconnection tries
#define MQTT_RECONNECT      5000    // Delay between mqtt reconnection tries

// GPIO settings
#define INPUT_PIN     1             // GPIO1 -> Rx pin as input for doorbell recognition
#define OUTPUT_PIN    2             // GPIO2 -> Output for door opener

// Basic app settings
#define ENABLE_DOOROPEN     false   // If enabled, door can be opened with payload DOOROPEN_KEYWORD in MQTT_TOPIC
#define DOOROPEN_KEYWORD    "open"  // Keyword in MQTT_TOPIC which opens the door (if enabled)
#define DOORBELL_KEYWORD    "ring"  // Message that is published to MQTT_TOPIC if doorbell rings 

#include "SiedleESP.h"
 
/*--------------------------------------------*/
/* BASIC SETUP                                */
/*--------------------------------------------*/
void setup() {
    
    // Only use TX pin -> RX is input from doorbell
    Serial.begin(115200,SERIAL_8N1,SERIAL_TX_ONLY);
    Serial.println();

    cfg.wifiSSID   = "SSID";
    cfg.wifiPass   = "password";
    cfg.wifiHost   = "TestESP";
    cfg.mqttBroker = "192.168.178.10";
    cfg.mqttPort   = "1883";
    cfg.mqttUser   = "";
    cfg.mqttPass   = "";
    cfg.mqttClient = "TestESP";
    cfg.mqttTopic  = "home/general/testesp";
    
    app.debounceTime = 10000;
    app.openDuration = 3000;
    
    // Configure wifi
    setupWifi();
    setupMQTT();

    // Project dependent
    setupGPIO();

}

/*--------------------------------------------*/
/* CHECK WIFI                                 */
/*--------------------------------------------*/
void check_wifi(){

    // Check WiFi connectivity
   int wifi_retry = 0;
   while(WiFi.status() != WL_CONNECTED && wifi_retry < 5 ) {
     wifi_retry++;
     Serial.printf("WiFi not connected. Trying to connect...");
     WiFi.disconnect();
     WiFi.mode(WIFI_OFF);
     delay(10);
     WiFi.mode(WIFI_STA);
     WiFi.begin(cfg.wifiSSID.c_str(), cfg.wifiPass.c_str());
     delay(WIFI_RECONNECT);
   }
   if(wifi_retry >= 5) {
     Serial.println("\nWifi connection not possible, rebooting...");
     ESP.restart();
   } else if (wifi_retry > 0){
     Serial.println("WiFi reconnected");
     Serial.println("IP address: ");
     Serial.println(WiFi.localIP());
   }
}

/*--------------------------------------------*/
/* CHECK MQTT                                 */
/*--------------------------------------------*/
void check_mqtt(){

    // Check MQTT connectivity
    int mqtt_retry = 0;
    bool res;
    
    if (!client.connected()) {
        while (!client.connected() && mqtt_retry < 5 && WiFi.status() == WL_CONNECTED) {
            mqtt_retry++;
            Serial.print("MQTT not connected, connecting to MQTT broker...");
            if(cfg.mqttUser == ""){
              res = client.connect(cfg.mqttClient.c_str());
            } else {
              res = client.connect(cfg.mqttClient.c_str(), cfg.mqttUser.c_str(), cfg.mqttPass.c_str());
            }
            if (!res) {
                Serial.print("failed, rc=");
                Serial.print(client.state());
                Serial.print(", retrying in 1 second");
                delay(MQTT_RECONNECT);
            } else {
                if(ENABLE_DOOROPEN){
                  client.subscribe(cfg.mqttTopic.c_str());
                }
            }
            
        }
        if(WiFi.status() != WL_CONNECTED){
          Serial.println("Not connected to WiFi!");
        }
        if(mqtt_retry >= 5){
          Serial.print("MQTT connection not possible, rebooting...");
          ESP.restart();
        }
    } 
}

/*--------------------------------------------*/
/* CYCLIC FUNCTION                            */
/*--------------------------------------------*/
void loop() {

    /*-----------------------------------*/
    /* Base stuff                        */
    /*-----------------------------------*/
    check_wifi();
    check_mqtt();
    client.loop();

    /*-----------------------------------*/
    /* Project stuff                     */
    /*-----------------------------------*/
    if(gDoorOpened && client.connected() && WiFi.status() == WL_CONNECTED){
    
      if(client.publish(cfg.mqttTopic.c_str(), DOORBELL_KEYWORD)){
        Serial.println("Successfully published!");
        gDoorOpened = 0;
      } else {
        Serial.println("Failed publishing!");
      }
    
    } else if (gDoorOpened){
      
      if (!client.connected()){
        Serial.println("Not connected to MQTT broker!");
      }
      if(WiFi.status() != WL_CONNECTED){
        Serial.println("Not connected to WiFi!");
      }
        
    }

}

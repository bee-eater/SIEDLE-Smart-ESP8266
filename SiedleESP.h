#ifndef SIEDLE_ESP_H
#define SIEDLE_ESP_H

/*--------------------------------------------*/
/* CONFIG STRUCTURES                          */
/*--------------------------------------------*/
typedef struct {
  String wifiSSID;            // WiFi name
  String wifiPass;            // WiFi password
  String wifiHost;            // WiFi hostname of this ESP
  String mqttBroker;          // IP of MQTT broker
  String mqttPort;            // Port of MQTT broker
  String mqttUser;            // Username for MQTT broker
  String mqttPass;            // Password for MQTT broker
  String mqttClient;          // MQTT client id of this ESP
  String mqttTopic;           // Topic for recognition and cmnd
} config_t;
config_t cfg;

// App config structure
typedef struct {
  unsigned int debounceTime;  // [ms] Debouncing time for interrupt input
  unsigned int openDuration;  // [ms] Time how long door opener should be "pressed"
} app_t;
app_t app;

/*--------------------------------------------*/
/* GLOBAL VARIABLES                           */
/*--------------------------------------------*/
WiFiClient espClient;
PubSubClient client(espClient);
volatile bool gDoorOpened = 0;

/*--------------------------------------------*/
/* INTERRUPT WHEN INPUT COMES                 */
/*--------------------------------------------*/
void handleInterrupt(){
    
    // Debounce using millis
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    
    // If interrupts come faster than 10s, ignore it
    if (interrupt_time - last_interrupt_time > app.debounceTime){
      gDoorOpened = 1;
    }
    last_interrupt_time = interrupt_time;
    
}

/*--------------------------------------------*/
/* MQTT CALLBACK FUNCTION                     */
/*--------------------------------------------*/
void mqttCallback(char* topic, byte* payload, unsigned int length) {

    // Check if topic is correct
    payload[length] = '\0';
    if(strcmp(topic, cfg.mqttTopic.c_str()) == 0){
        // Check if received open command
        if(strcmp((const char*)payload, DOOROPEN_KEYWORD) == 0){
             digitalWrite(OUTPUT_PIN, HIGH);
             delay(app.openDuration);
             digitalWrite(OUTPUT_PIN, LOW);
        }
    }
}

/*--------------------------------------------*/
/* CONFIGURE GPIO                             */
/*--------------------------------------------*/
void setupGPIO(){
  
    // Use GPIO1 (Rx) as inputm, GPIO2 as output
    pinMode(INPUT_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(INPUT_PIN), handleInterrupt, FALLING);
    
    // Set callback function if door opening is enabled
    if(ENABLE_DOOROPEN){
      pinMode(OUTPUT_PIN, OUTPUT);
      client.setCallback(mqttCallback);
    }
    
}

/*--------------------------------------------*/
/* SETUP WIFI                                 */
/*--------------------------------------------*/
void setupWifi() {
  
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(cfg.wifiSSID);
 
    WiFi.begin(cfg.wifiSSID.c_str(), cfg.wifiPass.c_str());
    wifi_station_set_hostname((char*)cfg.wifiHost.c_str());
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
}

/*--------------------------------------------*/
/* SETUP MQTT                                 */
/*--------------------------------------------*/
void setupMQTT(){
    client.setServer(cfg.mqttBroker.c_str(), cfg.mqttPort.toInt());
}

#endif

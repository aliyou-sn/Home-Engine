#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h> 
#include "setup.h"

                            
String deviceName = "Home_Engine";                          		
String  TopicRelay1 = "Home_Engine/relay1";       			
WiFiClient wiFiClient;
PubSubClient mqttPubSub(wiFiClient);
String UniqueId;
byte  RelayStatus1 = RELAY_OFF;
byte Input1 = 0;
byte state_input1 = SWITCH_OFF;

void setup_wifi();
void MqttReconnect();
void MqttHomeAssistantDiscovery();
void MqttReceiverCallback(char* , byte*, unsigned int);
void MqttPublishStatus_Relay1();

void setup(){
    pinMode(Switch1, INPUT_PULLUP);
    pinMode(RELAY1, OUTPUT);
    Serial.begin(115200);
    delay(500);
    Serial.println("");
    Serial.println("----------------------------------------------");
    Serial.print("MODEL: ");
    Serial.println(deviceModel);
    Serial.print("DEVICE: ");
    Serial.println(deviceName);
    Serial.print("Software Rev: ");
    Serial.println(Version);
    Serial.println("----------------------------------------------");
    setup_wifi();
    mqttPubSub.setServer(mqtt_server, mqttPort);
    mqttPubSub.setCallback(MqttReceiverCallback);
}

void loop(){
    if(WiFi.status() == WL_CONNECTED)
    {
        if(!mqttPubSub.connected())
            MqttReconnect();
        else
            mqttPubSub.loop();
    }
    if(InitSystem)
    {
        delay(1000);
        InitSystem = false;
		    Serial.println("INIT SYSTEM...");
        MqttHomeAssistantDiscovery();
    }

    // Inputs Monitor
    if(millis() - TimeInputs > 200){
        TimeInputs = millis();

        switch(state_input1){
            case SWITCH_OFF:
            {
                if(digitalRead(Switch1) == 1){
                    state_input1 = CHECKING;
                }
            } break;

            case CHECKING:
            {
                if(digitalRead(Switch1) == 1){
                    state_input1 = SWITCH_ON;
                    Input1 = 1;
                    RelayStatus1 = RELAY_ON;
                    digitalWrite(RELAY1, RelayStatus1);
                }
                else if(digitalRead(Switch1) == 0){                      
                    state_input1 = SWITCH_OFF;
                    Input1 = 0;
                    RelayStatus1 = RELAY_OFF;
                    digitalWrite(RELAY1, RelayStatus1);
                }
                    MqttPublishStatus_Relay1();

            } break;

            case SWITCH_ON:
            {
                if(digitalRead(Switch1) == 0){
                    state_input1 = CHECKING;
                }
            } break;
        }
    }
}

void setup_wifi(){
    int counter = 0;
    byte mac[6];
    delay(10);
    WiFi.begin(ssid, password);
    WiFi.macAddress(mac);
    UniqueId =  String(mac[0],HEX) + String(mac[1],HEX) + String(mac[2],HEX) + String(mac[3],HEX) + String(mac[4],HEX) + String(mac[5],HEX);

    while(WiFi.status() != WL_CONNECTED && counter++ < 5){
        delay(500);
    }

}

void MqttReconnect(){
    while (!mqttPubSub.connected()  && (mqttCounterConn++ < 4))
    {
        Serial.print("Attempting MQTT connection...");
        if (mqttPubSub.connect(mqtt_DeviceName, mqttUser, mqttPsw))
        {
            Serial.println("connected");
            mqttPubSub.subscribe("homeassistant/status");
            mqttPubSub.subscribe((TopicRelay1 + "/set").c_str());
            delay(500);
        } else
        {
            Serial.print("failed, rc=");
            Serial.print(mqttPubSub.state());
            Serial.println(" try again in 3 seconds");
            delay(3000);
        }
    }
    mqttCounterConn = 0;
}

void MqttHomeAssistantDiscovery(){
    String discoveryTopic;
    String payload;
    String strPayload;
    int uniqueId_increment = 0;
    if(mqttPubSub.connected())
    {
        StaticJsonDocument<600> payload;
        JsonArray modes;
        JsonObject device;
        JsonArray identifiers;

		discoveryTopic = "homeassistant/switch/" + deviceName + "_relay1/config"; 
        payload["name"] = deviceName + ".relay1";
        payload["uniq_id"] = UniqueId + "_relay1";
        payload["stat_t"] = TopicRelay1 + "/state";
        payload["cmd_t"] = TopicRelay1 + "/set";
        device = payload.createNestedObject("device");
        device["name"] = deviceName;
        device["model"] = deviceModel;
        device["sw_version"] = Version;
        device["manufacturer"] = manufacturer;
        identifiers = device.createNestedArray("identifiers");
        identifiers.add(UniqueId);

        serializeJsonPretty(payload, Serial);
        Serial.println(" ");
        serializeJson(payload, strPayload);

        mqttPubSub.publish(discoveryTopic.c_str(), strPayload.c_str());
        delay(100);

		// Send Current status of Relays
        MqttPublishStatus_Relay1();
        delay(100);
    }
}

void MqttReceiverCallback(char* topic, byte* inFrame, unsigned int length){
    byte state = 0;
    String payload;
    String topicMsg;
    StaticJsonDocument<256> doc;

    for (int i = 0; i < length; i++)
    {
        payload += (char)inFrame[i];
    }


    if(String(topic) == String("homeassistant/status"))
    {
        if(payload == "online")          
        {
            MqttHomeAssistantDiscovery(); 
        }
    }

	if(String(topic) == String(TopicRelay1 + "/set")) 
    {
        if(payload == "ON")
            RelayStatus1 = RELAY_ON;
        else if(payload == "OFF")
            RelayStatus1 = RELAY_OFF;
        digitalWrite(RELAY1, RelayStatus1);
        MqttPublishStatus_Relay1();
    }
}

void MqttPublishStatus_Relay1() 
{
    String strPayload;
    if(mqttPubSub.connected())
    {
        if(RelayStatus1 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";

        mqttPubSub.publish((TopicRelay1 + "/state").c_str(), strPayload.c_str());
    }
}




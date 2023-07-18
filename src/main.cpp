#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h> 
#include "setup.h"

                            
String deviceName = "Home_Engine";                          		
String  TopicRelay1 = "Home_Engine/relay1";  
String  TopicRelay2 = "Home_Engine/relay2"; 
String  TopicRelay3 = "Home_Engine/relay3"; 
String  TopicRelay4 = "Home_Engine/relay4"; 
String  TopicRelay5 = "Home_Engine/relay5"; 
String  TopicRelay6 = "Home_Engine/relay6"; 
WiFiClient wiFiClient;
PubSubClient mqttPubSub(wiFiClient);
String UniqueId;

byte  RelayStatus1 = RELAY_OFF;
byte Input1 = 0;
byte state_input1 = SWITCH_OFF;

byte  RelayStatus2 = RELAY_OFF;
byte Input2 = 0;
byte state_input2 = SWITCH_OFF;

byte  RelayStatus3 = RELAY_OFF;
byte Input3 = 0;
byte state_input3 = SWITCH_OFF;

byte  RelayStatus4 = RELAY_OFF;
byte Input4 = 0;
byte state_input4 = SWITCH_OFF;

byte  RelayStatus5 = RELAY_OFF;
byte Input5 = 0;
byte state_input5 = SWITCH_OFF;

byte  RelayStatus6 = RELAY_OFF;
byte Input6 = 0;
byte state_input6 = SWITCH_OFF;

void setup_wifi();
void MqttReconnect();
void MqttHomeAssistantDiscovery();
void MqttReceiverCallback(char* , byte*, unsigned int);
void MqttPublishStatus_Relay1();
void MqttPublishStatus_Relay2();
void MqttPublishStatus_Relay3();
void MqttPublishStatus_Relay4();
void MqttPublishStatus_Relay5();
void MqttPublishStatus_Relay6();


void setup(){
    pinMode(Switch1, INPUT_PULLUP);
    pinMode(RELAY1, OUTPUT);
    pinMode(Switch2, INPUT_PULLUP);
    pinMode(RELAY2, OUTPUT);
    pinMode(Switch3, INPUT_PULLUP);
    pinMode(RELAY3, OUTPUT);
    pinMode(Switch4, INPUT_PULLUP);
    pinMode(RELAY4, OUTPUT);
    pinMode(Switch5, INPUT_PULLUP);
    pinMode(RELAY5, OUTPUT);
    pinMode(Switch6, INPUT_PULLUP);
    pinMode(RELAY6, OUTPUT);
    pinMode(2,OUTPUT);
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
    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, LOW);
    digitalWrite(RELAY3, LOW);
    digitalWrite(RELAY4, LOW);
    digitalWrite(RELAY5, LOW);
    digitalWrite(RELAY6, LOW);
}

void loop(){
    if(WiFi.status() == WL_CONNECTED)
    {   digitalWrite(2,HIGH);
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

    // Inputs Monitor 1
    if(millis() - TimeInputs1 > 200){
        TimeInputs1 = millis();

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


     // Inputs Monitor 2
    if(millis() - TimeInputs2 > 200){
        TimeInputs2 = millis();

        switch(state_input2){
            case SWITCH_OFF:
            {
                if(digitalRead(Switch2) == 1){
                    state_input2 = CHECKING;
                }
            } break;

            case CHECKING:
            {
                if(digitalRead(Switch2) == 1){
                    state_input2 = SWITCH_ON;
                    Input2 = 1;
                    RelayStatus2 = RELAY_ON;
                    digitalWrite(RELAY2, RelayStatus2);
                }
                else if(digitalRead(Switch2) == 0){                      
                    state_input2 = SWITCH_OFF;
                    Input2 = 0;
                    RelayStatus2 = RELAY_OFF;
                    digitalWrite(RELAY2, RelayStatus2);
                }
                    MqttPublishStatus_Relay2();

            } break;

            case SWITCH_ON:
            {
                if(digitalRead(Switch2) == 0){
                    state_input2 = CHECKING;
                }
            } break;
        }
    }
     // Inputs Monitor 3
    if(millis() - TimeInputs3 > 200){
        TimeInputs3 = millis();

        switch(state_input3){
            case SWITCH_OFF:
            {
                if(digitalRead(Switch3) == 1){
                    state_input3 = CHECKING;
                }
            } break;

            case CHECKING:
            {
                if(digitalRead(Switch3) == 1){
                    state_input3 = SWITCH_ON;
                    Input3 = 1;
                    RelayStatus3 = RELAY_ON;
                    digitalWrite(RELAY3, RelayStatus3);
                }
                else if(digitalRead(Switch3) == 0){                      
                    state_input3 = SWITCH_OFF;
                    Input3 = 0;
                    RelayStatus3 = RELAY_OFF;
                    digitalWrite(RELAY3, RelayStatus3);
                }
                    MqttPublishStatus_Relay3();

            } break;

            case SWITCH_ON:
            {
                if(digitalRead(Switch3) == 0){
                    state_input3 = CHECKING;
                }
            } break;
        }
    }
     // Inputs Monitor 4
    if(millis() - TimeInputs4 > 200){
        TimeInputs4 = millis();

        switch(state_input4){
            case SWITCH_OFF:
            {
                if(digitalRead(Switch4) == 1){
                    state_input4 = CHECKING;
                }
            } break;

            case CHECKING:
            {
                if(digitalRead(Switch4) == 1){
                    state_input4 = SWITCH_ON;
                    Input4 = 1;
                    RelayStatus4 = RELAY_ON;
                    digitalWrite(RELAY4, RelayStatus4);
                }
                else if(digitalRead(Switch4) == 0){                      
                    state_input4 = SWITCH_OFF;
                    Input4 = 0;
                    RelayStatus4 = RELAY_OFF;
                    digitalWrite(RELAY4, RelayStatus4);
                }
                    MqttPublishStatus_Relay4();

            } break;

            case SWITCH_ON:
            {
                if(digitalRead(Switch4) == 0){
                    state_input4 = CHECKING;
                }
            } break;
        }
    }
     // Inputs Monitor 5
    if(millis() - TimeInputs5 > 200){
        TimeInputs5 = millis();

        switch(state_input5){
            case SWITCH_OFF:
            {
                if(digitalRead(Switch5) == 1){
                    state_input5 = CHECKING;
                }
            } break;

            case CHECKING:
            {
                if(digitalRead(Switch5) == 1){
                    state_input5 = SWITCH_ON;
                    Input5 = 1;
                    RelayStatus5 = RELAY_ON;
                    digitalWrite(RELAY5, RelayStatus5);
                }
                else if(digitalRead(Switch5) == 0){                      
                    state_input5 = SWITCH_OFF;
                    Input5 = 0;
                    RelayStatus5 = RELAY_OFF;
                    digitalWrite(RELAY5, RelayStatus5);
                }
                    MqttPublishStatus_Relay5();

            } break;

            case SWITCH_ON:
            {
                if(digitalRead(Switch5) == 0){
                    state_input5 = CHECKING;
                }
            } break;
        }
    }
     // Inputs Monitor 6
    if(millis() - TimeInputs6 > 200){
        TimeInputs6 = millis();

        switch(state_input6){
            case SWITCH_OFF:
            {
                if(digitalRead(Switch6) == 1){
                    state_input6 = CHECKING;
                }
            } break;

            case CHECKING:
            {
                if(digitalRead(Switch6) == 1){
                    state_input6 = SWITCH_ON;
                    Input6 = 1;
                    RelayStatus6 = RELAY_ON;
                    digitalWrite(RELAY6, RelayStatus6);
                }
                else if(digitalRead(Switch6) == 0){                      
                    state_input6 = SWITCH_OFF;
                    Input1 = 0;
                    RelayStatus6 = RELAY_OFF;
                    digitalWrite(RELAY6, RelayStatus6);
                }
                    MqttPublishStatus_Relay6();

            } break;

            case SWITCH_ON:
            {
                if(digitalRead(Switch6) == 0){
                    state_input6 = CHECKING;
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
    digitalWrite(2,HIGH);
    WiFi.macAddress(mac);
    UniqueId =  String(mac[0],HEX) + String(mac[1],HEX) + String(mac[2],HEX) + String(mac[3],HEX) + String(mac[4],HEX) + String(mac[5],HEX);

    while(WiFi.status() != WL_CONNECTED && counter++ < 5){
        digitalWrite(2,LOW);
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
            mqttPubSub.subscribe((TopicRelay2 + "/set").c_str());
            mqttPubSub.subscribe((TopicRelay3 + "/set").c_str());
            mqttPubSub.subscribe((TopicRelay4 + "/set").c_str());
            mqttPubSub.subscribe((TopicRelay5 + "/set").c_str());
            mqttPubSub.subscribe((TopicRelay6 + "/set").c_str());
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
        StaticJsonDocument<1000> payload;
        JsonArray modes;
        JsonObject device;
        JsonArray identifiers;
        //relay1
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

         //relay2
		discoveryTopic = "homeassistant/switch/" + deviceName + "_relay2/config"; 
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();
        payload["name"] = deviceName + ".relay2";
        payload["uniq_id"] = UniqueId + "_relay2";
        payload["stat_t"] = TopicRelay2 + "/state";
        payload["cmd_t"] = TopicRelay2 + "/set";
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

        //relay3
		discoveryTopic = "homeassistant/switch/" + deviceName + "_relay3/config"; 
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();
        payload["name"] = deviceName + ".relay3";
        payload["uniq_id"] = UniqueId + "_relay3";
        payload["stat_t"] = TopicRelay3 + "/state";
        payload["cmd_t"] = TopicRelay3 + "/set";
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

 //relay4
		discoveryTopic = "homeassistant/switch/" + deviceName + "_relay4/config"; 
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();
        payload["name"] = deviceName + ".relay4";
        payload["uniq_id"] = UniqueId + "_relay4";
        payload["stat_t"] = TopicRelay4 + "/state";
        payload["cmd_t"] = TopicRelay4 + "/set";
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

 //relay5
		discoveryTopic = "homeassistant/switch/" + deviceName + "_relay5/config"; 
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();
        payload["name"] = deviceName + ".relay5";
        payload["uniq_id"] = UniqueId + "_relay5";
        payload["stat_t"] = TopicRelay5 + "/state";
        payload["cmd_t"] = TopicRelay5 + "/set";
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

 //relay6
		discoveryTopic = "homeassistant/switch/" + deviceName + "_relay6/config"; 
        payload.clear();
        device.clear();
        identifiers.clear();
        strPayload.clear();
        payload["name"] = deviceName + ".relay6";
        payload["uniq_id"] = UniqueId + "_relay6";
        payload["stat_t"] = TopicRelay6 + "/state";
        payload["cmd_t"] = TopicRelay6 + "/set";
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

        digitalWrite(RELAY1, LOW);
        digitalWrite(RELAY2, LOW);
        digitalWrite(RELAY3, LOW);
        digitalWrite(RELAY4, LOW);
        digitalWrite(RELAY5, LOW);
        digitalWrite(RELAY6, LOW);
		// Send Current status of Relays
        MqttPublishStatus_Relay1();
        delay(100);
        MqttPublishStatus_Relay2();
        delay(100);
        MqttPublishStatus_Relay3();
        delay(100);
        MqttPublishStatus_Relay4();
        delay(100);
        MqttPublishStatus_Relay5();
        delay(100);
        MqttPublishStatus_Relay6();
        delay(100);
    }
}

void MqttReceiverCallback(char* topic, byte* inFrame, unsigned int length){
    byte state = 0;
    String payload;
    String topicMsg;
    StaticJsonDocument<1000> doc;

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

	if(String(topic) == String(TopicRelay2 + "/set")) 
    {
        if(payload == "ON")
            RelayStatus2 = RELAY_ON;
        else if(payload == "OFF")
            RelayStatus2 = RELAY_OFF;
        digitalWrite(RELAY2, RelayStatus2);
        MqttPublishStatus_Relay2();
    }

    if(String(topic) == String(TopicRelay3 + "/set")) 
    {
        if(payload == "ON")
            RelayStatus3 = RELAY_ON;
        else if(payload == "OFF")
            RelayStatus3 = RELAY_OFF;
        digitalWrite(RELAY3, RelayStatus3);
        MqttPublishStatus_Relay3();
    }

    if(String(topic) == String(TopicRelay4 + "/set")) 
    {
        if(payload == "ON")
            RelayStatus4 = RELAY_ON;
        else if(payload == "OFF")
            RelayStatus4 = RELAY_OFF;
        digitalWrite(RELAY4, RelayStatus4);
        MqttPublishStatus_Relay4();
    }

    if(String(topic) == String(TopicRelay5 + "/set")) 
    {
        if(payload == "ON")
            RelayStatus5 = RELAY_ON;
        else if(payload == "OFF")
            RelayStatus5 = RELAY_OFF;
        digitalWrite(RELAY5, RelayStatus5);
        MqttPublishStatus_Relay5();
    }

    if(String(topic) == String(TopicRelay6 + "/set")) 
    {
        if(payload == "ON")
            RelayStatus6 = RELAY_ON;
        else if(payload == "OFF")
            RelayStatus6 = RELAY_OFF;
        digitalWrite(RELAY6, RelayStatus6);
        MqttPublishStatus_Relay6();
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

void MqttPublishStatus_Relay2() 
{
    String strPayload;
    if(mqttPubSub.connected())
    {
        if(RelayStatus2 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";

        mqttPubSub.publish((TopicRelay2 + "/state").c_str(), strPayload.c_str());
    }
}
void MqttPublishStatus_Relay3() 
{
    String strPayload;
    if(mqttPubSub.connected())
    {
        if(RelayStatus3 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";

        mqttPubSub.publish((TopicRelay3 + "/state").c_str(), strPayload.c_str());
    }
}
void MqttPublishStatus_Relay4() 
{
    String strPayload;
    if(mqttPubSub.connected())
    {
        if(RelayStatus4 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";

        mqttPubSub.publish((TopicRelay4 + "/state").c_str(), strPayload.c_str());
    }
}
void MqttPublishStatus_Relay5() 
{
    String strPayload;
    if(mqttPubSub.connected())
    {
        if(RelayStatus5 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";

        mqttPubSub.publish((TopicRelay5 + "/state").c_str(), strPayload.c_str());
    }
}
void MqttPublishStatus_Relay6() 
{
    String strPayload;
    if(mqttPubSub.connected())
    {
        if(RelayStatus6 == 0)
            strPayload = "OFF";
        else
            strPayload = "ON";

        mqttPubSub.publish((TopicRelay6 + "/state").c_str(), strPayload.c_str());
    }
}





const char* ssid = "NITDA-ICT-HUB";                             
const char* password = "6666.2524#";                           
const char* mqtt_server = "172.16.122.37";                        
const char* mqttUser = "nithub";                              
const char* mqttPsw = "0000";                             
int mqttPort = 1883;                                     
const char* mqtt_DeviceName = "Home Engine 1";                          
const char* deviceModel = "Model A";                            
const char* Version = "1.0";                                   
const char*	manufacturer = "NITHUB";

#define SWITCH_OFF 0
#define CHECKING 1
#define SWITCH_ON 2
#define RELAY_OFF 0
#define RELAY_ON 1
const int Switch1 = 13;
const int RELAY1 = 15;
const int Switch2 = 12;
const int RELAY2 = 4;
const int Switch3 = 14;
const int RELAY3 = 5;
const int Switch4 = 27;
const int RELAY4 = 18;
const int Switch5 = 26;
const int RELAY5 = 19;
const int Switch6 = 25;
const int RELAY6 = 21;
unsigned long TimeInputs1 = 0;
unsigned long TimeInputs2 = 0;
unsigned long TimeInputs3 = 0;
unsigned long TimeInputs4 = 0;
unsigned long TimeInputs5 = 0;
unsigned long TimeInputs6 = 0;

int mqttCounterConn = 0;
bool InitSystem = true;
int canPublish = 0;

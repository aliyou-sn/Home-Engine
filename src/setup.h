const char* ssid = "Aliyu";                             
const char* password = "macbooker";                           
const char* mqtt_server = "192.168.43.223";                        
const char* mqttUser = "mqtt_1";                              
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
const int Switch1 = 4;
const int RELAY1 = 2;
unsigned long TimeInputs = 0;
int mqttCounterConn = 0;
bool InitSystem = true;
int canPublish = 0;

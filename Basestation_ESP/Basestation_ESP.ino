/* LIAM LAWNMOWER BWF Signal Generator and Control
 * Allows remote control of BWF on/off state and hopefully also SoC (State of Charge) monitoring
 * Future Plans: Automatically turn of BWF signal while charging to conserve energy and automatically turn of charging contacts while mowing
 * Virtual Pins used: V25: SoC, V26: Mower current action: V26: Reserved, V27: Reserved, V28: BWF Station RSSI, V29: Remote Debug, V30: Manual BWF control
 * 
 * 
 * 
 */

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Select which transmitter type you have by uncommenting that line
#define __1_L298_Standalone__

//---- No need to change anything below ----------------------

// Arduino pins and timing for the PWM signals.
#ifdef __1_L298_Standalone__ 
  #define PIN1_PWM D0
  #define PIN2_PWM D1
  #define PIN3_PWM D2
  #define PIN4_PWM D3
  #define LONG_DELAY 8000 
  #define SHORT_DELAY 250     
#endif


//GLOBAL VARIABLES
//BLYNK
char auth[] = "";              //ADD YOUR BLYNK TOKEN GENERATED IN THE APP HERE    

//WIFI
const char* ssid =      "";    //ADD YOUR WIFI DETAILS
const char* password =  "";    //ADD YOUR WIFI PASSWORD

//BWF STATION SPECIFIC VARIABLES
bool BWF_Signal = true;


//TIMER
unsigned long current_time;
unsigned long last_update_time;
unsigned long last_notify_time;
int polling_rate = 1000;

void setup() {
  Serial.begin(115200);                                   //Init serial monitor
  delay(30);                                              //NODE-MCU needs time to start serial else garbled letters will appear
  Serial.print("\n Connecting to: "); Serial.println(ssid);  
  WiFi.begin(ssid, password);                             //Connect to specified SSID and password
  

  while (WiFi.status() != WL_CONNECTED) {                 //Wait for wifi to connect
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wifi. Connectin to Blynk");
  Blynk.config(auth);
  while (Blynk.connect() == false) {                      //Wait for Blynk to connect
    Serial.print(".");
    delay(500);
  }

  Serial.println("WiFi Connected ");
  Serial.println("SSID: " + String(ssid));
  //Serial.println("IP Adress: " + String(WiFi.localIP())); //throws an error in this version.
  Serial.println("\nBlynk v" BLYNK_VERSION ": Device started");

  //BWF Sender settings
  #ifdef __1_L298_Standalone__
  pinMode(PIN1_PWM,OUTPUT);
  pinMode(PIN2_PWM,OUTPUT);
  pinMode(PIN3_PWM,OUTPUT);
  pinMode(PIN4_PWM,OUTPUT);
#endif

  Blynk.syncAll(); //Sync last state from server and perform global read/write
  
} //End setup


void loop() {
  Blynk.run();
  if (BWF_Signal == true) generateSignal(); //Turn on signal if button V30 in Blynk is on
  if (BWF_Signal == false) none();          //Turn off signal if button V30 in Blynk is off

  if (millis() - last_update_time >= polling_rate) {
    sendStatus();
    last_update_time = millis();
 } //END TIMER
} //END LOOP

//V28 is RSSI from BWF station

void sendStatus() {
  long rssi = WiFi.RSSI();
  Serial.println("RSSI: " + String(rssi));
  Blynk.virtualWrite(V28, rssi);
}


//V30 is manual on/off of BWF signal
BLYNK_WRITE(V30) {                                      //Write data from Blynk app to ESP
  int pinValue = param.asInt();
  //Serial.println(pinValue);
  if (pinValue == 0) BWF_Signal = false;      //Turn off BWF signal
  if (pinValue == 1) BWF_Signal = true;
  Serial.println("BWF ON/OFF: " + String(BWF_Signal));
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
}

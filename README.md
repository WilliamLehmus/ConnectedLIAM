# ConnectedLIAM
Addon to LIAM diy lawnmower by William Lehmus which adds wifi connectivity, remote monitoring and control. 
I´ve also created an additional mod that adds wifi to the base station for remote monitoring and control

This is a addon to Liam diy lawnmower found at:
GITHUB: https://github.com/sm6yvr/liam
FACEBOOK: https://www.facebook.com/groups/319588508137220/
PARTS STORE: https://www.facebook.com/groups/319588508137220/

Parts needed:
1) a working Liam DIY Lawnmower running the original Liam Code on an arduino. This addon has been tested with the latest version 5.4 
2) A Node-MCU microcontroller.
3) 3 male to female dupont cables (standard arduino cables..) 

Software needed:
1) ESPcoms.ino. Put this in your Liam folder.
2) Liam_ESP_addon.ino. Change the wifi details and add your Blynk token and then upload this to your ESP
3) BLYNK phone app
4) BLYNK arduino library (Found in library manager in Arduino IDE)

Connections:
1) NODE-MCU TX -> Morgan Shield Bluetooth RX
2) NODE-MCU RX -> Morgan shield Bluetooth TX
3) NODE-MCU GND -> Morgan shield GND. 

Modifications to original LIAM Code:
A lot of effort has been put in to making this mod as simple as possible to add but
since LIAM was never meant to be connected some modifications to the code are necessary. 

MOVE THE COMMENTED SECTIONs BELOW TO RESPECTIVE PARTS

  //PLACE THIS IF STATEMENT IN VOID LOOP
  if ((millis() - lastUpdate) > interval) {   
  connectedLiam();
  }

  //------COPY THE WHOLE SECTION BELOW TO GLOBAL VARIABLES------
  //TIMER
  unsigned long lastUpdate;           //Move to global variables
  int interval = 1000;                //Move to global variables

  struct MOWERDATA {          // move to global variable
    String activity;          //Current activity, I.E mowing, looking for signal, charging etc.
    int SoC;                  //Current battery level
    String SoCString;         //Current battery level in string format 
    float batMin;             //Minimum defined level of battery. Depleted level.
    float batMax;             //Maximum defined level of battery. SoC when to consider charging complete
    int leftBWF;              //Status of left BWF. IN (1) or OUT (0).
    int rightBWF;             //Status of left BWF. IN (1) or OUT (0).
    int leftRearBWF;          //Status of rear BWF. IN (1) or OUT (0).
    int rightRearBWF;         //Status of rear BWF. IN (1) or OUT (0).
    bool insideCable;         //Variable used to check if the mower is inside or outside the BWF or cannot see it.
  } mowerData;                //Object name. Fetch or edit data by calling for instance mowerData.SoC = batteryLevel;

Finally search for all instances of 'state' in all files through arduino IDE and add this line below all.
mowerData.activity = state;
States are the different activites of Liam. There are six of them, for instance: MOWING, LOOKING FOR BWF, DOCKING, CHARGIN etc..
To correctly make ConnectedLiam report the different states you need to fetch the states wherever they change in the original code.

For instance, when you search for state you will find lines like:
Switch(state) {
 case MOWING:
  mowerData.activity = state;     <--- You need to assign the state everytime the state in the original code changes
  doMowing();
  break;



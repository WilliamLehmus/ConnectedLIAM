# ConnectedLIAM
Addon made by William Lehmus to LIAM diy lawnmower (https://github.com/sm6yvr/liam) which adds wifi connectivity, remote monitoring and control. 
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

Follow the instructions in wiki for this mod. 
The same instructions are also available in the ESPcoms.ino file. 



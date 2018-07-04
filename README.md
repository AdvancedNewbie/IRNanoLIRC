# IRNanoLIRC

Simple IR Receiver using an Arduino Nano for WinLIRC and the IRMan.dll plugin
This, of course, should work for LIRC as well.

Sends received IR code as bytes across USB-Serial following
the IRMan protocol.  

# Bytes:

0: Header (set to identify remote)

1: Unique button code

2-4: Should be 0x00, but sends rest of code incase of button overlap - IRMan.dll doesn't seem to mind...

# Setting up WinLIRC:

Run ".\IRRecord.exe -d IRMan.dll ..\config.cfg" to configure WinLIRC configuration file after uploading
this firmware to your IR receiver board (this board).  Follow the instructions to setup your remote's 
unique button IR codes.  Use a program called 'EventGhost' for further functionality.

# Hardware:

Arduino Nano

A SM0038 or TSMP1138 IR Receiver or similar.  Has missing pin (space) between GND,VCC and Signal.

# Connections:

Simply connect GND to GND, VCC to 5V, and the Signal Pin to a digital input of your choice (default: 2)
 
 
 
 
AdvancedNewbie
07/03/2018

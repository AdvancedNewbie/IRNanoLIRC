/* IRNanoLIRC
 *  
 * Simple IR Receiver using an Arduino Nano for WinLIRC and the IRMan.dll plugin
 * This, of course, should work for LIRC as well.
 * 
 * Sends received IR code as bytes across USB-Serial following
 * the IRMan protocol.  
 * 
 * Bytes:
 * 0: Header (set to identify remote)
 * 1: Unique button code
 * 2-4: Should be 0x00, but sends rest of code incase of button overlap - IRMan.dll doesn't seem to mind...
 * 
 * Run ".\IRRecord.exe -d IRMan.dll ..\config.cfg" to configure WinLIRC configuration file after uploading
 * this firmware to your IR receiver board (this board).  Follow the instructions to setup your remote's 
 * unique button IR codes.  Use a program called 'EventGhost' for further functionality.
 * 
 * Uses a SM0038 or TSMP1138 IR Receiver or similar.  Has missing pin (space) between GND,VCC and Signal.
 * 
 * AdvancedNewbie
 * 07/03/2018
 */

#include <IRremote.h>

int RECV_PIN = 2;  //Change to Digital Pin of IR receiver

unsigned char lastp[5] = {0x00, 0x00, 0x00, 0x00, 0x00};  //To store last IR code received

IRrecv irrecv(RECV_PIN);  //Initialize IRrecv

decode_results results;  //A place to store IR code results - see IRremote.h

void setup()
{
  Serial.begin(9600);   //Default for IRMan.dll in WinLIRC
  Serial.write("OK");   //Since Arduino resets on serial, send 'OK' incase there was a 'IR' already sent
  irrecv.enableIRIn();  // Start the receiver
}

void loop() {
  
  if (irrecv.decode(&results)) {   //New IR code received
    unsigned char *p = (unsigned char*)&results.value;  //Cast results of new IR code to unsigned char p array
    if(p[0] != 0xFF){   //Received new IR code
      Serial.write(0x1E);  //Write header
      for(int i=0;i<=4;i++){
        Serial.write(p[i]);   //Write new IR Code
        lastp[i] = p[i];   //Store new IR Code incase of repeat
      }
      delay(250);  //Debounce button
    }
    if (p[0] == 0xFF){  //Received 'Repeat Last' command
      Serial.write(0x1E);  //Write header
      for(int i=0;i<=4;i++){
        Serial.write(lastp[i]);  //Write last IR Code
      }
      //No delay here (rapid fire!)
    }
    irrecv.resume(); // Receive the next value
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();  // get the new byte
    if (inChar == 'R') {  // If we get IR write OK once R is received
      Serial.write("OK");
    }
  }
}

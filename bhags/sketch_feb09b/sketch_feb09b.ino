
// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

String e;
char d;
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(15, 14); // RX, TX

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  XBee.begin(9600);    
}

void loop() {
  // Notice how there's no delays in this sketch to allow you to do other processing in-line while doing distance pings.

  if(Serial.available()){
    d = Serial.read();
    Serial.print(d);
    XBee.print(d);
  }
  if(XBee.available()){
    d = XBee.read();
    Serial.print(d);
  }
  // Do other stuff here, really. Think of it as multi-tasking.
  
}


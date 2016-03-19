// Program to check Xbee connection between two arduino

// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

SoftwareSerial XBee(5,6);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  XBee.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  XBee.Write("....work....");
  if(XBee.available()){
    Serial.print(XBee.read());
  }
}

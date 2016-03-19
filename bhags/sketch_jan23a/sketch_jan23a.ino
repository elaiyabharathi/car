
// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
//SoftwareSerial XBee(3, 4); // RX, TX

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
    Serial3.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
//  if(Serial.available()){
//    Serial.write(Serial.read());
//    XBee.write(Serial.read());
//  }
  if(Serial3.available()){
    Serial.write(Serial3.read());
  }
}

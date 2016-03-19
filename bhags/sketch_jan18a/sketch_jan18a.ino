#include "SoftwareSerial.h"

SoftwareSerial mySerial(10,11); // RX, TX

void setup() 
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.println("uBlox Neo 6M");

  // set the data rate for the SoftwareSerial port
  Serial2.begin(9600);

}

void loop() // run over and over
{
  if (Serial2.available()){
    
    Serial.write(Serial2.read());
  }
}


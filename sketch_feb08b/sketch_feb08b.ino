
// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

#define TRIGGER_PIN   9 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN      8 // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.



unsigned int pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long pingTimer;     // Holds the next ping time.
int dis = 0;
String e;
char d[4];
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(5, 6); // RX, TX

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  XBee.begin(9600);
  pingTimer = millis(); // Start now.
  
  
}

void loop() {
  // Notice how there's no delays in this sketch to allow you to do other processing in-line while doing distance pings.
  if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += pingSpeed;      // Set the next ping time.
    XBee.write("hi");
  }

  // Do other stuff here, really. Think of it as multi-tasking.
  
}


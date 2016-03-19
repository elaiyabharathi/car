#include <toneAC.h>
#include <NewPing.h>
// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define TRIGGER_PIN   9 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN      8 // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 9600;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

unsigned int pingSpeed = 500; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long pingTimer;     // Holds the next ping time.
unsigned long pingTimer2;
int dis = 0;
String e;
char d[4];
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(5, 6); // RX, TX

// The TinyGPS++ object
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  ss.begin(GPSBaud);
  XBee.begin(9600);
  pingTimer = millis(); // Start now.
}

void loop() {
  // Notice how there's no delays in this sketch to allow you to do other processing in-line while doing distance pings.
  if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += pingSpeed;      // Set the next ping time.
    sonar.ping_timer(echoCheck); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
  }
  // Do other stuff here, really. Think of it as multi-tasking.
    getGpsdata();  
  
}

void getGpsdata(){
  Serial.write("printing lat lon");
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  
  
  Serial.write("\n"); 
    smartDelay(1000);
}

void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
  // Don't do anything here!
  if (sonar.check_timer()) { // This is how you check to see if the ping was received.
    // Here's where you can add code.
    Serial.print("Ping: ");
    Serial.print(sonar.ping_result / US_ROUNDTRIP_CM); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
    Serial.print("cm\n");
    XBee.write("Dis: ");
    dis = sonar.ping_result / US_ROUNDTRIP_CM ;
    e = String(dis);
    e.toCharArray(d,4);
    XBee.write(d);
    XBee.write("cm\n");
//    if(dis<=30){
//    Serial.print("hey the man behind you is so near!!");
//           for (unsigned long freq = 150; freq <= 15000; freq += 10) {  
//          toneAC(freq); // Play the frequency (150 Hz to 15 kHz in 10 Hz steps).
//          delay(1);     // Wait 1 ms so you can hear it.
//        }
//        toneAC(0); // Turn off toneAC, can also use noToneAC().
//
//    }
  }
  // Don't do anything here!
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1){
      Serial.print('*');
      XBee.print('*');
    }
    Serial.print(' ');
    XBee.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    XBee.print(val,prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
      XBee.print(' ');
  }
  smartDelay(0);
}


// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

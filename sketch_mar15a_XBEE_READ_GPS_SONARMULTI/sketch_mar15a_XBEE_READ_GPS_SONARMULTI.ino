#include <NewPing.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#define MAX_DIS 300

// constants won't change. Used here to set a pin number :
const int ledPin =  53;      // the number of the LED pin
const int ledPin2 = 51;
int ledState = LOW;             // ledState used to set the LED

class ultrasonic{
    long onTime;
    unsigned long previousMillis=0;    // will store last time LED was updated
    NewPing *sonar;
public:
  ultrasonic(int trigg_pin,int echo_pin,int pingSpeed){
    sonar = new NewPing(trigg_pin,echo_pin,MAX_DIS);
    
    onTime = pingSpeed;
  }
  void update(int us){
     // check to see if it's time to change the state of the LED
     NewPing s = (*sonar);
    unsigned long currentMillis = millis();
    if ((currentMillis-previousMillis)>=onTime) {   // pingSpeed milliseconds since last ping, do another ping.
    previousMillis = currentMillis;
    Serial.print("Ultrasonic sensor ");
    Serial3.print("Ultrasonic sensor ");
    Serial.print(us);
    Serial3.print(us);
    Serial.print("\n");
    Serial3.print("\n");
    int cm = s.ping_cm();
      if(cm<=30)
      {
            ledState = LOW;
            digitalWrite(ledPin, ledState);  
      }
      else
      {
          ledState = HIGH;
          digitalWrite(ledPin,ledState);
      }
    Serial.print("dis");
    Serial3.print("dis");
    Serial.print(cm);
    Serial3.print(cm);
    Serial.print("\n");
    Serial.print("\n");
    }
  }
  
};

static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 9600;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
 TinyGPSPlus gps;
class GPS
{
 public:
 GPS(){
    ss.begin(GPSBaud);
  }

  void getGpsdata(float lati,float longi){
    Serial.write("printing lat lon");
    Serial3.write("printing lat lon");
    printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
    printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
    Serial.write("\n"); 
    Serial3.write("\n");
//    double courseToLondon =
//    TinyGPSPlus::courseTo(
//      gps.location.lat(),
//      gps.location.lng(),
//      lati, 
//      longi);
//    printFloat(courseToLondon, gps.location.isValid(), 7, 2);
    smartDelay(1000);
  }
  static void printFloat(float val, bool valid, int len, int prec)
  {
    if (!valid)
    {
      while (len-- > 1){
        Serial.print('*');
        Serial3.print('*');
      }
      Serial.print(' ');
      Serial3.print(' ');
    }
    else
    {
      Serial.print(val, prec);
      Serial3.print(val, prec);
      int vi = abs((int)val);
      int flen = prec + (val < 0.0 ? 2 : 1); // . and -
      flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
      for (int i=flen; i<len; ++i)
        Serial.print(' ');
        Serial3.print(' ');
    }
    smartDelay(0);
  }
  static void smartDelay(unsigned long ms)
  {
    unsigned long start = millis();
    do 
    {
      while (ss.available())
        gps.encode(ss.read());
    } while (millis() - start < ms);
  }
};


ultrasonic NW(6,7,2000);
ultrasonic N(8,9,6000);
ultrasonic NE(4,5,7000);
ultrasonic S(12,13,8000);
GPS g;
LiquidCrystal lcd(27,26,25,24,23,22);
byte rx_byte = 0;        // stores received byte
String rcd;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  Serial3.begin(9600);
  lcd.begin(16,2);
  lcd.print("Ann! Sorry");
}

void loop() {
  // put your main code here, to run repeatedly:
  NW.update(1);
  N.update(2);
  NE.update(3);
  S.update(4);
  //g.getGpsdata();
  g.getGpsdata(13.102532,80.200782);
  
  // check for data byte on serial port 3
  if (Serial3.available()) {
    // get a byte from serial port 3
    rx_byte = Serial3.read();
    //rcd = Serial3.read();
    // send the byte to the USB serial port
    //lcd.print(rcd);
    
      if(rx_byte = 'H'){
        
      }
    }
  }


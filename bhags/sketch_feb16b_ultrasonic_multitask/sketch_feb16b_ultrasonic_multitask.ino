#include <NewPing.h>
#define MAX_DIS 300

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
    Serial.print(us);
    Serial.print("\n");
    int cm = s.ping_cm();
    Serial.print("dis");
    Serial.print(cm);
    Serial.print("\n");
    }
  }
  
};

ultrasonic u1(6,7,2000);
ultrasonic u2(8,9,6000);
ultrasonic u3(10,11,7000);
ultrasonic u4(12,13,8000);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  // put your main code here, to run repeatedly:
  u1.update(1);
  u2.update(2);
  u3.update(3);
  u4.update(4);
}

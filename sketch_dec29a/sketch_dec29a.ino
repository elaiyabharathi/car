int lmt1=5,lmt2=6,rmt1=11,rmt2=10;     //set your motor output pins left motor terminals and right motor terminals
int value;           // declaring variable used in serial communication
void setup()         // main function executes only once
{
 pinMode(lmt1,OUTPUT);
 pinMode(lmt2,OUTPUT);
 pinMode(rmt1,OUTPUT);
 pinMode(rmt2,OUTPUT);
 Serial.begin(9600); // serial communication begins baud rate is 9600
}
void loop()
{
  value=Serial.read(); //it will read the data recieved by xbee
  switch(value)   // will activate the case according to the value
 
  {
    case 'w':     // pressing w from keyboard activates this case and robot moves forward
    Serial.println("Robot moves forward");
    fwd(); 
    break;        // restart the loop function
    case 'd':     // pressing d from keyboard activates this case and robot turns right
    Serial.println("Robot turns right");
    right();
    break;
    case 'a':     // pressing a from keyboard activates this case and robot turns left
    Serial.println("Robot turns left");
    left();
    break;
    case 's':     // pressing s from keyboard activates this case and robot stops
    Serial.println("Robot stops");
    Stop();
    break;
    case 'z':     // pressing z from keyboard activates this case and robot moves back
    Serial.println("Robot moves back");
    back();
    break;
  }
    
}
void Stop() // function details 
{
  digitalWrite(lmt1,LOW);   // logic to stop all motor signal 0 volt
  digitalWrite(lmt2,LOW);
  digitalWrite(rmt1,LOW);
  digitalWrite(rmt2,LOW);
}
void left()
{
  digitalWrite(lmt1,LOW);   // logic to move left. Right motor moves forward and left motor backwards
  digitalWrite(lmt2,HIGH);
  digitalWrite(rmt1,HIGH);
  digitalWrite(rmt2,LOW);
}
void right()                // logic to move right. Left motor moves forward and right motor backwards
{
  digitalWrite(lmt1,HIGH);
  digitalWrite(lmt2,LOW);
  digitalWrite(rmt1,LOW);
  digitalWrite(rmt2,HIGH);
}
void fwd()                   // logic to move forward. both motor moves forward
{
  digitalWrite(lmt1,HIGH);
  digitalWrite(lmt2,LOW);
  digitalWrite(rmt1,HIGH);
  digitalWrite(rmt2,LOW);
}
void back()                 // logic to move Backwards. both motor moves backwards
{
  digitalWrite(lmt1,LOW);
  digitalWrite(lmt2,HIGH);
  digitalWrite(rmt1,LOW);
  digitalWrite(rmt2,HIGH);
}
  
    

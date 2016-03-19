void setup() {
  // initialize serial ports
  Serial.begin(9600);    // USB serial port 0
  Serial3.begin(9600);   // serial port 3
}

String lati="13.012363";
String lon="80.235830";
byte rx_byte = 0;        // stores received byte

void loop() {
  delay(100);
  Serial3.print("Latitude:"+lati+"\n");
  Serial3.print("Longitude:"+lon+"\n");
  delay(200);
  Serial3.write("message:Pedestrian Crossing Ahead\n");
  delay(300);
  Serial3.write("radius: 10m");
  delay(500);
}

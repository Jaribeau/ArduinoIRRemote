/* Steup Function ********************/
void setup() {
  
  //Init IR/Serial TX pin
  Serial.begin(2400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  //Init button pins
  pinMode(2, OUTPUT);
  tone (2, 32767);
  
}//End of setup()


/* Main Loop *********************/
void loop() {
  //Serial.print("0x020>");
  //digitalWrite(2, LOW);
  //digitalWrite(1, HIGH);
  //Serial.println("Hello World!");
  delay(1000);
    
}//End of loop()

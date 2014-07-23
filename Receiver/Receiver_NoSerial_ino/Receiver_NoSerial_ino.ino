/* Steup Function ********************/
void setup() {
  
  //Init IR/Serial TX pin
  Serial.begin(2400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  //Init button pins
  pinMode(2, INPUT);
  
}//End of setup()


/* Main Loop *********************/
void loop() {
  if(digitalRead(2))
    Serial.println("HIGH MAN!");
  else
    Serial.println("Keep trying :(");
  delay(1);
    
}//End of loop()

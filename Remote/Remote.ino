
/******************************************/
/********* SYDE 192 - Team Blonde *********/
/********** ARDUINO 1 - REMOTE ************/
/******************************************/

/* Steup Function ********************/
void setup() {
  
  //Init IR/Serial TX pin
  Serial.begin(2400);
  
  //Init button pins
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  
  //Init interrupt
  attachInterrupt(0, interruptHandle, HIGH);
  tone (11, 38000);
  
}//End of setup()


/* Main Loop *********************/
void loop() {
  
  Serial.print("Sup!");
  delay(1000);
  //Not actually sure if there's anything for us to do in here... oh well.
    
}//End of loop()


/* Interrupt Handle for button presses ****************************/
void interruptHandle() {
  //Check for which button pressed and send corresponding IR code
  if(digitalRead(4))
     Serial.write("0x10/r");    //send power IR code
  else if(digitalRead(5))
     Serial.write("0x20/r");        //send volume up IR code
  else if(digitalRead(6))
     Serial.write("0x30/r");        //send volume down IR code
  else if(digitalRead(7))
     Serial.write("0x40/r");        //send mute IR code

}//End of interruptHandle()

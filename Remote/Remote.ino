/******************************************/
/********* SYDE 192 - Team Blonde *********/
/********** ARDUINO 1 - REMOTE ************/
/******************************************/

#define powerButton 6
#define volumeUp 7
#define volumeDown 8
#define mute 9

String command = "";

/* Steup Function ********************/
void setup() {
  
  //Init IR/Serial TX pin
  Serial.begin(2400);
  
  //Init button pins
  pinMode(powerButton, INPUT);
  pinMode(volumeUp, INPUT);
  pinMode(volumeDown, INPUT);
  pinMode(mute, INPUT);
  
  //Init interrupt
  attachInterrupt(1, interruptHandle, HIGH);
  //tone (11, 38000);
  
}//End of setup()


/* Main Loop *********************/
void loop() 
{
  //Check for which button pressed and send corresponding IR code
  if(digitalRead(powerButton))
  {
     Serial.print("Yellow>"); //power code
     while(digitalRead(powerButton))
       delay(10);//Don't resend until button released
  }
  else if(digitalRead(volumeUp))
  {
     Serial.print("Red>");    //send volume up IR code
     while(digitalRead(volumeUp))
       delay(10);//Don't resend until button released
  }
  else if(digitalRead(volumeDown))
  {
     Serial.print("Green>");    //send volume down IR code
     while(digitalRead(volumeDown))
       delay(10);//Don't resend until button released
  }
  else if(digitalRead(mute))
  {
     Serial.print("Blue>");    //send mute IR code
     while(digitalRead(mute))
       delay(10);//Don't resend until button released
  }    
}//End of loop()


/* Interrupt Handle for button presses ****************************/
void interruptHandle() 
{
  Serial.write('x');
  //Check for which button pressed and send corresponding IR code
  if(digitalRead(powerButton))
     command = "0x10>"; //power code
  else if(digitalRead(volumeUp))
     command = "0x20>";    //send volume up IR code
  else if(digitalRead(volumeDown))
     command = "0x30>";    //send volume down IR code
  else if(digitalRead(mute))
     command = "0x40>";    //send mute IR code

}//End of interruptHandle()

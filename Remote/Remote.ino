/******************************************/
/********* SYDE 192 - Team Blonde *********/
/********** ARDUINO 1 - REMOTE ************/
/******************************************/

/*
  IR Blaster LED cathode connects to TX pin, and the annode gets connected to the pin pulsing
  at 38kHz. The result is a 38kHz pulsing IR signal when the serial pin is high, and no signal 
  when it is low.
*/

#define powerButton 6
#define volumeUp 7
#define volumeDown 8
#define mute 9
  
  int startTime;
  int timeElapsed;
  boolean toggle = 0;

/* Steup Function ********************/
void setup() {
  
  //Init IR/Serial TX pin
  Serial.begin(2400);
  
  //Init button pins
  pinMode(powerButton, INPUT);
  pinMode(volumeUp, INPUT);
  pinMode(volumeDown, INPUT);
  pinMode(mute, INPUT);
  
  //Setup 38kHz pulse, method 1
  tone (13, 38000);
  
  //Setup 38kHz pulse, method 2
  /****** set timer1 interrupt at 48kHz *******/
  //Clear timer compare registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0; //initialize counter value to 0
  
  // set compare match register for 48kHz increments (OCR1A -> Output Compare Register)
  OCR1A = 332;  // = (16*10^6) / (48000) - 1
  //OCR1A = 15624;//SLower freq test for use with visible LED
  
  // turn on CTC (Clear timer on compare match) mode (page 136 in datasheet)
  TCCR1B |= (1 << WGM12);
  
  // Set up pre-scaler
  TCCR1B |= (1 << CS00);  //No prescaling (16mHz)
  //TCCR1B |= (1 << CS12) | (1 << CS10);  //1024 prescale for slow test with LED
  
  // enable timer compare interrupt (TIMSK1 -> Timer Interrupt Mask Register) page 139 of datasheet
  TIMSK1 |= (1 << OCIE1A);
  
  sei();//globally enable interrupts
  
}//End of setup()


/* Main Loop *********************/
void loop() 
{
  //Check for which button pressed and send corresponding IR code
  if(digitalRead(powerButton))
  {
     startTime = millis();
     timeElapsed = 0;  //Add button hold delay
     while(digitalRead(powerButton) && timeElapsed < 1000)
     {
       timeElapsed = millis() - startTime;  //Add button hold delay
     }
     if(timeElapsed >= 1000)
       Serial.print("Yellow>"); //power code
     else
       Serial.print("Randy>");  //Junk code for serial interrupt wakeup
       
     while(digitalRead(powerButton))
       delay(10);//Don't resend while button held
  }
  else if(digitalRead(volumeUp))
  {
     Serial.print("Red>");    //send volume up IR code
     while(digitalRead(volumeUp))
       delay(10);//Don't resend while button held
  }
  else if(digitalRead(volumeDown))
  {
     Serial.print("Green>");    //send volume down IR code
     while(digitalRead(volumeDown))
       delay(10);//Don't resend while button held
  }
  else if(digitalRead(mute))
  {
     Serial.print("Blue>");    //send mute IR code
     while(digitalRead(mute))
       delay(10);//Don't resend while button held
  }
}//End of loop()


//timer1 compare interrupt function to pulse pin 13 at 38kHz
ISR(TIMER1_COMPA_vect)
{
  if (toggle)
  {
    digitalWrite(13,HIGH);
    toggle = 0;
  }
  else
  {
    digitalWrite(13,LOW);
    toggle = 1;
  }
}//End of ISR


  boolean toggle = 0;

/* Steup Function ********************/
void setup() {
  
  //Init IR/Serial TX pin
  Serial.begin(2400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  //Init button pins
  pinMode(2, INPUT);
  pinMode(8, OUTPUT);
  tone (11, 38000);
  
  //Init interrupt
  /attachInterrupt(0, interruptHandle, HIGH);
  
  /****** set timer1 interrupt at 48kHz *******/
  //Clear timer compare registers
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  
  // set compare match register for 48kMz increments (OCR1A -> Output Compare Register)
  OCR1A = 332;// = (16*10^6) / (48000) - 1 (must be <65536)
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
  Serial.print("0x020>");
  //digitalWrite(2, LOW);
  //digitalWrite(1, HIGH);
  //Serial.println("Hello World!");
  if(!digitalRead(2))
    digitalWrite(8, HIGH);                                                                                                                
  
    
}//End of loop()

ISR(TIMER1_COMPA_vect){//timer1 interrupt 38kHz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
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
}

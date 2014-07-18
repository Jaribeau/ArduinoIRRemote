
/******************************************/
/********* SYDE 192 - Team Blonde *********/
/********** ARDUINO 2 - RECEIVER **********/
/******************************************/
#define ON 1
#define OFF 0

boolean ledMatrixStates[];
String serialIn;

  
/* Steup Function ****************************/
void setup() {
  
  //Init IR Serial and RX pin
  Serial.begin(2400);  //Start serial with baud rate of 2400
  
  //Init LED matrix and pins
  pinMode(4, INPUT);
  pinMode(4, INPUT);
  pinMode(4, INPUT);
  pinMode(4, INPUT);
  pinMode(4, INPUT);
  pinMode(4, INPUT);
  ledMatrixStates[] = {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF};
  
  //Init interrupt
  //attachInterrupt(0, interruptHandle, HIGH);
  
  
}//End of setup()


/* Main Loop ********************************/
void loop() {
  //Read IR serial input and make appropriate volume, or mute adjustments
  serialIn = Serial.read();
  
  //Rotate through which pin is turned on
    
}//End of loop()


/* Interrupt Handle *****************************/
void interruptHandle() {
  //Wake up or sleep arduino on interrupt

}//End of interruptHandle()


/******************************************/
/********* SYDE 192 - Team Blonde *********/
/********** ARDUINO 2 - RECEIVER **********/
/******************************************/

#define ON 1
#define OFF 0
#define row1 14
#define row2 15
#define row3 16
#define col1 17
#define col2 18
#define col3 19


boolean ledMatrixStates[9];
String serialIn;
int ledScrollState;

  
/* Steup Function ****************************/
void setup() {
  
  //Init IR Serial and RX pin
  Serial.begin(2400);  //Start serial with baud rate of 2400
  
  //Init LED matrix and pins
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  boolean ledMatrixStates[] = {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF};
  ledScrollState = 1;
  
  /***  LED MATRIX SCHEMATIC LAYOUT  *** (This takes precidence over the paper copy)
  * Row1/Pin 14 - (LED 1) -- (LED 2) -- (LED 3)
  * Row2/Pin 15 - (LED 4) -- (LED 5) -- (LED 6)
  * Row3/Pin 16 - (LED 7) -- (LED 8) -- (LED 9)
  *                  |          |          |
  *                Pin17      Pin18      Pin19
  *                 Col1       Col2       Col3 
  * 
  * LED 1: Red power/status LED, bottom of volume bar/always on (except when sleeping)
  * LED 2-9: Volume display LEDS
  * 
  */
   
          
  //Init interrupt
  //attachInterrupt(0, interruptHandle, HIGH);
  
  
}//End of setup()


/* Main Loop ********************************/
void loop() {
  //Read IR serial input and make appropriate volume, or mute adjustments
  serialIn += Serial.read();
  //TODO: - Add functionality based on serial messages. Eg. if serial message == volume up command, change appropriate matrix LEDs
  //      - Check for code deliminator or serial -1 state
  
  //Rotate through which pin is turned on
  //Set corresponding row high and column low (on)
    switch (ledScrollState) {
      case 1:
        digitalWrite(row1, ledMatrixStates[0]);  //Sets the corresponding row to the state of the LED (whether or not it should be on)
        digitalWrite(col1, !ledMatrixStates[0]); //Sets the corresponding column to the !state (opposite since this is the ground line of the LEDs) of the LED (whether or not it should be on)
        break;
      case 2:
        digitalWrite(row1, ledMatrixStates[1]);
        digitalWrite(col2, !ledMatrixStates[1]);
        break;
      case 3:
        digitalWrite(row1, ledMatrixStates[2]);
        digitalWrite(col3, !ledMatrixStates[2]);
        break;
      case 4:
        digitalWrite(row2, ledMatrixStates[3]);
        digitalWrite(col1, !ledMatrixStates[3]);
        break;
      case 5:
        digitalWrite(row2, ledMatrixStates[4]);
        digitalWrite(col2, !ledMatrixStates[4]);
        break;
      case 6:
        digitalWrite(row2, ledMatrixStates[5]);
        digitalWrite(col3, !ledMatrixStates[5]);
        break;
      case 7:
        digitalWrite(row3, ledMatrixStates[6]);
        digitalWrite(col1, !ledMatrixStates[6]);
        break;
      case 8:
        digitalWrite(row3, ledMatrixStates[7]);
        digitalWrite(col2, !ledMatrixStates[7]);
        break;
      case 9:
        digitalWrite(row3, ledMatrixStates[8]);
        digitalWrite(col3, !ledMatrixStates[8]);
        ledScrollState = 0;  //Reset scroll counter
        break;
      default:
        ledScrollState++;
    }
    
    delay(5);
    
}//End of loop()


/* Interrupt Handle *****************************/
void interruptHandle() {
  //Wake up or sleep arduino on interrupt

}//End of interruptHandle()


void selectLED(int ledNumber){
  //Set all LED rows low and columns high (off)
    digitalWrite(row1, LOW);
    digitalWrite(row2, LOW);
    digitalWrite(row3, LOW);
    digitalWrite(col1, HIGH);
    digitalWrite(col2, HIGH);
    digitalWrite(col3, HIGH);
    

}

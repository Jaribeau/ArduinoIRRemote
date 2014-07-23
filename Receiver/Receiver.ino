
/******************************************/
/********* SYDE 192 - Team Blonde *********/
/********** ARDUINO 2 - RECEIVER **********/
/******************************************/

  /** LED CONTROL EXPLAINED **/
  /* 9 LEDs are being controlled through only 6 pins. This is done by connecting the cathodes of 
  /* all LEDs in the same row to one pin. Same with annodes, except in columns. To turn on a
  /* specific LED, its row pin is set high and it's column pin set low. The intersection of these
  /* causes that LED to turn on.
  /*
  /* In order to make it appear that more than one LED is ON at a time, each time the code iterates,
  /* it turns on a different LED (one at a time). This happens fast enough that it appears to the
  /* human eye that they are all ON at the same time.
  /*
  /* In this code, the code rotates through every LED. If the LED's state is supposed to be OFF (as
  /* indicated by the corexponding bit in the "ledMatrixStates" array), that LED will not be turned
  /* ON during it's "turn".
  */
    
  /***  LED MATRIX SCHEMATIC LAYOUT  *** (This takes precidence over the paper copy)
  * Row1/Pin 8  - (LED 1) -- (LED 2) -- (LED 3)
  * Row2/Pin 9  - (LED 4) -- (LED 5) -- (LED 6)
  * Row3/Pin 10 - (LED 7) -- (LED 8) -- (LED 9)
  *                  |          |          |
  *                Pin11      Pin12      Pin13
  *                 Col1       Col2       Col3 
  * 
  * LED 1: Red power/status LED, bottom of volume bar/always on (except when sleeping)
  * LED 2-9: Volume display LEDS
  * 
  */

#define ON 1
#define OFF 0
#define row1 8
#define row2 9
#define row3 10
#define col1 11
#define col2 12
#define col3 13


byte ledMatrixStates [] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
int ledScrollState = 0;
String serialIn;
int serialQueCount, charIn;
int volume = 0;
boolean power = 0;
boolean mute = 0;

  
/* Steup Function */
void setup() {
  
  //Init IR Serial and RX pin
  Serial.begin(2400);  //Start serial with baud rate of 2400
  
  //Init LED matrix and pins
  pinMode(row1, OUTPUT);
  pinMode(row2, OUTPUT);
  pinMode(row3, OUTPUT);
  pinMode(col1, OUTPUT);
  pinMode(col2, OUTPUT);
  pinMode(col3, OUTPUT);    
  
  //Init interrupt
  //attachInterrupt(0, interruptHandle, HIGH);
  
}//End of setup()



/* Main Loop */
void loop() {
  
  refreshState(); //Function to read the serial, and take appropriate action on the LEDs
  
  setAllLEDsLow();
  scrollLEDMatrix(ledScrollState);
  ledScrollState++;
  if(ledScrollState > 9)
    ledScrollState = 1;
}//End of loop()



/* Interrupt Handle */
void interruptHandle() {
  //Wake up or sleep arduino on interrupt

}//End of interruptHandle()


//Function to read the serial, and take appropriate action on the LEDs
void refreshState()
{  
      //Read serial
      while(Serial.available())
      {  
        //While serial buffer contains messages
        charIn = Serial.read();
        serialIn += (char)charIn;  //Move character from serial buffer to String in working memory
      }
      
      //If full command is received (">" is end command character, update LED state matrix)
      if(serialIn.indexOf('>') >= 0)
      {  
        //Print command received to serial for testing
        //Serial.print("Test:");
        //Serial.print(serialIn);
        //Serial.println(".");
        
        //Update variable corresponding to command received
        if(serialIn.equals("Yellow>"))
          power = !power;
        else if(serialIn == "Red>" && volume < 8)
        {
            volume++;
            mute = false;
        }
        else if(serialIn.equals("Green>") && volume > 0)
        {
            volume--;
            mute = false;
        }
        else if(serialIn.equals("Blue>"))
        {
          mute = !mute;
        }
        
        serialIn = ""; //Clear serial string variable in wrking memory
        
        ////Update states of LEDs
        
          //Set all volume LEDs status to off
          for(int x = 1; x <= 8; x++)
            ledMatrixStates[x] = 0;
            
          //Make volume LEDs on = volume
          for(int x = 0; x <= volume; x++)
            ledMatrixStates[x] = 1;
            

    
        //Update volume LEDs, all turned off if mute is enabled
        if(mute)
        {
          //Set all volume LEDs status to off
          for(int x = 1; x <= 8; x++)
            ledMatrixStates[x] = 0;
        }
        
        /*
        //Update power LED
        if(power)
        {
          ledMatrixStates[0] = 1;  //Set power LED state to ON
        }
        else
        {
          //Set all volume LEDs status to off
          for(int x = 1; x < 9; x++)
            ledMatrixStates[x] = 0;
        }
        */
                    
        //Print out LED states
        for(int x = 0; x <= 8; x++)
        {
            Serial.print(ledMatrixStates[x]);
            Serial.print(", ");
        }
        Serial.println();
        Serial.println(mute);
    
      }//End of command actions   
      
  
}//End of refreshState()



/****** Function to update the state (on if it's matrixState is on, off if off) of a given LED */
void scrollLEDMatrix(int nextLEDToFlash){
  
  switch (nextLEDToFlash) {
    case 1:
      digitalWrite(row1, !ledMatrixStates[0]);  //Sets the corresponding row to the state of the LED (whether or not it should be on)
      digitalWrite(col1, ledMatrixStates[0]); //Sets the corresponding column to the !state (opposite since this is the ground line of the LEDs) of the LED (whether or not it should be on)
      break;
    case 2:
      digitalWrite(row1, !ledMatrixStates[1]);
      digitalWrite(col2, ledMatrixStates[1]);
      break;
    case 3:
      digitalWrite(row1, !ledMatrixStates[2]);
      digitalWrite(col3, ledMatrixStates[2]);
      break;
    case 4:
      digitalWrite(row2, !ledMatrixStates[3]);
      digitalWrite(col1, ledMatrixStates[3]);
      break;
    case 5:
      digitalWrite(row2, !ledMatrixStates[4]);
      digitalWrite(col2, ledMatrixStates[4]);
      break;
    case 6:
      digitalWrite(row2, !ledMatrixStates[5]);
      digitalWrite(col3, ledMatrixStates[5]);
      break;
    case 7:
      digitalWrite(row3, !ledMatrixStates[6]);
      digitalWrite(col1, ledMatrixStates[6]);
      break;
    case 8:
      digitalWrite(row3, !ledMatrixStates[7]);
      digitalWrite(col2, ledMatrixStates[7]);
      break;
    case 9:
      digitalWrite(row3, !ledMatrixStates[8]);
      digitalWrite(col3, ledMatrixStates[8]);
      ledScrollState = 0;  //Reset scroll counter
      break;
   }
}//End of scrollLEDMatrix()

void setAllLEDsLow(){
  //Set all LED rows low and columns high (off)
    digitalWrite(row1, HIGH);
    digitalWrite(row2, HIGH);
    digitalWrite(row3, HIGH);
    digitalWrite(col1, LOW);
    digitalWrite(col2, LOW);
    digitalWrite(col3, LOW);
}//End of setAllLEDsLow()

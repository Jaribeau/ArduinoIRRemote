// Puts the Arduino to sleep
#include <avr/interrupt.h>
#include <avr/sleep.h>

// use a pull up resistor on pin 2 and 12 to 5V.
// attach a led with resistor to gnd on pin 10.
// ground pin 12 momentary to put the Arduino to sleep
// and ground pin 2 momentary to wake it up again.
// When awake, the arduino will run the led_blink code together 

int ledPin = 13;         // LED connected to digital pin 13         
int sleepPin = 12;       // active LOW, ground this pin momentary to sleep
int interruptPin = 10;   // LED to show the action of a interrupt
int wakePin = 2;         // active LOW, ground this pin momentary to wake up
int sleepStatus = 0;     // variable to store a request for sleep

void setup()
{
pinMode(ledPin, OUTPUT);         // sets the digital pin as output
pinMode(interruptPin, OUTPUT);   //
pinMode(sleepPin, INPUT);        // sets the digital pin as input
pinMode(wakePin, INPUT);

/* Enable an interrupt. In the function call 
attachInterrupt(A, B, C)
A   can be either 0 or 1 for interrupts on pin 2 or 3.   
B   Name of a function you want to execute while in interrupt A.
C   Trigger mode of the interrupt pin. Can be:
  LOW - a low level trigger
  CHANGE - a change in level trigger
  RISING - a rising edge of a level trigger
  FALLING - a falling edge of a level trigger

All sleep modes use LOW except for the IDLE sleep mode.
*/

// use pin 2, interrupt 0, to run function wakeUpNow when pin 2 gets LOW. 
attachInterrupt(0, wakeUpNow, LOW);
}
// put the arduino to sleep
void sleepNow()         
{
  /* 
  Set sleep mode. In the Atmega8 datasheet
  http://www.atmel.com/dyn/resources/prod_documents/doc2486.pdf pg35
  there is a list of sleep modes that explains which clocks and 
  wake up sources are available in each sleep modus.

  In the avr/sleep.h file, the call names of each sleep modus are found:
  The 5 different modes are:
    SLEEP_MODE_IDLE         -the least power savings 
    SLEEP_MODE_ADC
    SLEEP_MODE_PWR_SAVE
    SLEEP_MODE_STANDBY
    SLEEP_MODE_PWR_DOWN     -the most power savings
  Want as much power savings as possible, so use SLEEP_MODE_PWR_DOWN
  */

  // sleep mode is set here
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // enables the sleep bit in the mcucr register so sleep is possible. a safety pin.
  sleep_enable();              
  /* Enable an interrupt. address case where interrupt is pushed accidentally. ensure that accidentally pushed the interrupt button doesn't interrupt our running program. To run interrupt code other than the sleep function, place it in the setup(). 
  In the function call attachInterrupt(A, B, C)
  A   can be either 0 or 1 for interrupts on pin 2 or 3.   
  B   Name of a function you want to execute at interrupt for A.
  C   Trigger mode of the interrupt pin. can be:
    LOW        a low level triggers
    CHANGE     a change in level triggers
    RISING     a rising edge of a level triggers
    FALLING    a falling edge of a level triggers

   All sleep modes use LOW except for the IDLE sleep mode.
   */
   // use interrupt 0 (pin 2) and run function wakeUpNow when pin 2 gets LOW 
  attachInterrupt(0,wakeUpNow, LOW); 
  // put arduino to sleep
  sleep_mode();                
  // first thing arduino does after waking from sleep: disable sleep
  sleep_disable();             
  // disable interrupt 0 on pin 2 so the wakeUpNow code will not be executed during normal run time
  detachInterrupt(0);          
  // wait 2 secs to allow people to notice the interrupt. light the LED to show that the interrupt is handled.
  delay(1000);                 
  // turn off the interrupt LED
  digitalWrite (interruptPin, LOW);
}

// Handle interrupt after wake-up.
void wakeUpNow() {
  //execute code here after wake-up before returning to the loop() function
  // timers and code using timers (serial.print and more...) will not work here.
  digitalWrite(interruptPin, HIGH);
}

void loop() {
  // sets the LED on
  digitalWrite(ledPin, HIGH);
  // waits for a second        
  delay(1000);
  // sets the LED off                         
  digitalWrite(ledPin, LOW);
  // waits for a second           
  delay(1000);
  // read sleep pin here. only active                          
  sleepStatus = digitalRead(sleepPin);
  //when blink led is off, start to put the device in sleep, call sleep function                                       
  if (sleepStatus == LOW) {
    sleepNow();
  }
}

String serialIn;
int serialQueCount, charIn;


/* Steup Function ********************/
void setup() {

  //Init IR/Serial TX pin
  Serial.begin(2400);
  pinMode(2, INPUT);

}//End of setup()


/* Main Loop *********************/
void loop() {      

  //Read serial, do stuff
      while(Serial.available()){
        charIn = Serial.read();
        serialIn += (char)charIn;
      }
      if(serialIn.indexOf('>') >= 0){
        Serial.print("Test: ");
        Serial.println(serialIn);
        serialIn = "";
      }


  /*
  //Read serial, do stuff
   int serialQueCount = Serial.available();
   if(serialQueCount > 0){
   while(serialQueCount--){
   charIn = Serial.read();
   serialIn += charIn;
   Serial.print("Test:");
   Serial.print((char)charIn);
   }
   }
   */

}//End of loop()


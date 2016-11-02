/*
Easy example of the deboucing libary for two inputs

     For further informations please visit http://www.legl.de/led-cube.html
     If you have any questions, suggestions for improvements or other remarks please write an e-mail. 

     License:
          Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License http://creativecommons.org/licenses/by-nc-sa/4.0/
          Please be honest and follow these rules
	 
     legl-electronics
*/

#include <Debouncing.h>

#define PIN_A 7           //input A
#define PIN_B 8           //input B
#define SAMPLES 3         //how often the same state must be read

//create the objects
Debouncing pinA(PIN_A, SAMPLES);
Debouncing pinB(PIN_B, SAMPLES);



void setup() {
     pinA.begin();
     pinB.begin();

     Serial.begin(9600);
}

void loop() {
     
     //update the states
     pinA.updateState();
     pinB.updateState();
     
     //it there was a change we want to print it
     if(pinA.returnEdge() != DEB_NO_EDGE)
     {
          Serial.print("A is ");
          //get actual state
          Serial.print(pinA.returnState());
          Serial.print("! Bounced: ");
          //calculate the bouncings
          //if there is now bouncing the returnCount = SAMPLES --> the bouncings are the deviation
          Serial.print(pinA.returnCount() - SAMPLES);
          Serial.println(" times.");
      }  
 

     if(pinB.returnEdge() != DEB_NO_EDGE)
     {
          Serial.print("B is ");
          Serial.print(pinB.returnState());
          Serial.print("! Bounced: ");
          Serial.print(pinB.returnCount() - SAMPLES);
          Serial.println(" times.");
      }     
    
}


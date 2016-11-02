#ifndef Debouncing_h
#define Debouncing_h

#include "Arduino.h"

/*	 
	  For further informations please visit http://www.legl.de/led-cube.html
      If you have any questions, suggestions for improvements or other remarks please write an e-mail. 

     License:
        Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License http://creativecommons.org/licenses/by-nc-sa/4.0/
        Please be honest and follow these rules
	 
		legl-electronics
*/


typedef enum {DEB_FALLING_EDGE, DEB_RISING_EDGE, DEB_NO_EDGE} DebouncingReturnType;

class Debouncing
{
     public:
          Debouncing(int pin, int samples);
		  
		  //inits everything
          void begin();
		  
		  //updates the pin´s state
          void updateState();
		  
		  //returns the last save state of the pin
          boolean returnState();
		  
		  //returns the calls of updateState from the last save state to the new save state 
          int returnCount();
		  
		  //returns the edge, once checked it will return that there was no edge
          DebouncingReturnType returnEdge();

     private:
		  //saves the digital input pin
          int _PIN;
		  //saves the wantet samples until it is said that the pin state is save
          int _SAMPLES;
		  //saves the last state of the pin
          boolean _lastState;
		  //saves the last save state of the pin
          boolean _saveState;
          //saves the calls of updateState from the last save state to the new save state 
		  int _count;
		  //saves the samples we had in the same state
          int _samples;
		  //saves whether we are in a save state or not 
          boolean _inSaveState;
		  //saves the edge
          DebouncingReturnType _edge;
};

#endif




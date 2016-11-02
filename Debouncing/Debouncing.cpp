/*
     Debouncing - Libary for debouncing digital inputs
     created by legl-electronics
     known bucks -	 
	 
	  For further informations please visit http://www.legl.de/led-cube.html
      If you have any questions, suggestions for improvements or other remarks please write an e-mail. 

     License:
        Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License http://creativecommons.org/licenses/by-nc-sa/4.0/
       Please be honest and follow these rules
	 
		legl-electronics
*/


#include "Debouncing.h"

Debouncing::Debouncing(int pin, int samples)
{
  _PIN = pin;
  _SAMPLES = samples;
}

//inits everything
void Debouncing::begin()
{
	 //set the pin mode
     pinMode(_PIN, INPUT);
	 //turn the pullup on
     digitalWrite(_PIN, HIGH);
	 
	 //init all variables
     _lastState = digitalRead(_PIN);
     _saveState = _lastState;
     _count = 1;
     _samples = 1;
     _inSaveState = true;
     _edge = DEB_NO_EDGE;
}

//updates the pin´s state
void Debouncing::updateState()
{
	 //if we are in a save state
     if(_inSaveState == true)
     {
		  //and there is a change we want to reset everything
		  //runs only the first time when there was a change after a save state
          if (_saveState != digitalRead(_PIN))
          {
               _lastState = digitalRead(_PIN);
               _samples = 1;
               _count = 1;
               _inSaveState = false;
          }
      }
      else
      {
		  //if there was a change to the last saved state we reset the samples
          if (_lastState != digitalRead(_PIN))
          {
               _lastState = digitalRead(_PIN);
               _samples = 1;
               _count ++;
          }
          else
          {
			   //it there was no change we can increase the samples
               _samples ++;
               _count ++;
			   
			   //if we have enough samples (the state of the pin did not changes sample-times) we have a new save state
               if (_samples >= _SAMPLES)
               {
					//save that we are in a save state and the save state
                    _saveState = digitalRead(_PIN);
                    _lastState = _saveState;
                    _inSaveState = true;
					
					//save that we have a edge
                    if(_saveState == HIGH)
                    {
                         _edge = DEB_RISING_EDGE;
                    }
                    else
                    {
                         _edge = DEB_FALLING_EDGE;
                    }
               }
          }
     }
}

//returns the last save state of the pin
boolean Debouncing::returnState()
{
     return _saveState;
}

//returns the calls of updateState from the last save state to the new save state
///with this you can calculate the the bouncings of the pin (count - SAMPLES)
//it can also be used if you want to know when the first change was
int Debouncing::returnCount()
{
     return _count;
}

//returns the edge, once checked it will return that there was no edge
DebouncingReturnType Debouncing::returnEdge()
{
     DebouncingReturnType tmpEdge = _edge;
     _edge = DEB_NO_EDGE;
     return tmpEdge;
}

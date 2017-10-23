#ifndef _OUTPUTPIN_H
#define _OUTPUTPIN_H

#include "Def.h"
#include "Pin.h"
/*class OutputPin 
  ---------------
 An output obtains a value as a result of calculating the outputs of
 a component.
*/
//Pre Deff.s:
//class Pin;
class InputPin;

class OutputPin: public Pin	//inherited from class Pin
{
private:

	//Array of Input Pins (pointers) to be connected to that OutputPin
	//For simplicity, we consider it a constant length
	InputPin* m_InputPins[FANOUT];	
	int m_FanOut;	//Maximum No. of input pins connected to that output pin (depends on the component)

	int m_ConnectionsCount;	//Actual No. of input pins connected to that output pin

public:

	//constructor & destructor:
	OutputPin();	
	virtual ~OutputPin();

	//setters:
	bool ConnectTo(InputPin* r_InputPin);	//connect to a new input pin
	bool DisConnectTo(InputPin* r_InputPin);
	
	//getters:
	InputPin ** getConnectedPins();
	int getConnectionsCount();
	bool isConnected();

};

#endif
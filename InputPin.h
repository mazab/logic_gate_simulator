#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Def.h"
#include "Pin.h"
//Pre Deff.s:
//class Pin;
class OutputPin;
class Wire;

class InputPin: public Pin	//inherited from class Pin
{
private:

	OutputPin* m_OutputPin; //ptr to the InputPin connected to the pin

	Wire* m_Wire;

public:

	//constructor & destructor:
	InputPin();
	virtual ~InputPin();

	//setters:
	void setOutputPin(OutputPin* r_OutputPin);
	void setWire(Wire* r_Wire);
	
	//getters:
	OutputPin* getOutputPin();
	Wire* getWire();
	
};

#endif
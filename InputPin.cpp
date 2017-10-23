#include "Includes.h"

//Constructor:
InputPin::InputPin()
{
	m_Wire = NULL;
}
//==============================================================================================================
//Destructor:
InputPin::~InputPin()
{}
//==============================================================================================================
//setters:
void InputPin::setOutputPin(OutputPin* r_OutputPin)
{
	m_OutputPin = r_OutputPin;
}

void InputPin::setWire(Wire* r_Wire)
{
	m_Wire = r_Wire;
}
//==============================================================================================================
//getters:
OutputPin* InputPin::getOutputPin()
{
	return m_OutputPin;
}

Wire* InputPin::getWire()
{
	return m_Wire;
}


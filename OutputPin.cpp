#include "Includes.h"

//Constructor:
OutputPin::OutputPin()
{
	m_FanOut = FANOUT;
	for(int i= m_FanOut-1; i>=0; i--)
		m_InputPins[i] = NULL;

	m_ConnectionsCount = 0;		//initially Pin is not connected to anything.

}
//==============================================================================================================
//Destructor:
OutputPin::~OutputPin()
{}
//==============================================================================================================
//setters:

//Function ConnectTo:
//Connects the ouput pin the the passed input pin if the fan out permits
//if the no. of connected pin is already equals to the fan out, no more connections can be created.
bool OutputPin::ConnectTo(InputPin *r_InputPin)
{
	if(m_ConnectionsCount < m_FanOut)
	{
		m_InputPins[m_ConnectionsCount] = r_InputPin;	//add a new pin the the array of pins
		m_ConnectionsCount++;		//increase no. of connected pins
		m_isConnected = true;
		return true;
	}
	
	return false;	//can't connect to any more input pins
}

bool OutputPin::DisConnectTo(InputPin* r_InputPin)
{
	int tmp = m_ConnectionsCount;
	while(tmp > 0)
	{
		if( r_InputPin == m_InputPins[tmp-1])
		{
			for(int i=tmp+1; i<=m_ConnectionsCount; i++)
				m_InputPins[i-2] = m_InputPins[i-1];
			m_InputPins[m_ConnectionsCount-1] = NULL;
			m_ConnectionsCount --;
			if(m_ConnectionsCount == 0)
				m_isConnected = false;
			return true;
		}
		else
			tmp--;
	}
	return false;
}
//==============================================================================================================
//getters:
InputPin ** OutputPin::getConnectedPins()
{
	return m_InputPins;
}

int OutputPin::getConnectionsCount()
{
	return m_ConnectionsCount;
}




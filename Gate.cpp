#include "Includes.h"

//Constructor:
Gate::Gate(char* r_Label, ComponentType r_Name, char* r_URL ,int r_Inputs)
	 :Component(r_Label, r_Name)
{
	m_URL = r_URL;

	m_ConnectedInputPins =0;

	//this case will happen when loading a UserDefined gata:
	if(r_Inputs != 0)
	{
		//we will set them manualy later:
		m_Inputs = r_Inputs;
		for(int i=0; i<4; i++)
		{
			m_InputPins[i] = new InputPin;
			m_InputPins[i]->setComponent(this);
		}
	}
	m_OutputPin = new OutputPin;
	m_OutputPin->setComponent(this);
}
//====
Gate::Gate(char* r_Label, ComponentType r_Name, const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager, char* r_URL, int r_Inputs)
	 :Component(r_Label, r_Name, r_GfxInfo, r_ApplicationManager)
{
	m_ConnectedInputPins =0;

	m_URL = r_URL;

	//this case will happen when loading a UserDefined gata:
	if(r_Inputs != 0)
	{
		//we will set them manualy later:
		m_Inputs = r_Inputs;
		for(int i=0; i<m_Inputs; i++)
		{
			m_InputPins[i] = new InputPin;
			m_InputPins[i]->setComponent(this);
		}
	}

	m_OutputPin = new OutputPin;
	m_OutputPin->setComponent(this);
	Point* p = new Point;
	p->x = m_Current_GfxInfo.UpLeft.x + 71;
	p->y = m_Current_GfxInfo.UpLeft.y + 26;
	m_OutputPin->setPosition(p);

	m_FanOut = 0;
}
//==============================================================================================================
//Destructor:
Gate::~Gate()
{
	delete [] m_InputPins;
}
//==============================================================================================================
//Setters:
void Gate::incInputs()
{
	m_ConnectedInputPins++;
}

void Gate::decInputs()
{
	m_ConnectedInputPins--;
}

	void Gate::incFanouts()
{
	this->m_FanOut++;
}

void Gate::decFanouts()
{
	this->m_FanOut--;
}

bool Gate::ConnectOutputPinTo(InputPin* r_Input)
{
	bool test = m_OutputPin->ConnectTo(r_Input);
	this->m_FanOut = test ? m_FanOut : m_FanOut+1;
	return test;
}

bool Gate::DisconnectOutputPinFrom(InputPin* r_Input)
{
	bool test = m_OutputPin->DisConnectTo(r_Input);
	this->m_FanOut = test ? m_FanOut : m_FanOut-1;
	return test;
}

bool Gate::ConnectInputPinTo(OutputPin* r_Out)
{
	if(m_ConnectedInputPins < m_Inputs)
	{
		m_InputPins[m_ConnectedInputPins]->setOutputPin(r_Out);
		m_InputPins[m_ConnectedInputPins]->setConn(true);
		m_ConnectedInputPins++;
		return true;
	}
	else
		return false;
}

bool Gate::DisconnectInputPinFrom(OutputPin* r_Out)
{
	//Searching for the inputpin which connected to the given output pin:
	bool found = false;
	int i = 0;
	while( (!found) && (i< m_ConnectedInputPins) )
	{
		if( m_InputPins[i]->getOutputPin() == r_Out )
			found = true;
		else
			i++;
	}
	// If this pin was found:
	if(found)
	{
		if(i != m_ConnectedInputPins-1)
		{
			// 1)---> Put the Data at the last Pin in this Pin:
			m_InputPins[i]->setOutputPin( m_InputPins[m_ConnectedInputPins-1]->getOutputPin() );
			m_InputPins[i]->setWire( m_InputPins[m_ConnectedInputPins-1]->getWire() );
			
			// 2)---> Make the pointers in the wire and the output pin of the last pin, points to the pin 'i':
			(m_InputPins[i]->getOutputPin())->ConnectTo( m_InputPins[i]);
			(m_InputPins[i]->getWire())->setInputPin( m_InputPins[i]);
			(m_InputPins[i]->getOutputPin())->DisConnectTo(m_InputPins[m_ConnectedInputPins-1]);
		}

		// 3)---> Set the data in the last pin to NULL:
		m_InputPins[m_ConnectedInputPins-1]->setConn(false);
		m_InputPins[m_ConnectedInputPins-1]->setOutputPin(NULL);
		m_InputPins[m_ConnectedInputPins-1]->setWire(NULL);
		

		// 4)---> Count-- :
		m_ConnectedInputPins--;

		// 5)---> Return True:
		return true;
	}
	else
		return false;
}

void Gate::setInputs(int Num)
{
	m_Inputs = Num;
	for(int i=0; i< m_Inputs; i++)
		m_InputPins[i]->setComponent(this);
}

void Gate::setURL(char* r_URL)
{
	m_URL = r_URL;
}
//==============================================================================================================
//Getters:

//This function returns a reference to the specefied input pin,
//VI HENT!:
// use this call form to get a reference to the last added connection:
//            i.e:      InputPin* In = G.getInputPin( G.getConnectedInputs() ); // 'G' is an object from any gate !
InputPin* Gate::getInputPin(int Index)
{
	return m_InputPins[Index-1];
}
//===
OutputPin* Gate::getOutputPin()
{
	return  m_OutputPin;
}
//===
int Gate::getFanOuts()
{
	return m_FanOut;
}
//====
int Gate::getConnectedInputs()
{
	return m_ConnectedInputPins;
}
//====
int Gate::getInputPinsCount()
{
	return m_Inputs;
}

char* Gate::getURL()
{
	return this->m_URL;
}

int Gate::getInputPinIndex(InputPin* r_In)
{
	int i = 0;
	while(i < m_Inputs)
	{
		if (r_In == m_InputPins[i])
			return i+1;
		i++ ;
	}
}










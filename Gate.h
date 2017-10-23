#ifndef _GATE_H
#define _GATE_H

#include "Def.h"
#include "Component.h"
/*
  Class Gate
  -----------
  - Base class for all types of gates
  - Each gate has n inputs pins and one output pin
                     
					        Component
			____________________|___________________
		   |             |             |            |
		   *             *            Gate          *
*/

//Pre Deff.s:
class ApplicationManager;
class InputPin;
class OutputPin;

class Gate :public Component
{
protected:
	
	char* m_URL; //The path of the gate photo
	
	InputPin*  m_InputPins[4];	//Array of input pins of the gate
	
	OutputPin* m_OutputPin;	//The gate's output pin
	
	int m_Inputs;	//No. of input pins of that component.
	
	int m_FanOut; //the No. of the pins conected to this output pin
	
	int m_ConnectedInputPins;

public:
	//constructor & destructor:
	Gate(char* r_Label, ComponentType r_Name, char* r_URL , int r_Inputs=0);//when using this defolt constructor, You have to set the ApplicationManager and the Graphics info manualy.
	Gate(char* r_Label, ComponentType r_Name, const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager, char* m_URL, int r_Inputs=0);
	virtual ~Gate();
	
	//Setters: 
	void incInputs();
	void decInputs();
	void incFanouts();
	void decFanouts();                             
	//                                                                                                __
	bool ConnectOutputPinTo(InputPin* r_Input); //connect the gate's oitputPin to a specific InputPin   | 
	bool DisconnectOutputPinFrom(InputPin* r_Input);//Disconnect                                        |--->   return true,
	bool ConnectInputPinTo(OutputPin* r_Out); //Connect inputpin                                        | if the operation succeeded.
	bool DisconnectInputPinFrom(OutputPin* r_Out); //Disconnect                                       __| 
	void setInputs(int Num); //create the inputs' list (we will use it in some cases!
	void setURL(char* r_URL);
	                                                                                              
	//Getters:
	InputPin* getInputPin(int Index); // returns a reference to a specefied inputPin in this gate.
	OutputPin* getOutputPin(); //returns a reference to the Output pin of this gate.
	int getFanOuts(); // returns the number of the inputpins connected to the gate's gt4output pin.
	int getConnectedInputs();// returns the number of the connected input pins in this gate.
	int getInputPinsCount();//return the total number of input pins of this gate.
	int getInputPinIndex(InputPin* r_In); // returns the index of the pased inputpin
	char* getURL();

	//Pure Virtuals!:
	virtual void Load(ifstream&) = 0; //the component can load itself
	virtual void Save(ofstream& out) = 0; //the component can save itself
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw() = 0;	//for each component to Draw itself
	virtual bool IsMatch(Point p) = 0;   //to test if the point is located in the area of this gate
	//To change the pins GfxInfo:
	virtual void UpdatePinsGfxInfo()=0; //this function must be called after each change in the Component's GfxInfo/.
	virtual char* getUrl() = 0 ;
	virtual char* getIC() = 0;
	virtual char* getType() = 0;
	
};

#endif

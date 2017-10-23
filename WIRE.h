#ifndef _WIRE_H
#define _WIRE_H

#include "Def.h"
#include "Component.h"

/*
                            Component
			____________________|___________________
		   |             |             |            |
		  WIRE           *             *            *
*/

//Pre Deff.s:
//class Component;
class OutputPin;
class InputPin;


class Wire : public Component
{
private:

	Point  m_DrawingPoints[50];
	int m_DrawingPoints_Count;
	InputPin* m_Input;
	OutputPin* m_Output;
	int LoadingTerminator ;

public:

	//constructor & destructor:
	Wire();//when using this defolt constructor, You have to set the ApplicationManager and the Graphics info manualy.
	Wire(InputPin* r_Input, OutputPin* r_Output, const GraphicsInfo & r_GfxInfo /* pass any thing (useless)!*/, ApplicationManager* r_ApplicationManager);
	virtual ~Wire();
	
	//Setters:
	void setInputPin(InputPin* r_In);
	void setOutputPin(OutputPin* r_Out);

	//getters:
	InputPin* getInputPin();
	OutputPin* getOutputPin();
	int getConnectedPenIndex(); // returns the index of the connected inputpin in its gate.
	int getLoadingTerminator() ;

	//Virtuals!:
	virtual void Load(ifstream&); //the component can load itself
	virtual void Save(ofstream& out); //the component can save itself
	virtual void Operate();	//Calculates the output according to the inputs
	virtual void Draw();	//for each component to Draw itself
	virtual bool IsMatch(Point p); //to test if the point is located in the area of this gate
	virtual void UpdatePinsGfxInfo() ;
	virtual char* getUrl() ;
	virtual char* getIC() ;
	virtual char* getType() ;

	//service pack:
	bool DrawWire(int x=0, int y=0); //Draws the wire
	bool isValid(Point P, Component**  CmpList); //chek if this point is empty
};
#endif
#ifndef _LED_H
#define _LED_H

#include "Def.h"
#include "Component.h"

/*
                            Component
			____________________|___________________
		   |             |             |            |
		   *            LED            *            *
*/

//Pre Deff.s:
//class Component;
class InputPin;

class Led : public Component
{
private:

	char* m_URL_ON;
	char* m_URL_OFF;
	InputPin* m_Pin;

public:

	//constructor & destructor:
	Led(); //when using this defolt constructor, You have to set the ApplicationManager and the Graphics info manualy.
	Led(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager);
	virtual ~Led();

	//getters:
	InputPin* getPin();

	//Setters:
	bool connectTo(OutputPin* r_Out);

	//Virtuals!:
	virtual void Load(ifstream&); //the component can load itself
	virtual void Save(ofstream& out); //the component can save itself
	virtual void Operate();	//Calculates the output according to the inputs
	virtual void Draw();	//for each component to Draw itself
	virtual bool IsMatch(Point p);
	//To change the pins GfxInfo:
	virtual void UpdatePinsGfxInfo(); //this function must be called after each change in the Component's GfxInfo.
	virtual char* getUrl() ;
	virtual char* getIC() ;
	virtual char* getType() ;
};
#endif
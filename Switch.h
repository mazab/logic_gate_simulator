#ifndef _SWITCH_H
#define _SWITCH_H

#include "Def.h"
#include "Component.h"
/*
                            Component
			____________________|___________________
		   |             |             |            |
		   *             *             *         Switch
*/

//Pre Deff.s:
//class Component;
class OutputPin;

class Switch : public Component
{
private:
	
	OutputPin* m_Pin;
	char* m_URL_ON;
	char* m_URL_OFF;

public:
	
	//constructor & destructor:
	Switch(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager);
	Switch(); //when using this defolt constructor, You have to set the ApplicationManager and the Graphics info manualy.
	virtual ~Switch();

	//getters:
	OutputPin* getPin();
	

	//setter:
	bool ConnectTo(InputPin* In);

	//Virtuals!:
	virtual void Load(ifstream&); //the component can load itself
	virtual void Save(ofstream& out); //the component can save itself
	virtual void Operate();	//Calculates the output according to the inputs
	virtual void Draw();	//for each component to Draw itself
	virtual bool IsMatch(Point p);
	//To change the pins GfxInfo:
	virtual void UpdatePinsGfxInfo(); //this function must be called after each change in the Component's GfxInfo.
	char* getUrl();
	char*getIC();
	char* getType();


};
#endif
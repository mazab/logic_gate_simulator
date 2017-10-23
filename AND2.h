#ifndef _AND2_H
#define _AND2_H


#include "Def.h"

//Pre deff.s:
//class Gate;

class AND2:public Gate
{
public:

	//constructor & destructor:
	AND2();//when using this defolt constructor, You have to set the ApplicationManager and the Graphics info manualy
	AND2(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager);
	virtual ~AND2();

	//Virtuals!:
	virtual void Load(ifstream&); //the component can load itself
	virtual void Save(ofstream& out); //the component can save itself
	virtual void Operate();	//Calculates the output of the gate
	virtual void Draw();	//Draws gate
	virtual bool IsMatch(Point p);
	//To change the pins GfxInfo:
	virtual void UpdatePinsGfxInfo(); //this function must be called after each change in the Component's GfxInfo.
	virtual char* getUrl();
	virtual char* getIC();
	virtual char* getType();
};

#endif
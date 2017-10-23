#ifndef _NAND3_H
#define _NAND3_H

#include "Gate.h"

//Pre deff.s:
//class Gate;

class NAND3:public Gate
{
public:

	//constructor & destructor:
	NAND3();//when using this defolt constructor, You have to set the ApplicationManager and the Graphics info manualy
	NAND3(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager);
	virtual ~NAND3();

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
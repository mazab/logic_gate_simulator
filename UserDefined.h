#ifndef _USER_DEFINED_H
#define _USER_DEFINED_H

/*
  Class UserDefined:
  -------------------
  represent a multi-input User Defined gate
*/
#include "Gate.h"

class UserDefined:public Gate
{
private:
	char *m_InputsNames; // The names of the inputs
	char* m_Formula; // The logical formula which calculates the output

public:
	//constructor & destructor:
	UserDefined();//when using this defolt constructor, You have to set the ApplicationManager and the Graphics info manualy
	UserDefined(const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager, char* r_Label, int r_Inputs, char* r_Formula);
	virtual ~UserDefined();

	//setters:
	void createInputsNames(int i); // set the m_Inputs =i & generate the defult names for this i (use it only one time!)
	void setFormula(char* r_Formula);

	//getters:
	char* getFormula(); //returns the formula

	//Virtuals!:
	virtual void Load(ifstream&); //the component can load itself
	virtual void Save(ofstream& out); //the component can save itself
	virtual void Operate();	//Calculates the output of the gate
	virtual void Draw();	//Draws gate
	virtual bool IsMatch(Point p);
	
	//To change the pins GfxInfo:
	virtual void UpdatePinsGfxInfo(); //this function must be called after each change in the Component's GfxInfo.

};

#endif
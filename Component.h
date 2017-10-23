#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "Def.h"
#include <iostream>

using namespace std;
//Pre Deff.s:
class ApplicationManager;

//Base class for classes Gate, SWITCH, and LED.
class Component
{	
protected:

	static int ID_Generator; //used in generating IDs.
	
	int m_Level;

	bool Moving; //true if the component is moving

	int m_ID; //the key we can use to find the component
	
	//The parameters required to draw a component:
	GraphicsInfo m_Current_GfxInfo; //the current possetions info. for this component
	GraphicsInfo m_Old_GfxInfo; // the old possetions info. (used on "redo")
	
	//the Label of the component:
	char* m_Current_Label; //the current Label
	char* m_Old_Label; //for the "undo" action
	
	ComponentType m_Name;// the name of the component
	
	ApplicationManager * m_ApplicationManager; // pointer to the ApplicationManager, gives acces to input and output classes, and also the container classes

public:
	
	//constructor & destructor:
	Component(char* r_Label, ComponentType r_Name, const GraphicsInfo & r_GfxInfo, ApplicationManager* r_ApplicationManager);
	Component(char* r_Label, ComponentType r_Name); //this constructor will be used in the loading action
	virtual ~Component();

	//Setters:
	void changeMovingStatus(); 
	void setApplicationManager(ApplicationManager * r_ApplicationManager);
	void setCurrentGfxInfo(const GraphicsInfo & r_GfxInfo);
	void setOldGfxInfo(const GraphicsInfo & r_GfxInfo);
	void setCurrentLabel(char* r_Label);
	void setOldLabel(char* r_Label);
	void setLevel(int l);
	
	//getters:
	bool isMoving();
	static int getIDGenerator();
	int getID();
	GraphicsInfo getCurrentGfxInfo();
	GraphicsInfo getOldGfxInfo();
	char* getCurrentLabel();
	char* getOldLabel();
	ComponentType getName();
	int getLevel();
	
	//Pure Virtuals!:
	virtual void Load(ifstream&) = 0; //the component can load itself
	virtual void Save(ofstream& out) = 0; //the component can save itself
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw() = 0;	//for each component to Draw itself
	virtual bool IsMatch(Point p) = 0; //to test if the point is located in the area of this gate
	//To change the pins GfxInfo:
	virtual void UpdatePinsGfxInfo() = 0; //this function must be called after each change in the Component's GfxInfo. 
	virtual char* getUrl() = 0;
	virtual char* getIC() = 0;
	virtual char* getType() = 0;
	
};

#endif

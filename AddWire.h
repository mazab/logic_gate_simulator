#ifndef WIRE_H
#define WIRE_H

#include "AddComponent.h"

class AddWire : public AddComponent
{
private:
	bool First; //true if this excution in the first time
public:
	AddWire(OutputPin* Source, InputPin* Destination ,ApplicationManager* pManager);
	void ReadActionParameters(ApplicationManager* pManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager* pMananger);
	//unExecutes the action in order to undo it
	virtual void unExecute(ApplicationManager* pManager);
	~AddWire();
};

#endif


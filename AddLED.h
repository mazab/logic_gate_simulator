#ifndef _ADD_LED_GATE_H
#define _ADD_LED_GATE_H

#include "AddComponent.h"

class AddLED :	public AddComponent
{
public:
	AddLED (Point Center , ApplicationManager* r_ptrManager);
	void ReadActionParameters(ApplicationManager* pManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager* pMananger);
	//unExecutes the action in order to undo it
	virtual void unExecute(ApplicationManager* pManager);

	virtual ~AddLED();
};

#endif
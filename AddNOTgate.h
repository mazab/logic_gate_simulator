#ifndef _ADD_NOT_GATE_H
#define _ADD_NOT_GATE_H

#include "AddComponent.h"

class AddNOTgate :	public AddComponent
{
public:
	AddNOTgate (Point Center , ApplicationManager* r_ptrManager);
	void ReadActionParameters(ApplicationManager* pManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager* pMananger);
	//unExecutes the action in order to undo it
	virtual void unExecute(ApplicationManager* pManager);

	virtual ~AddNOTgate();
};

#endif
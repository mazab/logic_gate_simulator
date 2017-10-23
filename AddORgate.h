#ifndef _ADD_OR_GATE_H
#define _ADD_OR_GATE_H

#include "AddComponent.h"

class AddORgate :  public AddComponent
{
public:
	AddORgate (Point Center , ActionType A , ApplicationManager* r_ptrManager);
	void ReadActionParameters(ApplicationManager* pManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager* pMananger);
	//unExecutes the action in order to undo it
	virtual void unExecute(ApplicationManager* pManager);

	virtual ~AddORgate();
};

#endif
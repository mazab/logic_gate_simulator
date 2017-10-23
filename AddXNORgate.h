#ifndef _ADD_XNOR_GATE_H
#define _ADD_XNOR_GATE_H

#include "AddComponent.h"

class AddXNORgate :	public AddComponent
{
public:
	AddXNORgate (Point Center , ActionType A , ApplicationManager* r_ptrManager);
	void ReadActionParameters(ApplicationManager* pManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager* pMananger);
	//unExecutes the action in order to undo it
	virtual void unExecute(ApplicationManager* pManager);

	virtual ~AddXNORgate();
};

#endif
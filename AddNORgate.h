#ifndef _ADD_NOR_GATE_H
#define _ADD_NOR_GATE_H

#include "AddComponent.h"

class AddNORgate :	public AddComponent
{
public:
	AddNORgate (Point Center , ActionType A , ApplicationManager* r_ptrManager);
	void ReadActionParameters(ApplicationManager* pManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager* pMananger);
	//unExecutes the action in order to undo it
	virtual void unExecute(ApplicationManager* pManager);

	virtual ~AddNORgate();
};

#endif
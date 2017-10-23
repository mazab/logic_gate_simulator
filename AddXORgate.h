#ifndef _ADD_XOR_GATE_H
#define _ADD_XOR_GATE_H

#include "AddComponent.h"

class AddXORgate :	public AddComponent
{
public:
	AddXORgate (Point Center , ActionType A , ApplicationManager* r_ptrManager);
	void ReadActionParameters(ApplicationManager* pManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager* pMananger);
	//unExecutes the action in order to undo it
	virtual void unExecute(ApplicationManager* pManager);

	virtual ~AddXORgate();
};

#endif
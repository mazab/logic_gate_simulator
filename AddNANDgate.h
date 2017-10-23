#ifndef _ADD_NAND_GATE_H
#define _ADD_NAND_GATE_H

#include "AddComponent.h"

class AddNANDgate :	public AddComponent
{
public:
	AddNANDgate (Point Center , ActionType A , ApplicationManager* r_ptrManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager* pMananger);
	//unExecutes the action in order to undo it
	virtual void unExecute(ApplicationManager* pManager);

	virtual ~AddNANDgate();
};

#endif
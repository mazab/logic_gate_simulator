#ifndef _ADD_AND_GATE_H
#define _ADD_AND_GATE_H

#include "AddComponent.h"

class AddANDgate :	public AddComponent
{
public:
	AddANDgate (Point Center , ActionType A , ApplicationManager* r_ptrManager);
	
	virtual void ReadActionParameters(ApplicationManager* pManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager* pMananger);
	//unExecutes the action in order to undo it
	virtual void unExecute(ApplicationManager* pManager);

	~AddANDgate() ;

};

#endif
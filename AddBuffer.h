#ifndef _ADD_BUFFER_GATE_H
#define _ADD_BUFFER_GATE_H

#include "AddComponent.h"

class Buffer;

class AddBuffer :	public AddComponent
{
public:
	AddBuffer (Point Center , ApplicationManager* r_ptrManager);
	void ReadActionParameters(ApplicationManager* pManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager* pMananger);
	//unExecutes the action in order to undo it
	virtual void unExecute(ApplicationManager* pManager);

	virtual ~AddBuffer();
};

#endif
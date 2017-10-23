#ifndef _ACTION_H
#define _ACTION_H

#include "Def.h"

//Base class for all possible actions (abstract class)
class Action
{
public:
	//Reads parameters required for action to execute
	virtual void ReadActionParameters(ApplicationManager *pManager)=0;
	
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager *pManager) = 0;

	//unExecute the action (to be used in the undo/redo operations)
	virtual void unExecute(ApplicationManager *pManager) = 0;

	
};

#endif
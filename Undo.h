#ifndef UNDO_H
#define UNDO_H

#include "Action.h"



//class Undo : this class job is to undo the top action in the undo stack
class Undo:public Action
{
public:

	//Reads parameters required for action to execute
	virtual void ReadActionParameters(ApplicationManager *pManager);
	
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager *pManager);

	//unExecute the action (to be used in the undo/redo operations)
	virtual void unExecute(ApplicationManager *pManager);
};

#endif
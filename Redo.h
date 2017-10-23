#ifndef REDO_H
#define REDO_H


#include "Action.h"


//class Redo : this class job is to redo the top action in the redo stack
class Redo:public Action
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
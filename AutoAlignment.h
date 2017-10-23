#ifndef AUTOALIGNMENT_H
#define AUTOALIGNMENT_H


#include "Action.h"

//class AutoAlignment: its job is to align the components of each level in a neat way
class AutoAlignment:public Action
{
private:
	//dimensions of the window
	int windowWidth;     
	int windowHeight;

	//number of levels in the design
	int LevelCount;

public:

	//Reads parameters required for action to execute
	virtual void ReadActionParameters(ApplicationManager *pManager);
	
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager *pManager);

	//unExecute the action (to be used in the undo/redo operations)
	virtual void unExecute(ApplicationManager *pManager);
};

#endif
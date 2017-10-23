#ifndef _REMOVE_H
#define _REMOVE_H

#include "action.h"

class Component;
class Wire;

class Remove :public Action
{
private:
	Component* Used;
	Wire* Wires[FANOUT];
	bool First;

public:
	Remove(void);
	~Remove(void);

	void setUsedComp(ApplicationManager *pManager);
	
	//Reads parameters required for action to execute
	virtual void ReadActionParameters(ApplicationManager *pManager);
	
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager *pManager);

	//unExecute the action (to be used in the undo/redo operations)
	virtual void unExecute(ApplicationManager *pManager);
};
#endif

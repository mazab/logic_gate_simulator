#ifndef SAVE_H
#define SAVE_H

#include "Action.h"

//class Save: saves the components in a file with the required formate
class Save:public Action
{
private:
	int windowWidth;
	int windowHeight;
public:

	//this fn reads the action parameters from the user
	virtual void ReadActionParameters(ApplicationManager *pManager);

	//this fn executes the action (Save) to load a specific file 
	virtual void Execute(ApplicationManager *pManager);

	//this fn will have empty body as we will not unExectes this action
	virtual void unExecute(ApplicationManager *pManager);
};

#endif
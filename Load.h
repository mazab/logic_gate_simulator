#ifndef LOAD_H
#define LOAD_H

#include "Action.h"

//class Load : Loads the components and the connections form the file specified by the user
class Load:public Action
{
private:
	int windowWidth ;
	int windowHeight ;
public:

	//this fn reads the action parameters from the user
	virtual void ReadActionParameters(ApplicationManager *pManager);

	//this fn executes the action (Load) to load a specific file 
	virtual void Execute(ApplicationManager *pManager);

	//this fn will have empty body as we will not unExectes this action
	virtual void unExecute(ApplicationManager *pManager);
};

#endif